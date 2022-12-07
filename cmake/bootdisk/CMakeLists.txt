cmake_minimum_required(VERSION 3.14)

project(bootdisk)
message(STATUS "Project " ${PROJECT_NAME})

# BIOS-dev.code:total-tracks:-heads:-sectors:start-track:-head:-sector
# Default-Werte fuer Boot von Floppy (USB/HD erkennt bootsect.asm selbst):
set(BOOTDEVICE "0:80:2:18:0:0:1")

add_custom_command(OUTPUT "${CHURLOS_ROOT_DIR}/bootdisk.vmi"
        BYPRODUCTS "${CMAKE_BINARY_DIR}/bootsect" "${CMAKE_BINARY_DIR}/setup" "${CMAKE_BINARY_DIR}/build" "${CMAKE_BINARY_DIR}/system.img" "${CMAKE_BINARY_DIR}/bootdisk.img" "${CMAKE_BINARY_DIR}/bootdisk.vmi"

        # Compile bootsect and setup code
        COMMAND nasm -f bin -o "${CMAKE_BINARY_DIR}/bootsect" "${CHURLOS_SRC_DIR}/bootdisk/bootsect.asm"
        COMMAND nasm -f bin -o "${CMAKE_BINARY_DIR}/setup" "${CHURLOS_SRC_DIR}/bootdisk/setup.asm"

        # Compile build code
        COMMAND gcc -o "${CMAKE_BINARY_DIR}/build" "${CHURLOS_SRC_DIR}/bootdisk/build.c"

        # Build system.img
        COMMAND objcopy -O binary "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/system" "${CMAKE_BINARY_DIR}/system.img"

        # Build bootdisk
        COMMAND "${CMAKE_BINARY_DIR}/build" "${CMAKE_BINARY_DIR}/bootsect" "${CMAKE_BINARY_DIR}/setup" "${CMAKE_BINARY_DIR}/system.img" ${BOOTDEVICE} "${CMAKE_BINARY_DIR}/bootdisk.img"
        COMMAND dd if="${CMAKE_BINARY_DIR}/bootdisk.img" of="${CMAKE_BINARY_DIR}/bootdisk.vmi" bs=1474560 conv=sync
        COMMAND /run/current-system/sw/bin/cp "${CMAKE_BINARY_DIR}/bootdisk.vmi" "${CHURLOS_ROOT_DIR}/bootdisk.vmi"
        DEPENDS system
        )

add_custom_target(${PROJECT_NAME} DEPENDS ${CHURLOS_ROOT_DIR}/bootdisk.vmi)
