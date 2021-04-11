project(AgarioEngineDemo)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include_directories(src)

add_subdirectory(src)

add_executable(${BINARY}_run example.cpp)

target_link_libraries(${BINARY}_run PUBLIC ${CMAKE_PROJECT_NAME}_lib -lsfml-graphics -lsfml-window -lsfml-system)
# add_subdirectory(tests)
# add_subdirectory(lib/glm)
add_subdirectory(lib/googletest)