cmake_minimum_required(VERSION 3.14)

target_sources(lib PUBLIC
        ${CHURLOS_SRC_DIR}/lib/stream/CGA_Stream.cc
        ${CHURLOS_SRC_DIR}/lib/stream/Logger.cc
        ${CHURLOS_SRC_DIR}/lib/stream/OutStream.cc
        ${CHURLOS_SRC_DIR}/lib/stream/StringBuffer.cc
        )
