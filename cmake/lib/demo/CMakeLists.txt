cmake_minimum_required(VERSION 3.14)

target_sources(lib PUBLIC
        ${CHURLOS_SRC_DIR}/lib/demo/ArrayDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/HeapDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/KeyboardDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/MainMenu.cc
        ${CHURLOS_SRC_DIR}/lib/demo/PagingDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/PCSPKdemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/PreemptiveThreadDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/SmartPointerDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/StringDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/TextDemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/VBEdemo.cc
        ${CHURLOS_SRC_DIR}/lib/demo/VectorDemo.cc
        )
