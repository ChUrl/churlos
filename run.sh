#!/usr/bin/env bash

QEMU_BIN="qemu-system-i386"
QEMU_MACHINE="pc"
QEMU_CPU="base"
QEMU_RAM="128M"
QEMU_ARGS="-drive format=raw,file=./bootdisk.vmi -boot a -k en-us -vga std -serial stdio" # or -monitor stdio
QEMU_AUDIO_ARGS="-audiodev id=pa,driver=pa -machine pcspk-audiodev=pa"
QEMU_GDB_PORT=""

command="${QEMU_BIN} -machine ${QEMU_MACHINE} -m ${QEMU_RAM} -cpu ${QEMU_CPU} ${QEMU_ARGS} ${QEMU_AUDIO_ARGS}"

printf "Running: %s\\n" "${command}"

if [ -n "${QEMU_GDB_PORT}" ]; then
  $command -gdb tcp::"${QEMU_GDB_PORT}" -S &
else
  $command
fi
