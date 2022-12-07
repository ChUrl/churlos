cmake_minimum_required(VERSION 3.14)

project(system)
message(STATUS "Project " ${PROJECT_NAME})

include_directories(${CHURLOS_SRC_DIR})

# Set source files
set(SOURCE_FILES
        ${CHURLOS_SRC_DIR}/startup.asm
        ${CHURLOS_SRC_DIR}/main.cc
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} device kernel lib)
