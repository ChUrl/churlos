#!/usr/bin/env bash

BUILD_DIR="build"
CORE_COUNT=8
BUILD_TYPE="Debug"
TARGET="bootdisk"

echo "Creating build-directory ${BUILD_DIR}"
mkdir -p ${BUILD_DIR}
cd $BUILD_DIR || exit

echo "Using ${CORE_COUNT} CPU-Cores for make"

cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
make -j "${CORE_COUNT}" "${TARGET}"
