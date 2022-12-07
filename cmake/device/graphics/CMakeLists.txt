cmake_minimum_required(VERSION 3.14)

target_sources(device PUBLIC
        ${CHURLOS_SRC_DIR}/device/graphics/CGA.cc
        ${CHURLOS_SRC_DIR}/device/graphics/CGA_Stream.cc
        ${CHURLOS_SRC_DIR}/device/graphics/Fonts.cc
        ${CHURLOS_SRC_DIR}/device/graphics/LFBgraphics.cc
        ${CHURLOS_SRC_DIR}/device/graphics/VESA.cc
        )
