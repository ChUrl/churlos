cmake_minimum_required(VERSION 3.14)

# Set source directory variables
set(CHURLOS_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
set(CHURLOS_SRC_DIR "${CHURLOS_ROOT_DIR}/src")
set(CHURLOS_TOOL_DIR "${CHURLOS_ROOT_DIR}/tools")

# Set output directory variables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/shared)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Force out of source build
message(STATUS "Force out of source build check...")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
if (insource)
    message(FATAL_ERROR "Please do not build in your source dir. Use a dedicated build folder!")
endif ()

# Set compiler-flags
ENABLE_LANGUAGE(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
set(CMAKE_ASM_NASM_INCLUDES "${CHURLOS_SRC_DIR}/")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -I${CMAKE_ASM_NASM_INCLUDES} -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")
set(CMAKE_C_FLAGS "-m32 -march=i386 -mfpmath=387 -mno-mmx -mno-sse -mno-avx -Wall -fno-stack-protector -nostdlib -fno-pic -no-pie -ffreestanding")
if(CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 9)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmanual-endbr")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wl,--build-id=none -Wno-non-virtual-dtor -fno-threadsafe-statics -Wplacement-new=0 -fno-use-cxa-atexit -fno-rtti -fno-exceptions -std=c++20 -T ${CHURLOS_SRC_DIR}/link.ld")

# Add subdirectories
add_subdirectory(bootdisk)
add_subdirectory(device)
add_subdirectory(kernel)
add_subdirectory(lib)
add_subdirectory(system)
