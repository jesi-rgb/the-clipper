#include "TheClipper/CustomLookAndFeel.h"
#include "TheClipper/Graphics.h"
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
  using namespace graphics;
  
  auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);
  auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
  auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
  auto centre = bounds.getCentre();

  Circle(centre, radius)
    .glow(15, primaryColor, 0.1f, 0.02f)
    .render(g);

  Arc(centre, radius, rotaryStartAngle, rotaryEndAngle)
    .stroke(backgroundColor.brighter(0.3f), 8.0f)
    .render(g);

  if (sliderPos > 0.0f) {
    juce::ColourGradient gradient(primaryColor, centre.x, centre.y,
                                  secondaryColor, centre.x + radius,
                                  centre.y + radius, false);
    Arc(centre, radius, rotaryStartAngle, toAngle)
      .stroke(gradient, 8.0f)
      .render(g);
  }

  auto thumbPoint = centre.getPointOnCircumference(radius - 4, toAngle);
  
  Circle(thumbPoint, 12)
    .fill(accentColor)
    .glow(3, accentColor, 0.3f, 0.1f)
    .render(g);
    
  Circle(thumbPoint, 4)
    .fill(textColor)
    .render(g);
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
    using namespace graphics;
    
    trackBounds = trackBounds.withSizeKeepingCentre(12, hf - 20);

    RoundedRect(trackBounds, 6.0f)
      .fill(backgroundColor.brighter(0.2f))
      .stroke(primaryColor.withAlpha(0.8f), 2.0f)
      .render(g);

    auto normalizedPos = (sliderPos - trackBounds.getY()) / trackBounds.getHeight();
    normalizedPos = 1 - juce::jlimit(0.0f, 1.0f, normalizedPos);

    auto filledHeight = normalizedPos * trackBounds.getHeight();
    auto filledBounds = trackBounds.withTop(trackBounds.getBottom() - filledHeight);

    juce::ColourGradient gradient(
        secondaryColor, filledBounds.getCentreX(), filledBounds.getBottom(),
        primaryColor, filledBounds.getCentreX(), filledBounds.getY(), false);
    
    RoundedRect(filledBounds, 6.0f)
      .gradient(gradient)
      .render(g);

    auto thumbY = trackBounds.getBottom() - normalizedPos * trackBounds.getHeight();
    auto thumbBounds = juce::Rectangle<float>(trackBounds.getCentreX() - 15, thumbY - 8, 30, 16);

    RoundedRect(thumbBounds, 8.0f)
      .glow(3, accentColor, 0.4f, 0.1f)
      .render(g);
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
  using namespace graphics;
  
  auto bounds = juce::Rectangle<int>(0, 0, width, height).toFloat().reduced(2);

  juce::ColourGradient borderGradient(primaryColor, 0, 0, secondaryColor,
                                      static_cast<float>(width),
                                      static_cast<float>(height), false);

  RoundedRect(bounds, 8.0f)
    .fill(backgroundColor.brighter(0.1f))
    .gradient(borderGradient)
    .stroke(juce::Colours::white, 2.0f)
    .render(g);

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
