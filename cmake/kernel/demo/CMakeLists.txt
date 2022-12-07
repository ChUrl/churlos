cmake_minimum_required(VERSION 3.14)

target_sources(kernel PUBLIC
        ${CHURLOS_SRC_DIR}/kernel/demo/ArrayDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/bmp_hhu.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/HeapDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/KeyboardDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/MainMenu.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/PagingDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/PCSPKdemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/PreemptiveThreadDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/SmartPointerDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/StringDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/TextDemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/VBEdemo.cc
        ${CHURLOS_SRC_DIR}/kernel/demo/VectorDemo.cc
        )
