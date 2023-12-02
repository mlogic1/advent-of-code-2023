cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(advent2023 CXX)

SET (SRC_DIR ./src)

SET (SRC_FILES
        ${SRC_DIR}/main.cpp
		${SRC_DIR}/day01.cpp
)

add_executable(advent2023 ${SRC_FILES})

# target_link_libraries(smart-mirror PRIVATE libcurl_static ${SDL2_LIBRARIES} SDL2_ttf)
# target_include_directories(smart-mirror PRIVATE ./lib/json)