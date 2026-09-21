using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Text;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Reflection;
using System.Windows.Forms;

namespace DarkEden.Updater
{
    // The 2008 "Darkeden Game Launcher" window: the original art, laid out by the
    // original numbers (GameUpdater2009, ScreenObjectInfo::InitRenewal). The
    // background carries every button in its normal state; an _on bitmap is drawn
    // over a button while the mouse is on it.
    sealed class LauncherForm : Form
    {
        static readonly Rectangle s_panel = new Rectangle(11, 30, 598, 357);        // was the web browser
        static readonly Rectangle s_homepage = new Rectangle(28, 410, 73, 47);
        static readonly Rectangle s_market = new Rectangle(115, 410, 73, 47);
        static readonly Rectangle s_start = new Rectangle(433, 410, 160, 47);
        static readonly Rectangle s_exit = new Rectangle(555, 9, 51, 17);
        static readonly Rectangle s_bar_files = new Rectangle(239, 419, 173, 4);
        static readonly Rectangle s_bar_total = new Rectangle(239, 429, 173, 4);
        static readonly Rectangle s_status = new Rectangle(0, 390, 620, 18);
        static readonly Rectangle s_drag = new Rectangle(0, 0, 620, 28);
        static readonly Point s_version_right = new Point(533, 12);

        // The art's 1024x768 / 800x600 switch. Those two are wiped off the pill they
        // sat in, and it carries our own display settings instead: a fullscreen box
        // and a size that opens a list.
        static readonly Rectangle s_pill = new Rectangle(204, 438, 212, 19);
        static readonly Rectangle s_fullscreen = new Rectangle(211, 439, 94, 17);
        static readonly Rectangle s_resolution = new Rectangle(312, 439, 98, 17);
        const int s_box = 11;                   // btn_on.bmp, the art's "selected" dot
        const int s_pill_clean_left = 231;      // columns of the pill with nothing drawn on them
        const int s_pill_clean_right = 386;

        enum Hot { None, Homepage, Market, Start, Exit, Fullscreen, Resolution }

        readonly UpdateEngine m_engine;
        readonly Config m_config;
        readonly Bitmap m_back;
        readonly Bitmap m_bar;
        readonly Dictionary<Hot, Bitmap> m_hover = new Dictionary<Hot, Bitmap>();
        readonly Dictionary<char, Bitmap> m_digits = new Dictionary<char, Bitmap>();
        readonly Bitmap m_ver;
        readonly Bitmap m_box_on;
        readonly ContextMenuStrip m_sizes = new ContextMenuStrip();
        readonly Font m_font = new Font("Segoe UI", 8.25f);
        readonly Font m_small_font = new Font("Segoe UI", 7.5f);
        readonly Timer m_timer = new Timer();
        Hot m_hot = Hot.None;
        Hot m_pressed = Hot.None;
        bool m_launching;
        bool m_auto_start;

        public LauncherForm(UpdateEngine engine, Config config, bool autoStart)
        {
            m_engine = engine;
            m_config = config;
            m_auto_start = autoStart;

            m_back = CleanPill(LoadArt("back.bmp"));
            m_bar = LoadArt("bar_full.bmp");
            m_ver = LoadArt("ver.bmp");
            m_box_on = LoadArt("btn_on.bmp");
            m_hover[Hot.Homepage] = LoadArt("customers_on.bmp");
            m_hover[Hot.Market] = LoadArt("account_on.bmp");
            m_hover[Hot.Start] = LoadArt("start_on.bmp");
            m_hover[Hot.Exit] = LoadArt("exit_on.bmp");
            for (int d = 0; d <= 9; d++)
                m_digits[(char)('0' + d)] = LoadArt("ver_0" + d + ".bmp");
            m_digits['.'] = LoadArt("ver_dot.bmp");

            Text = "DarkEden";
            Icon = Icon.ExtractAssociatedIcon(Assembly.GetExecutingAssembly().Location);
            FormBorderStyle = FormBorderStyle.None;
            AutoScaleMode = AutoScaleMode.None;
            StartPosition = FormStartPosition.CenterScreen;
            ClientSize = m_back.Size;
            BackColor = Color.Black;
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.OptimizedDoubleBuffer, true);

            m_sizes.ShowImageMargin = false;
            m_sizes.ShowCheckMargin = true;
            m_sizes.Font = m_font;
            m_sizes.Renderer = new ToolStripProfessionalRenderer(new DarkMenuColors());
            m_sizes.BackColor = Color.FromArgb(24, 10, 10);

            m_timer.Interval = 50;
            m_timer.Tick += delegate { OnTick(); };
        }

        static Bitmap LoadArt(string name)
        {
            using (Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("Art." + name))
            {
                if (stream == null)
                    throw new FileNotFoundException("Missing embedded art: " + name);

                // a Bitmap made from a stream wants the stream kept open; copy it off
                using (Bitmap loaded = new Bitmap(stream))
                {
                    Bitmap copy = new Bitmap(loaded.Width, loaded.Height, PixelFormat.Format32bppArgb);
                    using (Graphics g = Graphics.FromImage(copy))
                        g.DrawImage(loaded, 0, 0, loaded.Width, loaded.Height);
                    return copy;
                }
            }
        }

        // The pill is a left-to-right fade, so each of its rows is refilled by
        // fading between the clean pixel on either side of what was drawn there.
        static Bitmap CleanPill(Bitmap back)
        {
            for (int y = s_pill.Top; y < s_pill.Bottom; y++)
            {
                Color left = back.GetPixel(s_pill_clean_left, y);
                Color right = back.GetPixel(s_pill_clean_right, y);
                int span = s_pill_clean_right - s_pill_clean_left;

                for (int x = s_pill_clean_left + 1; x < s_pill_clean_right; x++)
                {
                    int t = x - s_pill_clean_left;
                    back.SetPixel(x, y, Color.FromArgb(
                        left.R + (right.R - left.R) * t / span,
                        left.G + (right.G - left.G) * t / span,
                        left.B + (right.B - left.B) * t / span));
                }
            }
            return back;
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            m_engine.Start();
            m_timer.Start();
        }

        void OnTick()
        {
            if (m_engine.Phase == Phase.Restarting)
            {
                m_timer.Stop();
                Close();
                return;
            }

            // /start: only after a clean update, and only the once
            if (m_auto_start && m_engine.Phase != Phase.Working)
            {
                m_auto_start = false;
                if (m_engine.Phase == Phase.Ready && CanStart)
                    StartGame();
            }
            Invalidate();
        }

        bool CanStart
        {
            get
            {
                if (m_launching)
                    return false;

                Phase phase = m_engine.Phase;
                return (phase == Phase.Ready || phase == Phase.Failed)
                    && File.Exists(Path.Combine(m_engine.GameDir, m_engine.Launch.Replace('/', '\\')));
            }
        }

        bool IsLive(Hot hot)
        {
            switch (hot)
            {
                case Hot.Homepage: return m_config.HomepageUrl.Length > 0;
                case Hot.Market: return m_config.MarketUrl.Length > 0;
                case Hot.Start: return CanStart;
                case Hot.Exit: return true;
                case Hot.Fullscreen: return !m_launching;
                case Hot.Resolution: return !m_launching && !m_config.FullScreen;    // fullscreen fills the desktop
            }
            return false;
        }

        static Rectangle RectOf(Hot hot)
        {
            switch (hot)
            {
                case Hot.Homepage: return s_homepage;
                case Hot.Market: return s_market;
                case Hot.Start: return s_start;
                case Hot.Exit: return s_exit;
                case Hot.Fullscreen: return s_fullscreen;
                case Hot.Resolution: return s_resolution;
            }
            return Rectangle.Empty;
        }

        Hot HitTest(Point p)
        {
            foreach (Hot hot in new[] { Hot.Exit, Hot.Start, Hot.Homepage, Hot.Market, Hot.Fullscreen, Hot.Resolution })
            {
                if (RectOf(hot).Contains(p) && IsLive(hot))
                    return hot;
            }
            return Hot.None;
        }

        // ---- drawing
        protected override void OnPaint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            g.TextRenderingHint = TextRenderingHint.ClearTypeGridFit;

            g.DrawImage(m_back, 0, 0, m_back.Width, m_back.Height);

            if (m_hot != Hot.None && IsLive(m_hot) && m_hover.ContainsKey(m_hot))
            {
                Rectangle rect = RectOf(m_hot);
                g.DrawImage(m_hover[m_hot], rect.X, rect.Y + (m_pressed == m_hot ? 1 : 0), rect.Width, rect.Height);
            }

            // GAME START stays dark until there is a game to start
            if (!CanStart)
            {
                using (Brush shade = new SolidBrush(Color.FromArgb(170, 0, 0, 0)))
                    g.FillRectangle(shade, s_start);
            }

            DrawBar(g, s_bar_files, m_engine.FileFraction);
            DrawBar(g, s_bar_total, m_engine.TotalFraction);
            DrawVersion(g, m_engine.Version);
            DrawPanel(g);

            Color status_color = m_engine.Phase == Phase.Failed ? Color.FromArgb(255, 120, 110) : Color.FromArgb(215, 215, 215);
            string status = m_engine.Status;
            string detail = m_engine.Detail;
            if (!string.IsNullOrEmpty(detail))
                status += "   (" + detail + ")";

            TextRenderer.DrawText(g, status, m_font, s_status, status_color,
                TextFormatFlags.HorizontalCenter | TextFormatFlags.VerticalCenter | TextFormatFlags.EndEllipsis | TextFormatFlags.NoPrefix);

            DrawDisplaySettings(g);
        }

        // [o] Fullscreen     1280x720 v
        void DrawDisplaySettings(Graphics g)
        {
            Color lit = Color.FromArgb(255, 235, 235), normal = Color.FromArgb(225, 205, 205), dim = Color.FromArgb(120, 95, 95);
            TextFormatFlags flags = TextFormatFlags.Left | TextFormatFlags.VerticalCenter | TextFormatFlags.NoPrefix | TextFormatFlags.NoPadding;

            int box_x = s_fullscreen.X + 2, box_y = s_fullscreen.Y + (s_fullscreen.Height - s_box) / 2;
            if (m_config.FullScreen)
                g.DrawImage(m_box_on, box_x, box_y, s_box, s_box);
            else
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                using (Brush dot = new SolidBrush(Color.FromArgb(235, 228, 228)))
                    g.FillEllipse(dot, box_x + 1, box_y + 1, s_box - 3, s_box - 3);
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.Default;
            }

            Rectangle label = new Rectangle(box_x + s_box + 5, s_fullscreen.Y, s_fullscreen.Right - box_x - s_box - 5, s_fullscreen.Height);
            TextRenderer.DrawText(g, "Fullscreen", m_small_font, label, m_hot == Hot.Fullscreen ? lit : normal, flags);

            Color size_color = m_config.FullScreen ? dim : (m_hot == Hot.Resolution ? lit : normal);
            string size = m_config.Width + "x" + m_config.Height;
            TextRenderer.DrawText(g, size, m_small_font, s_resolution, size_color, flags);

            // the little arrow that says this one opens
            int ax = s_resolution.X + TextRenderer.MeasureText(g, size, m_small_font, s_resolution.Size, flags).Width + 6;
            int ay = s_resolution.Y + s_resolution.Height / 2 - 1;
            using (Brush arrow = new SolidBrush(size_color))
                g.FillPolygon(arrow, new[] { new Point(ax, ay), new Point(ax + 7, ay), new Point(ax + 3, ay + 4) });
        }

        void ToggleFullscreen()
        {
            m_config.FullScreen = !m_config.FullScreen;
            m_config.Save("FullScreen", m_config.FullScreen ? "1" : "0");
            Invalidate();
        }

        void ShowSizes()
        {
            m_sizes.Items.Clear();

            List<Size> choices = ResolutionFile.Choices();
            Size current = new Size(m_config.Width, m_config.Height);
            if (!choices.Contains(current))
                choices.Add(current);           // typed into the ini by hand; keep it on offer

            foreach (Size choice in choices)
            {
                Size size = choice;
                ToolStripMenuItem item = new ToolStripMenuItem(size.Width + " x " + size.Height);
                item.ForeColor = Color.FromArgb(230, 215, 215);
                item.Checked = size == current;
                item.Click += delegate
                {
                    m_config.Width = size.Width;
                    m_config.Height = size.Height;
                    m_config.Save("Resolution", size.Width + "x" + size.Height);
                    Invalidate();
                };
                m_sizes.Items.Add(item);
            }

            m_sizes.Show(this, new Point(s_resolution.X, s_pill.Bottom + 1));
        }

        sealed class DarkMenuColors : ProfessionalColorTable
        {
            static readonly Color s_back = Color.FromArgb(24, 10, 10), s_pick = Color.FromArgb(110, 18, 18), s_edge = Color.FromArgb(120, 30, 30);

            public override Color ToolStripDropDownBackground { get { return s_back; } }
            public override Color ImageMarginGradientBegin { get { return s_back; } }
            public override Color ImageMarginGradientMiddle { get { return s_back; } }
            public override Color ImageMarginGradientEnd { get { return s_back; } }
            public override Color MenuBorder { get { return s_edge; } }
            public override Color MenuItemBorder { get { return s_edge; } }
            public override Color MenuItemSelected { get { return s_pick; } }
            public override Color MenuItemSelectedGradientBegin { get { return s_pick; } }
            public override Color MenuItemSelectedGradientEnd { get { return s_pick; } }
            public override Color CheckBackground { get { return s_pick; } }
            public override Color CheckSelectedBackground { get { return s_pick; } }
            public override Color CheckPressedBackground { get { return s_pick; } }
        }

        void DrawBar(Graphics g, Rectangle rect, double fraction)
        {
            int filled = (int)Math.Round(rect.Width * Math.Max(0.0, Math.Min(1.0, fraction)));
            if (filled > 0)
                g.DrawImage(m_bar, new Rectangle(rect.X, rect.Y, filled, rect.Height), new Rectangle(0, 0, filled, rect.Height), GraphicsUnit.Pixel);
        }

        // "Ver 1.0.3" in the art's own digits, ending at the art's right edge for it
        void DrawVersion(Graphics g, string version)
        {
            if (string.IsNullOrEmpty(version))
                return;

            List<Bitmap> glyphs = new List<Bitmap>();
            glyphs.Add(m_ver);
            foreach (char c in version)
            {
                Bitmap glyph;
                if (m_digits.TryGetValue(c, out glyph))
                    glyphs.Add(glyph);
            }

            int width = 0;
            foreach (Bitmap glyph in glyphs)
                width += glyph.Width;

            int x = s_version_right.X - width;
            foreach (Bitmap glyph in glyphs)
            {
                g.DrawImage(glyph, x, s_version_right.Y, glyph.Width, glyph.Height);
                x += glyph.Width;
            }
        }

        // Where the old launcher showed a web page: the server's news.txt when it
        // has one, and under it what the updater has been doing.
        void DrawPanel(Graphics g)
        {
            using (Brush fill = new SolidBrush(Color.FromArgb(14, 12, 12)))
                g.FillRectangle(fill, s_panel);

            Rectangle text = Rectangle.Inflate(s_panel, -12, -10);
            string news = m_engine.News;
            string[] log = m_engine.GetLog();

            if (!string.IsNullOrEmpty(news))
            {
                Rectangle top = new Rectangle(text.X, text.Y, text.Width, text.Height - 76);
                TextRenderer.DrawText(g, news.Replace("\r\n", "\n"), m_font, top, Color.FromArgb(220, 210, 200),
                    TextFormatFlags.WordBreak | TextFormatFlags.NoPrefix | TextFormatFlags.EndEllipsis);

                using (Pen rule = new Pen(Color.FromArgb(70, 20, 20)))
                    g.DrawLine(rule, text.X, top.Bottom + 4, text.Right, top.Bottom + 4);

                text = new Rectangle(text.X, top.Bottom + 10, text.Width, text.Bottom - top.Bottom - 10);
            }

            // the newest lines that fit, oldest first
            int line_h = m_small_font.Height + 1;
            int rows = Math.Max(1, text.Height / line_h);
            int first = Math.Max(0, log.Length - rows);

            for (int i = first; i < log.Length; i++)
            {
                Rectangle row = new Rectangle(text.X, text.Y + (i - first) * line_h, text.Width, line_h);
                Color color = log[i].StartsWith("FAILED") ? Color.FromArgb(255, 120, 110) : Color.FromArgb(150, 145, 140);
                TextRenderer.DrawText(g, log[i], m_small_font, row, color,
                    TextFormatFlags.Left | TextFormatFlags.VerticalCenter | TextFormatFlags.EndEllipsis | TextFormatFlags.NoPrefix);
            }
        }

        // /shot: what the window looks like once the update has run, without showing it
        public void SaveShot(string path)
        {
            m_engine.Start();
            for (int wait = 0; m_engine.Phase == Phase.Working && wait < 1200; wait++)
                System.Threading.Thread.Sleep(100);

            using (Bitmap shot = new Bitmap(ClientSize.Width, ClientSize.Height))
            {
                using (Graphics g = Graphics.FromImage(shot))
                    OnPaint(new PaintEventArgs(g, new Rectangle(Point.Empty, ClientSize)));
                shot.Save(path, ImageFormat.Png);
            }
        }

        // ---- mouse
        protected override void OnMouseMove(MouseEventArgs e)
        {
            Hot hot = HitTest(e.Location);
            if (hot != m_hot)
            {
                m_hot = hot;
                Cursor = hot == Hot.None ? Cursors.Default : Cursors.Hand;
                Invalidate();
            }
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            m_hot = m_pressed = Hot.None;
            Invalidate();
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
                return;

            m_pressed = HitTest(e.Location);

            // the title strip moves the window, as the old one's did
            if (m_pressed == Hot.None && s_drag.Contains(e.Location))
            {
                ReleaseCapture();
                SendMessage(Handle, 0xA1 /* WM_NCLBUTTONDOWN */, (IntPtr)2 /* HTCAPTION */, IntPtr.Zero);
            }
            Invalidate();
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            Hot pressed = m_pressed;
            m_pressed = Hot.None;
            Invalidate();

            if (e.Button != MouseButtons.Left || pressed == Hot.None || pressed != HitTest(e.Location))
                return;

            switch (pressed)
            {
                case Hot.Exit: Close(); break;
                case Hot.Start: StartGame(); break;
                case Hot.Homepage: OpenUrl(m_config.HomepageUrl); break;
                case Hot.Market: OpenUrl(m_config.MarketUrl); break;
                case Hot.Fullscreen: ToggleFullscreen(); break;
                case Hot.Resolution: ShowSizes(); break;
            }
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                Close();
            else if (e.KeyCode == Keys.Enter && CanStart)
                StartGame();
        }

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        static extern bool ReleaseCapture();

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        static extern IntPtr SendMessage(IntPtr hwnd, int message, IntPtr wparam, IntPtr lparam);

        static void OpenUrl(string url)
        {
            if (url.StartsWith("http://", StringComparison.OrdinalIgnoreCase) || url.StartsWith("https://", StringComparison.OrdinalIgnoreCase))
            {
                try { Process.Start(url); }
                catch (Exception) { }
            }
        }

        // ---- the point of it all
        //
        // DarkEden.exe NEWSTART0 Futec(ip:port). Without NEWSTART the game would
        // only start the updater again; the digit is the dimension. The game reads
        // the address as text into a short buffer, so a host name is resolved here.
        void StartGame()
        {
            string server = m_engine.Server;
            if (!Config.IsValidServer(server))
            {
                MessageBox.Show(this, "No login server is set.\nPut LoginServer=ip:port in " + Config.FileName + ".", "DarkEden",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            int colon = server.LastIndexOf(':');
            string host = server.Substring(0, colon);
            string port = server.Substring(colon + 1);

            IPAddress address;
            if (!IPAddress.TryParse(host, out address))
            {
                try
                {
                    address = Array.Find(Dns.GetHostAddresses(host), delegate(IPAddress a) { return a.AddressFamily == AddressFamily.InterNetwork; });
                }
                catch (SocketException) { address = null; }

                if (address == null)
                {
                    MessageBox.Show(this, "Cannot find the login server.", "DarkEden", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }

            // The game reads its display settings once, as it starts - and writes the
            // file back as 1280x720 when it exits, which is why this is done every time.
            try
            {
                ResolutionFile.Write(m_engine.GameDir, m_config.Width, m_config.Height, m_config.FullScreen);
            }
            catch (Exception e)
            {
                MessageBox.Show(this, "Could not save the display settings:\n" + e.Message, "DarkEden", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

            try
            {
                ProcessStartInfo info = new ProcessStartInfo(
                    Path.Combine(m_engine.GameDir, m_engine.Launch.Replace('/', '\\')),
                    "NEWSTART0 Futec(" + address + ":" + port + ")");
                info.WorkingDirectory = m_engine.GameDir;     // every data path in the game is relative
                info.UseShellExecute = false;
                Process.Start(info);
            }
            catch (Exception e)
            {
                MessageBox.Show(this, "Could not start the game:\n" + e.Message, "DarkEden", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            m_launching = true;
            Close();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                m_timer.Dispose();
                m_sizes.Dispose();
                m_font.Dispose();
                m_small_font.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
