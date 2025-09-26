#pragma once

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryData.h"

namespace audio_plugin {

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
  CustomLookAndFeel();

  void drawRotarySlider(juce::Graphics& g,
                        int x,
                        int y,
                        int width,
                        int height,
                        float sliderPos,
                        float rotaryStartAngle,
                        float rotaryEndAngle,
                        juce::Slider& slider) override;

  void drawLinearSlider(juce::Graphics& g,
                        int x,
                        int y,
                        int width,
                        int height,
                        float sliderPos,
                        float minSliderPos,
                        float maxSliderPos,
                        juce::Slider::SliderStyle style,
                        juce::Slider& slider) override;

  void drawComboBox(juce::Graphics& g,
                    int width,
                    int height,
                    bool isButtonDown,
                    int buttonX,
                    int buttonY,
                    int buttonW,
                    int buttonH,
                    juce::ComboBox& box) override;

  void drawLabel(juce::Graphics& g, juce::Label& label) override;

  juce::Font departureMono{juce::FontOptions(juce::Typeface::createSystemTypefaceFor(
          BinaryData::DepartureMonoRegular_otf,
          BinaryData::DepartureMonoRegular_otfSize))};

private:
  juce::Colour primaryColor{0xff00ff88};     // Neon green
  juce::Colour secondaryColor{0xffff0088};   // Neon pink
  juce::Colour accentColor{0xff0088ff};      // Neon blue
  juce::Colour backgroundColor{0xff1a1a1a};  // Very dark gray
  juce::Colour textColor{0xffffffff};        // White
};

}  // namespace audio_plugin
