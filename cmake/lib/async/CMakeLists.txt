cmake_minimum_required(VERSION 3.14)

target_sources(lib PUBLIC
        ${CHURLOS_SRC_DIR}/lib/async/Semaphore.cc
        ${CHURLOS_SRC_DIR}/lib/async/SpinLock.cc
        )
