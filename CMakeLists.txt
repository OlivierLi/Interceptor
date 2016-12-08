cmake_minimum_required(VERSION 2.8)
project(interceptor)

SET(CMAKE_CXX_COMPILER clang++)
SET(CLANG_COMPILE_FLAGS "-Wall -Werror -Wextra -Wfatal-errors --std=c++11 -g")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CLANG_COMPILE_FLAGS}" )

#Find all cpp files recursively
file(GLOB_RECURSE SRC "src" "src/*.cpp")

add_executable(bin/interceptor ${SFML_HEADERS} ${SRC})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML REQUIRED system window graphics network audio)

include_directories( ${OPENGL_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
target_link_libraries(bin/interceptor ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} )
