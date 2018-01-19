cmake_minimum_required (VERSION 2.6)
project (Visualization)

set (Visualization_VERSION 0.0.0)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -O2 -Wall")
set (SOURCE ${PROJECT_SOURCE_DIR}/tests/test)

add_subdirectory("${PROJECT_SOURCE_DIR}/src/graphics")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/graphics/filters")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/math")
add_executable(main ${SOURCE} ${HEADERS})