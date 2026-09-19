// present.hlsl - pixel shaders for the GPU present layer (CD3D9Scaler).
//
// Both shaders are ps_2_0 so they run on any D3D9-class GPU and work with
// the fixed-function pretransformed quad the presenter already draws.
// Rebuild the headers with build_shaders.bat after editing.
//
// Constants (set by CD3D9Scaler):
//   c0 = (texW, texH, 1/texW, 1/texH)      size of the texture being sampled
//   c1 = (texelsPerPixelX, texelsPerPixelY, sharpness 0..1, unused)

sampler2D s0 : register(s0);
float4    c0 : register(c0);
float4    c1 : register(c1);

// Sharp bilinear ("pixel AA"): each texel is shown as a solid block with a
// one-screen-pixel-wide blend at its edges, whatever the scale ratio. Avoids
// the softness of plain bilinear and the shimmer of nearest at 1.5x. When
// the ratio is >= 1 texel per pixel (downscaling) it degrades to bilinear.
float4 PS_Sharp(float2 uv : TEXCOORD0) : COLOR
{
    float2 pix = uv * c0.xy - 0.5;          // texel space, 0 = centre of texel 0
    float2 i   = floor(pix);
    float2 f   = pix - i;                   // 0 at centre of texel i, 1 at centre of i+1
    float2 w   = min(c1.xy, 1.0);           // blend width in texels = one screen pixel
    float2 t   = saturate((f - 0.5) / w + 0.5);
    float2 uv2 = (i + 0.5 + t) * c0.zw;     // hardware bilinear does the blend
    return tex2D(s0, uv2);
}

// ---------------------------------------------------------------------------
// xBR level 2 (Hyllian) - edge-directed reconstruction of pixel art. Needs
// ps_3_0, which in turn needs a vertex shader, so it uses VS_Pass with
// clip-space positions instead of the pretransformed quad.
// ---------------------------------------------------------------------------

struct VS_IN  { float3 pos : POSITION; float2 uv : TEXCOORD0; };
struct VS_OUT { float4 pos : POSITION; float2 uv : TEXCOORD0; };

VS_OUT VS_Pass(VS_IN i)
{
    VS_OUT o;
    o.pos = float4(i.pos, 1.0);
    o.uv  = i.uv;
    return o;
}

static const float  XBR_EQ_THRESHOLD    = 15.0 / 255.0;
static const float  XBR_LV2_COEFFICIENT = 2.0;
static const float3 XBR_Y               = float3(0.299, 0.587, 0.114);

float4 xdf(float4 A, float4 B) { return abs(A - B); }
bool4  xeq(float4 A, float4 B) { return (xdf(A, B) < XBR_EQ_THRESHOLD.xxxx); }
float4 xwd(float4 a, float4 b, float4 c, float4 d, float4 e, float4 f, float4 g, float4 h)
{
    return xdf(a, b) + xdf(a, c) + xdf(d, e) + xdf(d, f) + 4.0 * xdf(g, h);
}

float4 PS_Xbr(float2 uv : TEXCOORD0) : COLOR
{
    const float4 Ao = float4( 1.0, -1.0, -1.0,  1.0);
    const float4 Bo = float4( 1.0,  1.0, -1.0, -1.0);
    const float4 Co = float4( 1.5,  0.5, -0.5,  0.5);
    const float4 Ax = float4( 1.0, -1.0, -1.0,  1.0);
    const float4 Bx = float4( 0.5,  2.0, -0.5, -2.0);
    const float4 Cx = float4( 1.0,  1.0, -0.5,  0.0);
    const float4 Ay = float4( 1.0, -1.0, -1.0,  1.0);
    const float4 By = float4( 2.0,  0.5, -2.0, -0.5);
    const float4 Cy = float4( 2.0,  0.0, -1.0,  0.5);

    float2 fp = frac(uv * c0.xy);
    float2 dx = float2(c0.z, 0.0);
    float2 dy = float2(0.0, c0.w);

    float3 A1 = tex2D(s0, uv - dx - 2.0*dy).rgb;
    float3 B1 = tex2D(s0, uv      - 2.0*dy).rgb;
    float3 C1 = tex2D(s0, uv + dx - 2.0*dy).rgb;
    float3 A0 = tex2D(s0, uv - 2.0*dx - dy).rgb;
    float3 A  = tex2D(s0, uv - dx - dy).rgb;
    float3 B  = tex2D(s0, uv      - dy).rgb;
    float3 C  = tex2D(s0, uv + dx - dy).rgb;
    float3 C4 = tex2D(s0, uv + 2.0*dx - dy).rgb;
    float3 D0 = tex2D(s0, uv - 2.0*dx).rgb;
    float3 D  = tex2D(s0, uv - dx).rgb;
    float3 E  = tex2D(s0, uv).rgb;
    float3 F  = tex2D(s0, uv + dx).rgb;
    float3 F4 = tex2D(s0, uv + 2.0*dx).rgb;
    float3 G0 = tex2D(s0, uv - 2.0*dx + dy).rgb;
    float3 G  = tex2D(s0, uv - dx + dy).rgb;
    float3 H  = tex2D(s0, uv      + dy).rgb;
    float3 I  = tex2D(s0, uv + dx + dy).rgb;
    float3 I4 = tex2D(s0, uv + 2.0*dx + dy).rgb;
    float3 G5 = tex2D(s0, uv - dx + 2.0*dy).rgb;
    float3 H5 = tex2D(s0, uv      + 2.0*dy).rgb;
    float3 I5 = tex2D(s0, uv + dx + 2.0*dy).rgb;

    float4 b  = float4(dot(B, XBR_Y), dot(D, XBR_Y), dot(H, XBR_Y), dot(F, XBR_Y));
    float4 c  = float4(dot(C, XBR_Y), dot(A, XBR_Y), dot(G, XBR_Y), dot(I, XBR_Y));
    float4 d  = b.yzwx;
    float4 e  = dot(E, XBR_Y).xxxx;
    float4 f  = b.wxyz;
    float4 g  = c.zwxy;
    float4 h  = b.zwxy;
    float4 i  = c.wxyz;
    float4 i4 = float4(dot(I4, XBR_Y), dot(C1, XBR_Y), dot(A0, XBR_Y), dot(G5, XBR_Y));
    float4 i5 = float4(dot(I5, XBR_Y), dot(C4, XBR_Y), dot(A1, XBR_Y), dot(G0, XBR_Y));
    float4 h5 = float4(dot(H5, XBR_Y), dot(F4, XBR_Y), dot(B1, XBR_Y), dot(D0, XBR_Y));
    float4 f4 = h5.yzwx;

    bool4 fx      = (Ao * fp.y + Bo * fp.x > Co);
    bool4 fx_left = (Ax * fp.y + Bx * fp.x > Cx);
    bool4 fx_up   = (Ay * fp.y + By * fp.x > Cy);

    bool4 lv0 = !xeq(e, f) && !xeq(e, h);
    bool4 lv1 = (!xeq(f, b) && !xeq(f, c)) || (!xeq(h, d) && !xeq(h, g)) ||
                (xeq(e, i) && ((!xeq(f, f4) && !xeq(f, i4)) || (!xeq(h, h5) && !xeq(h, i5)))) ||
                xeq(e, g) || xeq(e, c);
    bool4 lv2l = !xeq(e, g) && !xeq(d, g);
    bool4 lv2u = !xeq(e, c) && !xeq(b, c);

    bool4 edr      = (xwd(e, c, g, i, h5, f4, h, f) < xwd(h, d, i5, f, i4, b, e, i)) && lv1 && lv0;
    bool4 edr_left = ((XBR_LV2_COEFFICIENT * xdf(f, g)) <= xdf(h, c)) && lv2l && edr;
    bool4 edr_up   = (xdf(f, g) >= (XBR_LV2_COEFFICIENT * xdf(h, c))) && lv2u && edr;

    bool4 nc = edr && (fx || (edr_left && fx_left) || (edr_up && fx_up));
    bool4 px = (xdf(e, f) <= xdf(e, h));

    float3 res = E;
    if (nc.w) res = px.w ? H : D;
    if (nc.z) res = px.z ? D : B;
    if (nc.y) res = px.y ? B : F;
    if (nc.x) res = px.x ? F : H;
    return float4(res, 1.0);
}

// Contrast-adaptive sharpening (AMD CAS, single pass, cross taps). Runs 1:1
// on the already-scaled frame. c1.z = strength 0..1.
float4 PS_Cas(float2 uv : TEXCOORD0) : COLOR
{
    float2 px = c0.zw;
    float3 n = tex2D(s0, uv + float2(0.0, -px.y)).rgb;
    float3 w = tex2D(s0, uv + float2(-px.x, 0.0)).rgb;
    float3 c = tex2D(s0, uv).rgb;
    float3 e = tex2D(s0, uv + float2(px.x, 0.0)).rgb;
    float3 s = tex2D(s0, uv + float2(0.0, px.y)).rgb;

    float3 mn = min(min(min(n, w), min(c, e)), s);
    float3 mx = max(max(max(n, w), max(c, e)), s);
    float3 rcpM = 1.0 / max(mx, 0.0001);
    float3 amp  = sqrt(saturate(min(mn, 2.0 - mx) * rcpM));
    float  peak = -1.0 / (8.0 - 3.0 * saturate(c1.z));   // -1/8 .. -1/5
    float3 wgt  = amp * peak;
    float3 col  = (wgt * (n + w + e + s) + c) / (4.0 * wgt + 1.0);
    return float4(saturate(col), 1.0);
}
