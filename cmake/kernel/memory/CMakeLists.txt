cmake_minimum_required(VERSION 3.14)

target_sources(kernel PUBLIC
        ${CHURLOS_SRC_DIR}/kernel/memory/Allocator.cc
        ${CHURLOS_SRC_DIR}/kernel/memory/BumpAllocator.cc
        ${CHURLOS_SRC_DIR}/kernel/memory/LinkedListAllocator.cc
        ${CHURLOS_SRC_DIR}/kernel/memory/Paging.cc
        )
