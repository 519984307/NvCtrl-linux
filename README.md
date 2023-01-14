# NvCtrl-Linux (previous GWEpp)
Simple and lightweight utility for control Nvida GPU on GNU/Linux

* Written in C++ and Qt for performance and lightweight
* No other extra dependencies such as Python and XNvCtrlLib (works in Wayland)

![UI 1](img/ui1.png)
![UI 1](img/ui2.png)

## Installation
* Download source code of [latest release](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/latest)
* Download AppImage file of [latest release](https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux/releases/latest)

### Building from sources
#### Build dependencies
* C++ compiler: (GCC or LLVM Clang) with C++17 support
* CMake and Make
* Qt5 package (Qt5Core, Qt5Widgets, Qt5Gui, Qt5DBus)
* Nvidia drivers 510.XX or later
#### Building steps
```
$ git clone --recurse-submodules https://codeberg.org/AlexCr4ckPentest/NvCtrl-linux
$ cd NvCtrl-linux
$ ./build.sh
```
#### To install executable in system, run:
``` $ sudo ./install.sh ```