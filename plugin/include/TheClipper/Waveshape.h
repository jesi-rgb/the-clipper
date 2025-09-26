#pragma once

#include <cmath>

namespace audio_plugin {

enum ClippingMode { Hard, Soft };

class Waveshape {
public:
  static float hardClip(float input, float threshold, float saturation);
  static float softClip(float input, float threshold, float saturation);
  static float processClipping(float inputSample,
                               float threshold,
                               float saturation,
                               float inputGain,
                               ClippingMode mode);

  static float gain(float x, float gain);
private:
  static float tanh_approx(float x);
  static float tanh(float x);
};

}  // namespace audio_plugin
