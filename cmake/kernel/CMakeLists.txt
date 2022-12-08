cmake_minimum_required(VERSION 3.14)

project(kernel)
message(STATUS "Project " ${PROJECT_NAME})

include_directories(${CHURLOS_SRC_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Add subdirectories
add_subdirectory(event)
add_subdirectory(exception)
add_subdirectory(interrupt)
add_subdirectory(memory)
add_subdirectory(process)
add_subdirectory(service)
add_subdirectory(system)
