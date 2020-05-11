cmake_minimum_required(VERSION 3.10)
project(ProjectBalls)

set(CMAKE_CXX_STANDARD 11)
set(SFML_STATIC_LIBRARIES TRUE) #SFML_STATIC
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
add_executable(ProjectBalls
        balls.cpp
        ${SOURCE_FILES})
include_directories("E:\\C projects\\ProjectBalls\\lib\\SFML-2.5.1(32)\\include")
target_link_libraries(ProjectBalls sfml-graphics)