## Version 1.5.10 (release)
### Changes and fixes
* Improved settings validation
* Some other internal changes
### Download
Download source code [for version 1.5.10](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.10)

Download AppImage file [for version 1.5.10](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.10)

## Version 1.5.9 (pre-release (UNSTABLE))
### Changes and fixes
* Added new dependency: Qt5Charts (for real time chart view)
* Some other internal changes
### Download
Download source code [for version 1.5.9](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.9)

Download AppImage file [for version 1.5.9](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.9)

## Version 1.5.7 (release)
### Changes and fixes
* HOTFIX: fixed segmentation fault error with std::filesystem::path
### Download
Download source code [for version 1.5.7](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.7)

Download AppImage file [for version 1.5.7](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.7)

## Version 1.5.6 (release)
### Changes and fixes
* Changed method GpuClockController::apply_clock_profile:
* * require arg - ref to current profile
* * replace raw for loops by std::for_each() + lambda
* Changed method MainWindow::load_fan_and_clock_offset_profiles(): 
* * replace raw for loops by std::for_each() + lambda 
* Clock profile values now shows only when profile applied
* Refactored MainWindow class
* Unifiend all controllers into one class - GpuSystemsController
* Removed some dead code
* Change some std::for_each() to raw for loops for readability
* Added settings validation
* Moved AppImage generation script to subfolder
* Added AppImage support in build script
* Critical: fixed bug in update checker
* Replace some std::for_each() with raw for loops (for readability)
* Marked some lambda\`s as static
### Download
Download source code [for version 1.5.6](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.6)

Download AppImage file [for version 1.5.6](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.6)

## Version 1.5.5 (pre-release (UNSTABLE))
### Changes and fixes
* Change some std::for_each() to raw for loops for readability
* Added settings validation
* Moved AppImage generation script to subfolder
* Added AppImage support in build script
* Other internal changes (codestyle + readability)
### Download
Download source code [for version 1.5.5](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.5)

Download AppImage file [for version 1.5.5](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.5)

## Version 1.5.3 (pre-release (UNSTABLE))
### Changes and fixes
* Critical: fixed bug in update checker
* Replace some std::for_each() with raw for loops (for readability)
* Marked some lambda\`s as static
### Download
Download source code [for version 1.5.3](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.3)

Download AppImage file [for version 1.5.3](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.3)

## Version 1.5.0 (pre-release (UNSTABLE))
### Changes and fixes
* Refactored MainWindow class
* Unifiend all controllers into one class - GpuSystemsController
* Removed some dead code
* Resume AppImage builds
* Other internal changes...
### Download
Download source code [for version 1.5.0](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.0)

Download AppImage file [for version 1.5.0](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.5.0)

## Version 1.4.41 (pre-release (UNSTABLE))
### Changes and fixes
* Updated submodules (spdlog)
* Fixed AppImage generation script
### Download
Download source code [for version 1.4.41](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.41)

Download AppImage file [for version 1.4.41](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.41)

## Version 1.4.40 (pre-release (UNSTABLE))
### Changes and fixes
* Changed method GpuClockController::apply_clock_profile:
* * require arg - ref to current profile
* * replace raw for loops by std::for_each() + lambda
* Changed method MainWindow::load_fan_and_clock_offset_profiles(): 
* * replace raw for loops by std::for_each() + lambda 
* Clock profile values now shows only when profile applied
* Other internal changes and fixes
### Download
Download source code [for version 1.4.40](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.40)

## Version 1.4.38 (pre-release (UNSTABLE))
### Changes and fixes
* Update submodules (NVMLpp, spdlog)
### Download
Download source code [for version 1.4.38](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.38)

## Version 1.4.37 (release)
### Changes and fixes
* Fixed double message about fan profile creation
* UI changes: moved fan speed and GPU temperature widgets to main (info) tab
* Updated submodules (spdlog)
* Fixed warning with LTO
* Added win32 platform support via MinGW cross compilation
* Disabled GPU processes table for win32 platform (unsupported yet)
* Fixed endless recursion in NVMLpp library
* Fixed curl binary for win32
* Refactored AppImage packing (add runtime)
### Download
Download source code [for version 1.4.37](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.37)

## Version 1.4.36 (pre-release (UNSTABLE))
### Changes and fixes
* Fixed double message about fan profile creation
### Download
Download source code [for version 1.4.36](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.36)

## Version 1.4.35 (pre-release (UNSTABLE))
### Changes and fixes
* UI changes: moved fan speed and GPU temperature widgets to main (info) tab
* Updated submodules (spdlog)
* Fixed warning with LTO
### Download
Download source code [for version 1.4.35](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.35)

## Version 1.4.34 (pre-release (UNSTABLE))
### Changes and fixes
* Removed all AppImages (refactoring structure)
### Download
Download source code [for version 1.4.34](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.34)

## Version 1.4.33 (pre-release (UNSTABLE))
### Changes and fixes
* Added win32 platform support via MinGW cross compilation
* Disabled GPU processes table for win32 platform (unsupported yet)
* Fixed endless recursion in NVMLpp library
* Fixed curl binary for win32
### Download
Download source code [for version 1.4.33](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.33)

## Version 1.4.31 (release)
### Changes and fixes
* Values now doesn\`t update when window is hidden (doesn\`t utilize much more CPU time when hidden)
### Download
Download source code [for version 1.4.31](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.31)

## Version 1.4.30 (release)
### Changes and fixes
* Update submodules (spdlog lib)
* Update copyright years on about dialog window
* All \*Controllers classes (and other classes) now marked as final
* Explicit QString creating replased by QStringLiteral to avoid allocations
### Download
Download source code [for version 1.4.30](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.30)

## Version 1.4.26 (release)
### Changes and fixes
* Static linking with libstdc++ and libgcc
### Download
Download source code [for version 1.4.26](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.26)

## Version 1.4.25 (release)
### Changes and fixes
* Changed changelog URL, fixed "temporarily redirected" error when trying to get changelog
### Download
Download source code [for version 1.4.25](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.25)

## Version 1.4.24 (release)
### Changes and fixes
* Updated submodules (spdlog lib)
* Using LTO (link time optimizations) by default (via cmake_cxx_flags)
### Download
Download source code [for version 1.4.24](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.24)

## Version 1.4.23 (release)
### Changes and fixes
* Avoiding QString heap allocations for static literals
* Updated build and appimage generate scripts
* Updated submodules
### Download
Download source code[for version 1.4.23](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.23)

## Version 1.4.22 (release)
### Changes and fixes
* Added build and install shell scripts for native build
* Internal changes
### Download
Download source code [for version 1.4.22](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.22)

## Version 1.4.21 (release)
### Changes and fixes
* Update submodules: update NVMLpp to version 525.60.11
* Some internal changes
### Download
Download source code [for version 1.4.21](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.21)

## Version 1.4.19 (release)
### Changes and fixes
* Rebranding, changed application name and descriprion
* Changed repository name, changed all URLs
* Removed unused code
* Some internal changes and fixes (updated submodules)
* Updated AppImage build script
* Renamed .AppDir folder
### Download
Download source code [for version 1.4.19](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.19)

## Version 1.4.16 (release)
### Changes and fixes
* Fallback to previous process view impl, fixed segfault
* Updated NVMLpp: fixed process list size, removed unused code
### Download
Download source code [for version 1.4.16](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.16)

## Version 1.4.15 (release)
### Changes and fixes
* Reduced max rows count in GpuProcessesOverviewDialog (32 -> 24)
### Download
Download source code [for version 1.4.15](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.15)

## Version 1.4.14 (release)
### Changes and fixes
* Change .dump() func call to decrease file size
* Added function name in debug log
### Download
Download source code [for version 1.4.14](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.14)

## Version 1.4.13 (release)
### Changes and fixes
* Added basic processes view (PID, memory usage, proc name)
* Added download links to changelog
* Open browser when link clicked on RecentUpdatesDialog window
* Removed std::async() call, replace by std::for_each
* Fixed not showing messagebox when local version is little bit higher than remote (for developers)
* Fixed wrong fan profile loading (it was load to clock offset comboBox widget)
* Removed unused code
### Download
Download source code [for version 1.4.13](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.13)

## Version 1.4.12 (pre-release (UNSTABLE))
### Changes and fixes
* Fixed wrong fan profile loading (it was load to clock offset comboBox widget)
* Removed unused code
### Download
Download source code [for version 1.4.12](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.12)

## Version 1.4.11 (pre-release (UNSTABLE))
### Changes and fixes
* Removed std::async() call, replace by std::for_each
* Fixed: wrong memory usage value for running processes
### Download
Download source code [for version 1.4.11](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.11)

## Version 1.4.10 (pre-release (UNSTABLE))
### Changes and fixes
* Added selected process termination via kill() syscall
* Added download links to changelog
* Open browser when link clicked on RecentUpdatesDialog window
### Download
Download source code [for version 1.4.10](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.10)

## Version 1.4.9 (pre-release (UNSTABLE))
### Changes and fixes
* Added base for killing selected process
* Added spacer in menuBar at tab 'view'
* Replaced GpuProcessesOverviewDialog with raw NVMLpp::NVML_device\* (GpuProcessesController not used yet)
### Download
Download source code [for version 1.4.9](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.9)

## Version 1.4.8 (pre-release (UNSTABLE))
### Changes and fixes
* Added basic processes view (PID, memory usage, proc name)
* Updated UI elements on GpuProcessesOverviewDialog
* Fixed errors in NVMLpp lib
### Download
Download source code [for version 1.4.8](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.8)

## Version 1.4.7 (pre-release (UNSTABLE))
### Changes and fixes
* Changed class name
* Added new class GpuProcessesController to get info about running processes on GPU
* Added timer on GpuProcessesOverviewDialog for work with GpuClockController
* Fixed not showing messagebox when local version is little bit higher than remote (for developers)
* Some other internal changes (codestyle, logic)
### Download
Download source code [for version 1.4.7](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.7)

## Version 1.4.5 (release)
### Changes and fixes
* Added support only one single application instance
* Added support to show MainWindow of already running application via IPC (DBus)
* New dependency: QtDBus lib (should be already installed with qt5-base package (for Arch GNU/Linux), other distros not tested)
* Some other internal fixes
### Download
Download source code [for version 1.4.5](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.5)

## Version 1.4.2 (release)
### Changes and fixes
* Changed SettingsManager class, now its doesn\`t need QObject
* Removed std::unique_ptr<> from SettingsManager for std::fstream object
### Download
Download source code [for version 1.4.2](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.2)

## Version 1.4.0 (release)
### Changes and fixes
* Big updates:
* * Fixed bugs in UpdateChecker
* * Changes all urls, on dialog about fixed label alignment
* * Added some new methods to MainWindow class for update clock offset values
* * Reimplemented clock profile UI and internals (NOT compatible with older versions!!!)
* * Reviewed and Reimplemented some methods inside GpuClockController class
* * In ClockProfileDialog replaced raw for-loops with std::for_each(), improved readability
* * Optimized and fixed applying of attributes via nvidia-settings subprocess call (packs args to batch instead of creating of nvidia-settings instances)
* * Fixed error when trying to open unexisting file in home dir (now SettingsManager create a new file)
* * Removed support of loading default config from /usr/share/gwepp/gwepp.json
* PKGBUILD files is no longer distributes
### Download
Download source code [for versions 1.4.0](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/tag/v1.4.0)

## Version 1.3.19 (pre-release (UNSTABLE))
### Changes and fixes
* Replaced submodule nlohman-json with single-include header file to speedup PKGBUILD packaging
* Fixed compile error

## Version 1.3.18 (pre-release (UNSTABLE))
### Changes and fixes
* Fixed bug in UpdateChecker
* Some internal changes and fixes

## Version 1.3.16 (pre-release (UNSTABLE))
### Changes and fixes
* Changes all urls, on dialog about fixed label alignment

## Version 1.3.15 (pre-release (UNSTABLE))
### Changes and fixes
* Added support to show clock offset values of current profile
* Fixed error with old (wrong) values on window when canceling EditClockOffsetProfile dialog
* Added some new methods to MainWindow class for update clock offset values

## Version 1.3.14 (pre-release (UNSTABLE))
### Changes and fixes
* Added current clock profile editting support (renewed EditClockOffsetProfileDialog UI)
* Fixed layout and widgets width on ClockProfileDialog
* In ClockProfileDialog replaced raw for-loops with std::for_each(), improved readability
* Some other fixes

## Version 1.3.11 (pre-release (UNSTABLE))
### Changes and fixes
* Fixed error with unexisting directory in /home

## Version 1.3.10 (pre-release (UNSTABLE))
### Changes and fixes
* Fixed error when trying to open unexisting file in home dir (now SettingsManager create a new file)
* Removed support of loading default config from /usr/share/gwepp/gwepp.json
* Updated default settings and fixed error with wrong value

## Version 1.3.9 (pre-release (UNSTABLE))
### Changes and fixes
* Reimplemented clock profile saving
* Added support clocks for GPU and memory both
* Added support of applying custon clock profile
* Reviewed and Reimplemented some methods inside GpuClockController class
* Optimized and fixed applying of attributes via nvidia-settings subprocess call (packs args to batch instead of creating of nvidia-settings instances)

## Version 1.3.8 (pre-release (UNSTABLE))
### Changes and fixes
* Added support of saving and applying clock profiles
* Internal changes in GpuClockController class (added new methods and other)
* Removed warning when selecting custom clock profile

## Version 1.3.7 (pre-release (UNSTABLE))
### Changes and fixes
* Started develop of new clock profile design (per pstate control)
* Show messageBox with warning - creating new clock profile is not implemented yet (it will implemented in next ver)

## Version 1.3.6 (stable release)
### Changes and fixes
* Updates submodules (update NVMLpp: PIMPL idiom)
* Some other fixes

## Version 1.3.5 (stable release)
### Changes and fixes
* Fixed error with thread stopping while it running
* Added new signal in UpdateChecker
* Showing message box when no updates found

## Version 1.3.4 (stable release)
### Changes and fixes
* Updated logic inside SettingsManager
* Fixed std::move() call in main.cpp (remove const)

## Version 1.3.3 (stable release)
### Changes and fixes
* Updated public interface of SettingsManager class
* Moved app settings validation from MainWidnow into SettingsManager
* Some other internal fixes

## Version 1.3.2 (stable release)
### Changes and fixes
* Added qrc file and move icons inside it (no more /usr/share/icons is used)
* Fixed error with missing icons when run AppImage
* Updated PKGBUILD for Arch based distros

## Version 1.3.1 (stable release)
### Changes and fixes
* Hotfix: fixed error with settings (reading null object)
* Added Appimage

## Version 1.3.0 (stable release)
### Changes and fixes
* Added check for updates from both branches
* Added changelog to repository
* Added support to read changelog when new version is available
* Internal changes (codestyle, logic)
* Update default app settings

## Version 1.2.8 (pre-release)
### Changes and fixes
* Added changelog to repository
* Added support to read changelog when new version is available
* Internal changes (codestyle, logic)

## Version 1.2.7 (pre-release)
### Changes and fixes
* Added support for check updates at startup
* UpdateChecker now is non-blocking thread (QThread), no blocks at startup
* Updated default app settings

