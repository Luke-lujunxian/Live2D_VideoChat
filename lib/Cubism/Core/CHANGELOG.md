# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),


## 2019-09-04

### Added

- Support new Inverted Masking features.
- Support ARM64 architecture for Universal Windows Platform.

### Changed

- Upgrade Core version to 04.00.0000 (67108864). This upgrade is following Cubism Editor 4.0 features.
- Add calling convention for *Windows/x86 DLL* only.

### Removed

- Remove bitcode binary due to suspension of *Cubism Bindings.*


## 2019-04-09

### Added

- Support Universal Windows Platform for Windows Store Application.


## 2019-01-31

### Added

- Add API to get the parent part of the specified part.
- Add API to get moc3 version.


## 2018-12-20

### Added

- [Native] Add new function: `csmGetPartParentPartIndices`.
- [Native, 3.3 Support] Support new Warp Deformer features.

### Changed

- Upgrade Core version to 03.03.0000 (50528256). This upgrade is following Cubism Editor 3.3 features.


## 2018-08-22

### Added

- [Native] Add support for Neon.


## 2018-05-14

### Added

- [Native] Add Windows **Visual C++ 2013** library.
- [Windows] Add runtime library choice `MT`, `MD`, `MTd`, `MDd`.
- [iOS] Add support for iPhone Simulator SDK.

### Fixed

- Fix an error occurred when linking libraries for Android `arm64-v8a`.


## 2017-11-17

### Fixed

- Fix processing of vertex index.


## 2017-10-05

### Added

- Provide bitcode for iOS.


## 2017-08-09

### Added

- [Native] Add Android *arm64-v8a* ABI library.

### Fixed

- Fix drawing order in certain scenarios.


## 2017-07-12

### Added

- Add experimental support for Emscripten.
- Add `CHANGELOG.md`.

### Fixed

- Fix access violation in certain scenarios.
- Fix update result in certain scenarios.


## 2017-05-02

### Added

- [Native] Add experimental support for Raspberry PI.
- Add `README.md`.
