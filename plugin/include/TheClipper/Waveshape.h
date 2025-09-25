#pragma once

#include <cmath>

namespace audio_plugin {

enum ClippingMode { Hard, Soft };

class Waveshape {
public:
  static float hardClip(float input, float threshold, float saturation);
  static float softClip(float input, float threshold, float saturation);
  static float processClipping(float input,
                               float threshold,
                               float saturation,
                               ClippingMode mode);

private:
  static float tanh_approx(float x);
};

}  // namespace audio_plugin
