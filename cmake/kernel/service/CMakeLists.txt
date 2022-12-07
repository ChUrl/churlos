cmake_minimum_required(VERSION 3.14)

target_sources(kernel PUBLIC
        ${CHURLOS_SRC_DIR}/kernel/service/Service.cpp
        ${CHURLOS_SRC_DIR}/kernel/service/EventService.cpp
        ${CHURLOS_SRC_DIR}/kernel/service/InterruptService.cpp
        ${CHURLOS_SRC_DIR}/kernel/service/MemoryService.cpp
        ${CHURLOS_SRC_DIR}/kernel/service/SchedulerService.cpp
        )
