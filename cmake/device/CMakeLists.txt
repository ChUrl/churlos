cmake_minimum_required(VERSION 3.14)

project(device)
message(STATUS "Project " ${PROJECT_NAME})

include_directories(${CHURLOS_SRC_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Add subdirectories
add_subdirectory(bios)
add_subdirectory(cpu)
add_subdirectory(graphics)
add_subdirectory(hid)
add_subdirectory(interrupt)
add_subdirectory(port)
add_subdirectory(sound)
add_subdirectory(time)
