#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"
#include "BinaryData.h"
#include "CustomLookAndFeel.h"

namespace audio_plugin {

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
  ~AudioPluginAudioProcessorEditor() override;

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  AudioPluginAudioProcessor& processorRef;
  using APVTS = juce::AudioProcessorValueTreeState;

  juce::Slider inputGainSlider;
  juce::Label inputGainLabel;
  std::unique_ptr<APVTS::SliderAttachment> inputGainAttachment;

  juce::Slider thresholdSlider;
  juce::Label thresholdLabel;
  std::unique_ptr<APVTS::SliderAttachment> thresholdAttachment;

  juce::ComboBox clippingModeCombo;
  juce::Label clippingModeLabel;
  std::unique_ptr<APVTS::ComboBoxAttachment> clippingModeAttachment;

  juce::Slider saturationSlider;
  juce::Label saturationLabel;
  std::unique_ptr<APVTS::SliderAttachment> saturationAttachment;

  juce::Font departureMono{juce::FontOptions(juce::Typeface::createSystemTypefaceFor(
          BinaryData::DepartureMonoRegular_otf,
          BinaryData::DepartureMonoRegular_otfSize))};



  CustomLookAndFeel lookAndFeel{};

  
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
}  // namespace audio_plugin
