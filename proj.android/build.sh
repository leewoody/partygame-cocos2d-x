#!/bin/bash
echo "# build start ..."
export NDK_ROOT=/Users/i_woodylee/android-ndk-r9d
python build_native.py
mv libs/libcocos2dx.jar ./
ant debug
ant release
mv ./libcocos2dx.jar ./libs

