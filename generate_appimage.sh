#!/usr/bin/sh

CURR_DIR=`pwd`
APP_VER="v$(cat ./.last_version)"
APP_DIR="./NvCtrl-Linux.AppDir"
BIN_DIR="$1"

function copy_runtime_lib()
{
  lib_name="$1"
  cp $lib_name $APP_DIR/usr/lib/.
}

if [ ! -d $APP_DIR ]
then
  mkdir $APP_DIR
  mkdir -p $APP_DIR/usr/bin
  mkdir -p $APP_DIR/usr/lib

  cp ./res/appimage/NvCtrl-Linux.desktop $APP_DIR/.
  cp ./res/appimage/AppRun $APP_DIR/.
  cp ./res/NvCtrl.png $APP_DIR/.

  desktop-file-validate $APP_DIR/NvCtrl-Linux.desktop
  chmod +x $APP_DIR/AppRun
fi

if [[ -d $BIN_DIR ]] && [[ -f $BIN_DIR/NvCtrl-Linux ]]
then
  copy_runtime_lib "/usr/lib/libQt5Core.so.5"
  copy_runtime_lib "/usr/lib/libQt5Gui.so.5"
  copy_runtime_lib "/usr/lib/libQt5Widgets.so.5"
  copy_runtime_lib "/usr/lib/libQt5DBus.so.5"
  copy_runtime_lib "/usr/lib/libpng16.so.16"
  copy_runtime_lib "/usr/lib/libz.so.1"
  copy_runtime_lib "/usr/lib/libharfbuzz.so.0"
  copy_runtime_lib "/usr/lib/libmd4c.so.0"
  copy_runtime_lib "/usr/lib/libdouble-conversion.so.3"
  copy_runtime_lib "/usr/lib/libicui18n.so.72"
  copy_runtime_lib "/usr/lib/libicuuc.so.72"
  copy_runtime_lib "/usr/lib/libpcre2-16.so.0"
  copy_runtime_lib "/usr/lib/libzstd.so.1"
  copy_runtime_lib "/usr/lib/libglib-2.0.so.0"
  copy_runtime_lib "/usr/lib/libfreetype.so.6"
  copy_runtime_lib "/usr/lib/libgraphite2.so.3"
  copy_runtime_lib "/usr/lib/libicudata.so.72"
  copy_runtime_lib "/usr/lib/libpcre2-8.so.0"
  copy_runtime_lib "/usr/lib/libbz2.so.1.0"
  copy_runtime_lib "/usr/lib/libbrotlidec.so.1"
  copy_runtime_lib "/usr/lib/libbrotlicommon.so.1"
  copy_runtime_lib "/usr/lib/libstdc++.so.6"
  cp $BIN_DIR/NvCtrl-Linux $APP_DIR/usr/bin/.
  
  echo -e "\e[1;34m[*]\e[0m Build started"
  appimagetool $APP_DIR
  if [ $? == 0 ]
  then
    mv NvCtrl-Linux-x86_64.AppImage NvCtrl-Linux-$APP_VER-x86_64.AppImage
    echo -e "\e[1;32m[+]\e[0m Build complete"
  else
    echo -e "\e[1;31m[-]\e[0m Build failed"
  fi
else
  echo -e "\e[1;36m[!]\e[0m Run 'make_build.sh' for native build"
fi

