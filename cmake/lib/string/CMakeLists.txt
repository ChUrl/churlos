cmake_minimum_required(VERSION 3.14)

target_sources(lib PUBLIC
        ${CHURLOS_SRC_DIR}/lib/string/String.cc
        ${CHURLOS_SRC_DIR}/lib/string/StringView.cc
        )
