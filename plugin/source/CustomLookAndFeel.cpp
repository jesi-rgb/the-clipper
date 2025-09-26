#include "TheClipper/CustomLookAndFeel.h"
#include "BinaryData.h"

namespace audio_plugin {

CustomLookAndFeel::CustomLookAndFeel() {
  setColour(juce::ResizableWindow::backgroundColourId, backgroundColor);
  setColour(juce::Slider::backgroundColourId, backgroundColor);
  setColour(juce::Slider::thumbColourId, primaryColor);
  setColour(juce::Slider::trackColourId, secondaryColor);
  setColour(juce::ComboBox::backgroundColourId, backgroundColor);
  setColour(juce::ComboBox::outlineColourId, accentColor);
  setColour(juce::Label::textColourId, textColor);
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                         int x,
                                         int y,
                                         int width,
                                         int height,
                                         float sliderPos,
                                         float rotaryStartAngle,
                                         float rotaryEndAngle,
                                         juce::Slider&) {
  auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);
  auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
  auto toAngle =
      rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
  auto centre = bounds.getCentre();

  // Draw outer glow
  for (float i = 0; i < 5; ++i) {
    g.setColour(primaryColor.withAlpha(0.1f - i * 0.02f));
    g.drawEllipse(centre.x - radius - i, centre.y - radius - i,
                  (radius + i) * 2, (radius + i) * 2, 2.0f);
  }

  // Draw main track
  juce::Path backgroundTrack;
  backgroundTrack.addArc(centre.x - radius, centre.y - radius, radius * 2.0f,
                         radius * 2.0f, rotaryStartAngle, rotaryEndAngle, true);
  g.setColour(backgroundColor.brighter(0.3f));
  g.strokePath(backgroundTrack,
               juce::PathStrokeType(8.0f, juce::PathStrokeType::curved));

  // Draw active track with gradient
  if (sliderPos > 0.0f) {
    juce::Path activeTrack;
    activeTrack.addArc(centre.x - radius, centre.y - radius, radius * 2.0f,
                       radius * 2.0f, rotaryStartAngle, toAngle, true);

    juce::ColourGradient gradient(primaryColor, centre.x, centre.y,
                                  secondaryColor, centre.x + radius,
                                  centre.y + radius, false);
    g.setGradientFill(gradient);
    g.strokePath(activeTrack,
                 juce::PathStrokeType(8.0f, juce::PathStrokeType::curved));
  }

  // Draw neon thumb
  auto thumbPoint = centre.getPointOnCircumference(radius - 4, toAngle);

  // Thumb glow
  for (float i = 0; i < 3; ++i) {
    g.setColour(accentColor.withAlpha(0.3f - i * 0.1f));
    g.fillEllipse(thumbPoint.x - (12 + i * 2), thumbPoint.y - (12 + i * 2),
                  (12 + i * 2) * 2, (12 + i * 2) * 2);
  }

  // Thumb core
  g.setColour(accentColor);
  g.fillEllipse(thumbPoint.x - 8, thumbPoint.y - 8, 16, 16);
  g.setColour(textColor);
  g.fillEllipse(thumbPoint.x - 4, thumbPoint.y - 4, 8, 8);
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g,
                                         int x,
                                         int y,
                                         int width,
                                         int height,
                                         float sliderPos,
                                         float,
                                         float,
                                         juce::Slider::SliderStyle style,
                                         juce::Slider&) {
  float xf = static_cast<float>(x);
  float yf = static_cast<float>(y);
  float wf = static_cast<float>(width);
  float hf = static_cast<float>(height);

  auto trackBounds = juce::Rectangle<float>(xf, yf, wf, hf).reduced(10);

  if (style == juce::Slider::LinearVertical) {
    trackBounds = trackBounds.withSizeKeepingCentre(12, hf - 20);

    // Draw track background with neon edge
    g.setColour(backgroundColor.brighter(0.2f));
    g.fillRoundedRectangle(trackBounds, 6.0f);

    // Neon outline
    g.setColour(primaryColor.withAlpha(0.8f));
    g.drawRoundedRectangle(trackBounds, 6.0f, 2.0f);

    // Draw filled portion with gradient
    auto normalizedPos =
        (sliderPos - trackBounds.getY()) / trackBounds.getHeight();

    normalizedPos = 1 - juce::jlimit(0.0f, 1.0f, normalizedPos);
    std::cout << "normalizedPos: " << normalizedPos << std::endl;
    std::cout << "sliderPos: " << sliderPos << std::endl;

    auto filledHeight = normalizedPos * trackBounds.getHeight();
    auto filledBounds =
        trackBounds.withTop(trackBounds.getBottom() - filledHeight);

    juce::ColourGradient gradient(
        secondaryColor, filledBounds.getCentreX(), filledBounds.getBottom(),
        primaryColor, filledBounds.getCentreX(), filledBounds.getY(), false);
    g.setGradientFill(gradient);
    g.fillRoundedRectangle(filledBounds, 6.0f);

    // Draw pulsating thumb
    auto thumbY =
        trackBounds.getBottom() - normalizedPos * trackBounds.getHeight();
    auto thumbBounds = juce::Rectangle<float>(trackBounds.getCentreX() - 15,
                                              thumbY - 8, 30, 16);

    // Thumb glow
    for (float i = 0; i < 3; ++i) {
      g.setColour(accentColor.withAlpha(0.4f - i * 0.1f));
      auto glowBounds = thumbBounds.expanded(i * 2);
      g.fillRoundedRectangle(glowBounds, 8.0f);
    }

    // Thumb
    // g.setColour(accentColor);
    // g.fillRoundedRectangle(thumbBounds, 8.0f);
    // g.setColour(textColor);
    // g.fillRoundedRectangle(thumbBounds.reduced(4), 4.0f);
  }
}

void CustomLookAndFeel::drawComboBox(juce::Graphics& g,
                                     int width,
                                     int height,
                                     bool isButtonDown,
                                     int buttonX,
                                     int buttonY,
                                     int buttonW,
                                     int buttonH,
                                     juce::ComboBox&) {
  auto bounds = juce::Rectangle<int>(0, 0, width, height).toFloat().reduced(2);

  // Background with neon border
  g.setColour(backgroundColor.brighter(0.1f));
  g.fillRoundedRectangle(bounds, 8.0f);

  // Animated border
  juce::ColourGradient borderGradient(primaryColor, 0, 0, secondaryColor,
                                      static_cast<float>(width),
                                      static_cast<float>(height), false);
  g.setGradientFill(borderGradient);
  g.drawRoundedRectangle(bounds, 8.0f, 2.0f);

  // Arrow
  auto arrowBounds = juce::Rectangle<float>(static_cast<float>(buttonX),
                                            static_cast<float>(buttonY),
                                            static_cast<float>(buttonW),
                                            static_cast<float>(buttonH))
                         .reduced(6);
  juce::Path arrow;
  arrow.addTriangle(arrowBounds.getCentreX() - 6, arrowBounds.getCentreY() - 3,
                    arrowBounds.getCentreX() + 6, arrowBounds.getCentreY() - 3,
                    arrowBounds.getCentreX(), arrowBounds.getCentreY() + 3);

  g.setColour(isButtonDown ? secondaryColor : accentColor);
  g.fillPath(arrow);
}

void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label) {
  auto bounds = label.getLocalBounds().toFloat();
  g.setFont(departureMono.withPointHeight(15.0f));

  // Text shadow/glow effect
  g.setColour(primaryColor.withAlpha(0.3f));
  g.drawText(label.getText(), bounds.translated(1, 1),
             label.getJustificationType(), true);
  g.drawText(label.getText(), bounds.translated(-1, -1),
             label.getJustificationType(), true);

  // Main text
  g.setColour(label.findColour(juce::Label::textColourId));
  g.drawText(label.getText(), bounds, label.getJustificationType(), true);
}

}  // namespace audio_plugin
