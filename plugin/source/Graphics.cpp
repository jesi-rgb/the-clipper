#include "TheClipper/Graphics.h"

namespace audio_plugin {
namespace graphics {

void Shape::applyGlow(juce::Graphics& g, const std::function<void(float)>& drawFunc) const {
    if (!style_.glow.has_value()) return;
    
    const auto& glow = style_.glow.value();
    for (float i = 0; i < glow.layers; ++i) {
        float alpha = glow.startAlpha - i * glow.falloff;
        if (alpha <= 0.0f) break;
        
        g.setColour(glow.color.withAlpha(alpha));
        drawFunc(i);
    }
}

void Shape::applyFill(juce::Graphics& g) const {
    if (style_.gradient.has_value()) {
        g.setGradientFill(style_.gradient.value());
    } else if (style_.fill != juce::Colours::transparentBlack) {
        g.setColour(style_.fill);
    }
}

void Shape::applyStroke(juce::Graphics& g, const juce::Path& path) const {
    if (style_.stroke != juce::Colours::transparentBlack) {
        g.setColour(style_.stroke);
        g.strokePath(path, juce::PathStrokeType(style_.strokeWidth, juce::PathStrokeType::curved));
    }
}

void Circle::render(juce::Graphics& g) const {
    if (style_.glow.has_value()) {
        applyGlow(g, [this, &g](float glowOffset) {
            auto expandedRadius = radius_ + glowOffset;
            juce::Rectangle<float> bounds(
                center_.x - expandedRadius, 
                center_.y - expandedRadius,
                expandedRadius * 2, 
                expandedRadius * 2
            );
            g.drawEllipse(bounds, 2.0f);
        });
    }

    juce::Rectangle<float> bounds(
        center_.x - radius_, 
        center_.y - radius_,
        radius_ * 2, 
        radius_ * 2
    );

    if (style_.fill != juce::Colours::transparentBlack || style_.gradient.has_value()) {
        applyFill(g);
        g.fillEllipse(bounds);
    }

    if (style_.stroke != juce::Colours::transparentBlack) {
        g.setColour(style_.stroke);
        g.drawEllipse(bounds, style_.strokeWidth);
    }
}

void RoundedRect::render(juce::Graphics& g) const {
    if (style_.glow.has_value()) {
        applyGlow(g, [this, &g](float glowOffset) {
            auto expandedBounds = bounds_.expanded(glowOffset);
            g.drawRoundedRectangle(expandedBounds, style_.cornerRadius, 2.0f);
        });
    }

    if (style_.fill != juce::Colours::transparentBlack || style_.gradient.has_value()) {
        applyFill(g);
        g.fillRoundedRectangle(bounds_, style_.cornerRadius);
    }

    if (style_.stroke != juce::Colours::transparentBlack) {
        g.setColour(style_.stroke);
        g.drawRoundedRectangle(bounds_, style_.cornerRadius, style_.strokeWidth);
    }
}

void Arc::render(juce::Graphics& g) const {
    juce::Path path;
    path.addArc(
        center_.x - radius_, 
        center_.y - radius_, 
        radius_ * 2.0f,
        radius_ * 2.0f, 
        startAngle_, 
        endAngle_, 
        true
    );

    if (style_.glow.has_value()) {
        applyGlow(g, [this, &g](float glowOffset) {
            juce::Path glowPath;
            glowPath.addArc(
                center_.x - radius_ - glowOffset, 
                center_.y - radius_ - glowOffset, 
                (radius_ + glowOffset) * 2.0f,
                (radius_ + glowOffset) * 2.0f, 
                startAngle_, 
                endAngle_, 
                true
            );
            g.strokePath(glowPath, juce::PathStrokeType(style_.strokeWidth + glowOffset * 2, juce::PathStrokeType::curved));
        });
    }

    if (style_.fill != juce::Colours::transparentBlack && !style_.gradient.has_value()) {
        g.setColour(style_.fill);
        g.fillPath(path);
    }

    if (style_.stroke != juce::Colours::transparentBlack || style_.gradient.has_value()) {
        if (style_.gradient.has_value()) {
            g.setGradientFill(style_.gradient.value());
        } else {
            g.setColour(style_.stroke);
        }
        g.strokePath(path, juce::PathStrokeType(style_.strokeWidth, juce::PathStrokeType::curved));
    }
}

}  // namespace graphics
}  // namespace audio_plugin