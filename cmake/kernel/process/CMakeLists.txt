cmake_minimum_required(VERSION 3.14)

target_sources(kernel PUBLIC
        ${CHURLOS_SRC_DIR}/kernel/process/Scheduler.cc
        ${CHURLOS_SRC_DIR}/kernel/process/Thread.cc
        ${CHURLOS_SRC_DIR}/kernel/process/thread_asm.cpp
        ${CHURLOS_SRC_DIR}/kernel/process/Thread.asm
        )
