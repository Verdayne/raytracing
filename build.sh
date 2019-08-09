#!/usr/bin/env bash
# build.sh

TARGET="raycasting"
BUILD_PATH="build"
COMPILR_FLAGS="-O0 -g -Wall -Wextra -Wshadow"

mkdir -p $BUILD_PATH

g++ -o $BUILD_PATH/$TARGET src/main.cpp $COMPILR_FLAGS