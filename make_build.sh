#!/usr/bin/sh

target="$1"

function build_impl()
{
  build_dir_name="$1"

  if [ ! -d ./$build_dir_name ];
  then
    mkdir $build_dir_name
  fi

  cd $build_dir_name
  echo -e "\e[1;34m[*]\e[0m Build started..."
  cmake .. && make -j$(nproc)

  if [ $? == 0 ];
  then
    echo -e "\e[1;32m[+]\e[0m Build complete!"
  else
    echo -e "\e[1;31m[-]\e[0m Build failed!"
  fi
}

function install_binaries()
{
  if [[ ! -d ./build-native ]] || [[ ! -f ./build-native/NvCtrl-Linux ]];
  then
    echo -e "\e[1;34m[*]\e[0m Please, run it again with arg 'native' to create native build"
    exit 1
  fi

  sudo cp ./build-native/NvCtrl-Linux /usr/bin/.
  if [ $? == 0 ];
  then
    echo -e "\e[1;32m[+]\e[0m Binary was installed in /usr/bin/"
  else
    echo -e "\e[1;31m[-]\e[0m Installation failed"
  fi
}

function build_native()
{
  echo -e "\e[1;34m[*]\e[0m Selected: native Linux build"
  build_impl "build-native"
}

function build_appimage()
{
  echo -e "\e[1;34m[*]\e[0m Selected: AppImage (portable) Linux build"
  ./scripts/generate_appimage.sh "./build-native"
}

function build_win32()
{
  echo -e "\e[1;34m[*]\e[0m Selected: Win32 build with MinGW"
}



if [ $target ];
then
  case "$target" in
    "linux" | "native" | "default") build_native ;;
    "appimage" | "linux-appimage" | "portable") build_appimage ;;
    "win32" | "windows" | "mingw") build_win32 ;;
    "install") install_binaries ;;
  esac
else
  echo -e "\e[1;31mRequired option\e[0m"
fi

