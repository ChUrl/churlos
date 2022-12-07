cmake_minimum_required(VERSION 3.14)

target_sources(kernel PUBLIC
        ${CHURLOS_SRC_DIR}/kernel/event/KeyEventListener.cc
        ${CHURLOS_SRC_DIR}/kernel/event/KeyEventManager.cc
        )
