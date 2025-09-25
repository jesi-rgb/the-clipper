#include "TheClipper/PluginEditor.h"
#include "TheClipper/PluginProcessor.h"

namespace audio_plugin {
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
  inputGainSlider.setSliderStyle(juce::Slider::Rotary);
  inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
  addAndMakeVisible(inputGainSlider);
  inputGainLabel.setText("Input Gain", juce::dontSendNotification);
  inputGainLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(inputGainLabel);
  inputGainAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
          processorRef.getValueTreeState(), "inputGain", inputGainSlider);

  thresholdSlider.setSliderStyle(juce::Slider::Rotary);
  thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
  addAndMakeVisible(thresholdSlider);
  thresholdLabel.setText("Threshold", juce::dontSendNotification);
  thresholdLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(thresholdLabel);
  thresholdAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
          processorRef.getValueTreeState(), "threshold", thresholdSlider);

  clippingModeCombo.addItem("Hard", 1);
  clippingModeCombo.addItem("Soft", 2);
  addAndMakeVisible(clippingModeCombo);
  clippingModeLabel.setText("Clipping Mode", juce::dontSendNotification);
  clippingModeLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(clippingModeLabel);
  clippingModeAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
          processorRef.getValueTreeState(), "clippingMode", clippingModeCombo);

  saturationSlider.setSliderStyle(juce::Slider::Rotary);
  saturationSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
  addAndMakeVisible(saturationSlider);
  saturationLabel.setText("Saturation", juce::dontSendNotification);
  saturationLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(saturationLabel);
  saturationAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
          processorRef.getValueTreeState(), "saturation", saturationSlider);

  setSize(480, 320);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::darkgrey);

  g.setColour(juce::Colours::white);
  g.setFont(24.0f);
  g.drawFittedText("The Clipper by askldjfha", juce::Rectangle<int>(0, 10, getWidth(), 30),
                   juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized() {
  auto bounds = getLocalBounds();
  bounds.removeFromTop(50);

  auto controlArea = bounds.reduced(20);
  int controlWidth = controlArea.getWidth() / 4;
  // int controlHeight = controlArea.getHeight();

  auto inputGainArea = controlArea.removeFromLeft(controlWidth);
  inputGainLabel.setBounds(inputGainArea.removeFromBottom(20));
  inputGainSlider.setBounds(inputGainArea);

  auto thresholdArea = controlArea.removeFromLeft(controlWidth);
  thresholdLabel.setBounds(thresholdArea.removeFromBottom(20));
  thresholdSlider.setBounds(thresholdArea);

  auto clippingModeArea = controlArea.removeFromLeft(controlWidth);
  clippingModeLabel.setBounds(clippingModeArea.removeFromBottom(20));
  clippingModeCombo.setBounds(
      clippingModeArea.removeFromBottom(30).reduced(10, 0));

  auto saturationArea = controlArea;
  saturationLabel.setBounds(saturationArea.removeFromBottom(20));
  saturationSlider.setBounds(saturationArea);
}
}  // namespace audio_plugin
