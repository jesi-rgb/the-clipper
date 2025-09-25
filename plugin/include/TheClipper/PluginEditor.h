#pragma once

#include "PluginProcessor.h"

namespace audio_plugin {

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
  ~AudioPluginAudioProcessorEditor() override;

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  AudioPluginAudioProcessor& processorRef;

  juce::Slider inputGainSlider;
  juce::Label inputGainLabel;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;

  juce::Slider thresholdSlider;
  juce::Label thresholdLabel;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;

  juce::ComboBox clippingModeCombo;
  juce::Label clippingModeLabel;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> clippingModeAttachment;

  juce::Slider saturationSlider;
  juce::Label saturationLabel;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> saturationAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
}  // namespace audio_plugin
