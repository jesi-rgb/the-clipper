# The Clipper

![Cmake workflow success badge](https://github.com/JanWilczek/audio-plugin-template/actions/workflows/cmake.yml/badge.svg)

A JUCE-based audio clipper plugin that provides precise clipping and waveshaping capabilities.

## Usage

This is a template repository which means you can right click "Use this template" on GitHub and create your own repo out of it.

After cloning it locally, you can proceed with the usual CMake workflow.

In the main repo directory execute

```bash
$ cmake -S . -B build
$ cmake --build build
```

The first run will take the most time because the dependencies (CPM, JUCE, and googletest) need to be downloaded.

Alternatively, you can use bundled CMake presets:

```bash
$ cmake --preset default # uses the Ninja build system
$ cmake --build build
$ ctest --preset default
```

Existing presets are `default`, `release`, and `Xcode`.

To run clang-format on every commit, in the main directory execute

```bash
pre-commit install
```

(for this you may need to install `pre-commit` with `pip`: `pip install pre-commit`).

Don't forget to change "YourPluginName" to, well, your plugin name everywhere 😉

## How was this template built?

See how I create this template step by step in this video:

[![Audio plugin template tutorial video](http://img.youtube.com/vi/Uq7Hwt18s3s/0.jpg)](https://www.youtube.com/watch?v=Uq7Hwt18s3s "Audio plugin template tutorial video")
