cmake_minimum_required(VERSION 3.14)

target_sources(kernel PUBLIC
        ${CHURLOS_SRC_DIR}/kernel/interrupt/Bluescreen.cc
        ${CHURLOS_SRC_DIR}/kernel/interrupt/IntDispatcher.cc
        )
