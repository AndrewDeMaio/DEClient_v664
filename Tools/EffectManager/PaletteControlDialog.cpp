#include "PaletteControlDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QColor>
#include <QtGlobal>
#include <numeric>

PaletteControlDialog::PaletteControlDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Palette Control");
    setMinimumWidth(350);
    setupUi();
    connect(m_redSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
    connect(m_greenSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
    connect(m_blueSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
    connect(m_brightnessSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
    connect(m_contrastSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
    connect(m_hueSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
    connect(m_saturationSlider, &QSlider::valueChanged, this, &PaletteControlDialog::adjustPalette);
}

void PaletteControlDialog::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();

    m_redSlider = new QSlider(Qt::Horizontal);
    m_greenSlider = new QSlider(Qt::Horizontal);
    m_blueSlider = new QSlider(Qt::Horizontal);
    m_brightnessSlider = new QSlider(Qt::Horizontal);
    m_contrastSlider = new QSlider(Qt::Horizontal);
    m_hueSlider = new QSlider(Qt::Horizontal);
    m_saturationSlider = new QSlider(Qt::Horizontal);

    m_redSlider->setRange(-100, 100);
    m_greenSlider->setRange(-100, 100);
    m_blueSlider->setRange(-100, 100);
    m_brightnessSlider->setRange(-100, 100);
    m_contrastSlider->setRange(-100, 100);
    m_hueSlider->setRange(-180, 180); // Rotação de -180 a +180 graus
    m_saturationSlider->setRange(-100, 100);

    m_redValueLabel = new QLabel("0");
    m_greenValueLabel = new QLabel("0");
    m_blueValueLabel = new QLabel("0");
    m_brightnessValueLabel = new QLabel("0");
    m_contrastValueLabel = new QLabel("0");
    m_hueValueLabel = new QLabel("0");
    m_saturationValueLabel = new QLabel("0");

    auto createSliderRow = [&](const QString& name, QSlider* slider, QLabel* label) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        rowLayout->addWidget(slider);
        rowLayout->addWidget(label);
        formLayout->addRow(name, rowLayout);
    };

    createSliderRow("Red:", m_redSlider, m_redValueLabel);
    createSliderRow("Green:", m_greenSlider, m_greenValueLabel);
    createSliderRow("Blue:", m_blueSlider, m_blueValueLabel);
    createSliderRow("Brightness:", m_brightnessSlider, m_brightnessValueLabel);
    createSliderRow("Contrast:", m_contrastSlider, m_contrastValueLabel);
    createSliderRow("Hue:", m_hueSlider, m_hueValueLabel);
    createSliderRow("Saturation:", m_saturationSlider, m_saturationValueLabel);

    QGroupBox* controlGroup = new QGroupBox("Adjustments");
    controlGroup->setLayout(formLayout);
    
    QPushButton* resetButton = new QPushButton("Reset");
    connect(resetButton, &QPushButton::clicked, this, &PaletteControlDialog::onResetClicked);

    mainLayout->addWidget(controlGroup);
    mainLayout->addWidget(resetButton);
}

void PaletteControlDialog::setPalette(const Palette& originalPalette)
{
    m_originalPalette = originalPalette;
    m_adjustedPalette = originalPalette;

    m_redSlider->blockSignals(true);
    m_greenSlider->blockSignals(true);
    m_blueSlider->blockSignals(true);
    m_brightnessSlider->blockSignals(true);
    m_contrastSlider->blockSignals(true);
    m_hueSlider->blockSignals(true);
    m_saturationSlider->blockSignals(true);

    m_redSlider->setValue(0);
    m_greenSlider->setValue(0);
    m_blueSlider->setValue(0);
    m_brightnessSlider->setValue(0);
    m_contrastSlider->setValue(0);
    m_hueSlider->setValue(0);
    m_saturationSlider->setValue(0);

    m_redSlider->blockSignals(false);
    m_greenSlider->blockSignals(false);
    m_blueSlider->blockSignals(false);
    m_brightnessSlider->blockSignals(false);
    m_contrastSlider->blockSignals(false);
    m_hueSlider->blockSignals(false);
    m_saturationSlider->blockSignals(false);

    updateLabels();
}

void PaletteControlDialog::reconfigure(const Palette& originalPalette, const Palette& adjustedPalette)
{
    m_originalPalette = originalPalette;
    m_adjustedPalette = adjustedPalette;
    calculateAndSetSliders(originalPalette, adjustedPalette);
}

void PaletteControlDialog::onResetClicked()
{
    setPalette(m_originalPalette);
    emit paletteReset();
}

void PaletteControlDialog::updateLabels()
{
    m_redValueLabel->setText(QString::number(m_redSlider->value()));
    m_greenValueLabel->setText(QString::number(m_greenSlider->value()));
    m_blueValueLabel->setText(QString::number(m_blueSlider->value()));
    m_brightnessValueLabel->setText(QString::number(m_brightnessSlider->value()));
    m_contrastValueLabel->setText(QString::number(m_contrastSlider->value()));
    m_hueValueLabel->setText(QString::number(m_hueSlider->value()));
    m_saturationValueLabel->setText(QString::number(m_saturationSlider->value()));
}

void PaletteControlDialog::adjustPalette()
{
    if (m_originalPalette.isEmpty()) return;

    updateLabels();

    m_adjustedPalette = m_originalPalette;

    int r_adj = m_redSlider->value();
    int g_adj = m_greenSlider->value();
    int b_adj = m_blueSlider->value();
    int br_adj = m_brightnessSlider->value();
    int contrast_adj = m_contrastSlider->value();
    int hue_adj = m_hueSlider->value();
    int sat_adj = m_saturationSlider->value();

    for (int i = 0; i < m_adjustedPalette.size(); ++i)
    {
        quint16 originalColor565 = m_originalPalette[i];

        // 1. Decodifica BGR 5-6-5 para QColor (RGB 8-8-8)
        int r8 = ((originalColor565 & 0xF800) >> 11) * 255 / 31;
        int g8 = ((originalColor565 & 0x07E0) >> 5)  * 255 / 63;
        int b8 = (originalColor565 & 0x001F)         * 255 / 31;
        QColor color(r8, g8, b8);

        // 2. Aplica ajustes RGB (Brilho, Contraste, Cor)
        // Fator de contraste: de 0.0 (cinza) a 2.0 (alto contraste)
        qreal contrastFactor = (100.0 + contrast_adj) / 100.0;
        r8 = qBound(0, (int)(contrastFactor * (r8 - 128) + 128), 255);
        g8 = qBound(0, (int)(contrastFactor * (g8 - 128) + 128), 255);
        b8 = qBound(0, (int)(contrastFactor * (b8 - 128) + 128), 255);

        int brightness = (br_adj * 255) / 100;
        r8 = qBound(0, r8 + brightness, 255);
        g8 = qBound(0, g8 + brightness, 255);
        b8 = qBound(0, b8 + brightness, 255);

        r8 = qBound(0, r8 + ((r_adj * 255) / 100), 255);
        g8 = qBound(0, g8 + ((g_adj * 255) / 100), 255);
        b8 = qBound(0, b8 + ((b_adj * 255) / 100), 255);
        color.setRgb(r8, g8, b8);

        // 3. Aplica ajustes HSL (Matiz, Saturação)
        int hue = color.hue();
        int sat = color.saturation();
        int lightness = color.lightness();

        hue = (hue + hue_adj + 360) % 360;
        sat = qBound(0, sat + (sat_adj * 255 / 100), 255);
        
        color.setHsl(hue, sat, lightness);
        
        // 4. Converte de volta para BGR 5-6-5
        int r5 = (color.red() * 31) / 255;
        int g6 = (color.green() * 63) / 255;
        int b5 = (color.blue() * 31) / 255;

        m_adjustedPalette[i] = (r5 << 11) | (g6 << 5) | b5;
    }

    emit paletteAdjusted(m_adjustedPalette);
}

void PaletteControlDialog::calculateAndSetSliders(const Palette& p1, const Palette& p2)
{
    if (p1.isEmpty() || p2.isEmpty() || p1.size() != p2.size()) {
        setPalette(p1);
        return;
    }

    long long r_diff_total = 0, g_diff_total = 0, b_diff_total = 0;
    for(int i = 0; i < p1.size(); ++i) {
        quint16 c1 = p1[i];
        quint16 c2 = p2[i];

        int r1 = ((c1 & 0xF800) >> 11); int g1 = ((c1 & 0x07E0) >> 5); int b1 = (c1 & 0x001F);
        int r2 = ((c2 & 0xF800) >> 11); int g2 = ((c2 & 0x07E0) >> 5); int b2 = (c2 & 0x001F);

        r_diff_total += (r2 - r1);
        g_diff_total += (g2 - g1);
        b_diff_total += (b2 - b1);
    }

    int r_slider = qBound(-100, static_cast<int>((r_diff_total * 100) / (p1.size() * 31)), 100);
    int g_slider = qBound(-100, static_cast<int>((g_diff_total * 100) / (p1.size() * 63)), 100);
    int b_slider = qBound(-100, static_cast<int>((b_diff_total * 100) / (p1.size() * 31)), 100);

    m_redSlider->blockSignals(true);
    m_greenSlider->blockSignals(true);
    m_blueSlider->blockSignals(true);
    m_brightnessSlider->blockSignals(true);
    m_contrastSlider->blockSignals(true);
    m_hueSlider->blockSignals(true);
    m_saturationSlider->blockSignals(true);

    m_redSlider->setValue(r_slider);
    m_greenSlider->setValue(g_slider);
    m_blueSlider->setValue(b_slider);
    // É muito complexo reverter HSL e Contraste, então os resetamos
    m_brightnessSlider->setValue(0);
    m_contrastSlider->setValue(0);
    m_hueSlider->setValue(0);
    m_saturationSlider->setValue(0);

    m_redSlider->blockSignals(false);
    m_greenSlider->blockSignals(false);
    m_blueSlider->blockSignals(false);
    m_brightnessSlider->blockSignals(false);
    m_contrastSlider->blockSignals(false);
    m_hueSlider->blockSignals(false);
    m_saturationSlider->blockSignals(false);

    updateLabels();
}