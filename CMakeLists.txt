project(AgarioEngineDemo)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)
# add_subdirectory(tests)
add_subdirectory(lib/glm/glm)
add_subdirectory(lib/googletest)