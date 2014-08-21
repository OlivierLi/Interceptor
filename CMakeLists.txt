cmake_minimum_required(VERSION 2.8)
project(interceptor)

SET(CMAKE_CXX_COMPILER clang++)

SET(CLANG_COMPILE_FLAGS "-Wall -Werror -Wextra -Wfatal-errors --std=c++11 -g")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CLANG_COMPILE_FLAGS}" )

#Not how it should be done, SFML should be located using cmake
set (CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} "-lsfml-system -lsfml-window")

#Find all cpp files recursively
file(GLOB_RECURSE SRC "src" "src/*.cpp")

#Find all SFML headers
file(GLOB SFML_HEADERS "src" "/usr/include/SFML/*.h")

add_executable(interceptor ${SFML_HEADERS} ${SRC})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
target_link_libraries(interceptor ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} )
