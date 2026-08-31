#pragma once

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include "PalettePack.h"

class PaletteControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaletteControlDialog(QWidget* parent = nullptr);

    void setPalette(const Palette& originalPalette);
    void reconfigure(const Palette& originalPalette, const Palette& adjustedPalette);

signals:
    void paletteAdjusted(const Palette& newPalette);
    void paletteReset();

private slots:
    void adjustPalette();
    void onResetClicked();

private:
    void setupUi();
    void updateLabels();
    void calculateAndSetSliders(const Palette& p1, const Palette& p2);

    Palette m_originalPalette;
    Palette m_adjustedPalette;

    // Controles da UI
    QSlider* m_redSlider;
    QSlider* m_greenSlider;
    QSlider* m_blueSlider;
    QSlider* m_brightnessSlider;
    QSlider* m_contrastSlider;     // Novo
    QSlider* m_hueSlider;          // Novo
    QSlider* m_saturationSlider;   // Novo

    QLabel* m_redValueLabel;
    QLabel* m_greenValueLabel;
    QLabel* m_blueValueLabel;
    QLabel* m_brightnessValueLabel;
    QLabel* m_contrastValueLabel;   // Novo
    QLabel* m_hueValueLabel;        // Novo
    QLabel* m_saturationValueLabel; // Novo
};