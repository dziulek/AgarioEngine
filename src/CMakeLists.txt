set(BINARY ${CMAKE_PROJECT_NAME})

# file(GLOB_RECURSE SOURCE_SHAPES /shapes/*.cpp)
# file(GLOB_RECURSE SOURCE_MAPS /maps/*.cpp)
# file(GLOB_RECURSE SOURCE_CORE *.cpp)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

# set(SOURCE_FILES ${SOURCE_SHAPES} ${SOURCE_SHAPES} ${SOURCE_CORE})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run PUBLIC ${CMAKE_PROJECT_NAME}_lib glm -lsfml-graphics -lsfml-window -lsfml-system)