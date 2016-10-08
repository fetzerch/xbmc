# Kodi CMake based buildsystem - Developer Guide

This file describes Kodi's CMake based buildsystem for Kodi developers
that need to extend the buildsystem in order to add additional
platforms, libraries or files.

The user documentation can be found in [project/cmake/README.md](https://github.com/xbmc/xbmc/tree/master/project/cmake/README.md).

## CMake

In order to extend some parts of the buildsystem some better
understanding of CMake itself is necessary. A good basic guide to start
with is: [CMake -cmake-buildsystem](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html).

One important note on CMake documentation that can be found in the
Internet. CMake has progressed a lot in the last years and many of the
concepts and recommendations that can be found are still based on older
CMake versions 2.4 or 2.6. Therefore make sure to either stick to the
official documentation or use guides that specifically target "Modern CMake".

## General concept
- some info about the architecture
- mirroring of build-artefacts
- depends and toolchain files
- Differences to typical cmake projects
- VS/Xcode vs. makefiles (static libs vs. libkodi)

## Tree structure

- project/cmake/*
- lib/*/CMakeLists.txt
- xbmc/*/CMakeLists.txt

## Variables

- CORE_BUILD_TYPE
- CORE_SOURCE_DIR
- CORE_BINARY_DIR
- CORE_SYSTEM_NAME
- CMAKE_GENERATOR

## Platform setup
- Archsetup file
- Installation file

## Writing CMake Modules
- <https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#a-sample-find-module>
- Try to create them loosly coupled to the kodi specifics
- Don't trust package config
