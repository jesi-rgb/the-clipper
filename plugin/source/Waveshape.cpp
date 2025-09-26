#include "TheClipper/Waveshape.h"
#include <cmath>

namespace audio_plugin {

float Waveshape::hardClip(float input, float threshold, float saturation) {
  float scaledInput = input * saturation;

  if (scaledInput > threshold) {
    return threshold;
  } else if (scaledInput < -threshold) {
    return -threshold;
  }

  return scaledInput;
}

float Waveshape::softClip(float input, float threshold, float saturation) {
  float scaledInput = input * saturation;
  float normalizedInput = scaledInput / threshold;

  return threshold * tanh(normalizedInput);
}

float Waveshape::processClipping(float inputSample,
                                 float threshold,
                                 float saturation,
                                 float inputGain,
                                 ClippingMode mode) {
  float input = gain(inputSample, inputGain);

  switch (mode) {
    case ClippingMode::Hard:
      return hardClip(input, threshold, saturation);
    case ClippingMode::Soft:
      return softClip(input, threshold, saturation);
    default:
      return input;
  }
}

float Waveshape::tanh_approx(float x) {
  if (x < -3.0f)
    return -1.0f;
  if (x > 3.0f)
    return 1.0f;

  return x * (27.0f + x * x) / (27.0f + 9.0f * x * x);
}

float Waveshape::tanh(float x) {
  return std::tanh(x);
}


float Waveshape::gain(float x, float gainDB) {
  float linearGain = std::pow(10.0f, gainDB / 20.0f);
  return x * linearGain;
}
}  // namespace audio_plugin
