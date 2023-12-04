cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(advent2023 CXX)

SET (SRC_DIR ./src)

SET (SRC_FILES
        ${SRC_DIR}/main.cpp
		${SRC_DIR}/day01.cpp
        ${SRC_DIR}/day02.cpp
        ${SRC_DIR}/day03.cpp
        ${SRC_DIR}/day04.cpp
)

add_executable(advent2023 ${SRC_FILES})