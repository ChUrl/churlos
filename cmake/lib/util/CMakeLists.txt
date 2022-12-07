cmake_minimum_required(VERSION 3.14)

target_sources(lib PUBLIC
        ${CHURLOS_SRC_DIR}/lib/util/String.cc
        ${CHURLOS_SRC_DIR}/lib/util/StringBuffer.cc
        ${CHURLOS_SRC_DIR}/lib/util/StringView.cc
        )
