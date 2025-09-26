#pragma once

#include <juce_graphics/juce_graphics.h>
#include <optional>
#include <memory>

namespace audio_plugin {
namespace graphics {

struct GlowEffect {
    int layers;
    juce::Colour color;
    float startAlpha;
    float falloff;
};

struct PulseAnimation {
    float frequency;
    float amplitude;
    float phase = 0.0f;
};

struct Style {
    juce::Colour fill = juce::Colours::transparentBlack;
    juce::Colour stroke = juce::Colours::transparentBlack;
    float strokeWidth = 1.0f;
    std::optional<juce::ColourGradient> gradient;
    std::optional<GlowEffect> glow;
    std::optional<PulseAnimation> pulse;
    float cornerRadius = 0.0f;
};

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;

    Shape& fill(juce::Colour color) { 
        style_.fill = color; 
        return *this; 
    }
    
    Shape& stroke(juce::Colour color, float width = 1.0f) { 
        style_.stroke = color; 
        style_.strokeWidth = width; 
        return *this; 
    }
    
    Shape& stroke(const juce::ColourGradient& grad, float width = 1.0f) {
        style_.gradient = grad;
        style_.strokeWidth = width;
        return *this;
    }
    
    Shape& gradient(const juce::ColourGradient& grad) { 
        style_.gradient = grad; 
        return *this; 
    }
    
    Shape& glow(int layers, juce::Colour color, float startAlpha, float falloff) {
        style_.glow = GlowEffect{layers, color, startAlpha, falloff};
        return *this;
    }
    
    Shape& pulse(float frequency, float amplitude) {
        style_.pulse = PulseAnimation{frequency, amplitude};
        return *this;
    }

    Shape& cornerRadius(float radius) {
        style_.cornerRadius = radius;
        return *this;
    }

    virtual void render(juce::Graphics& g) const = 0;

protected:
    Style style_;
    
    void applyGlow(juce::Graphics& g, const std::function<void(float)>& drawFunc) const;
    void applyFill(juce::Graphics& g) const;
    void applyStroke(juce::Graphics& g, const juce::Path& path) const;
};

class Circle : public Shape {
public:
    Circle(juce::Point<float> center, float radius) 
        : center_(center), radius_(radius) {}
    
    void render(juce::Graphics& g) const override;

private:
    juce::Point<float> center_;
    float radius_;
};

class RoundedRect : public Shape {
public:
    RoundedRect(juce::Rectangle<float> bounds, float cornerRadius = 0.0f) 
        : bounds_(bounds) {
        if (cornerRadius > 0.0f) {
            style_.cornerRadius = cornerRadius;
        }
    }
    
    void render(juce::Graphics& g) const override;

private:
    juce::Rectangle<float> bounds_;
};

class Arc : public Shape {
public:
    Arc(juce::Point<float> center, float radius, float startAngle, float endAngle)
        : center_(center), radius_(radius), startAngle_(startAngle), endAngle_(endAngle) {}
    
    void render(juce::Graphics& g) const override;

private:
    juce::Point<float> center_;
    float radius_;
    float startAngle_;
    float endAngle_;
};

template<typename ShapeType, typename... Args>
std::unique_ptr<ShapeType> make_shape(Args&&... args) {
    return std::make_unique<ShapeType>(std::forward<Args>(args)...);
}

}  // namespace graphics
}  // namespace audio_plugin
