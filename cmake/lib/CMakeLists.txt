cmake_minimum_required(VERSION 3.14)

project(lib)
message(STATUS "Project " ${PROJECT_NAME})

include_directories(${CHURLOS_SRC_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Add subdirectories
add_subdirectory(async)
add_subdirectory(mem)
add_subdirectory(stream)
add_subdirectory(util)
