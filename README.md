# The Clipper

![Cmake workflow success badge](https://github.com/jesi-rgb/the-clipper/actions/workflows/cmake.yml/badge.svg)

A JUCE-based audio clipper plugin that provides precise clipping and waveshaping capabilities.

## Dev

In the main repo directory execute:

```bash
$ cmake --preset default # uses the Ninja build system
$ cmake --build build
$ ctest --preset default
```

Existing presets are `default`, `release`, and `Xcode`.

Then simply run `quick_launch.sh`;
