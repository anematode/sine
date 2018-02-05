cmake_minimum_required (VERSION 2.6)
project (Visualization)

set (Visualization_VERSION 0.0.0)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -O3 -Wall")
set(SOURCE ${PROJECT_SOURCE_DIR}/tests/test src/graphics/canvas.cc src/graphics/canvas.h src/graphics/graphic.h src/graphics/renderingcontext.cc src/graphics/renderingcontext.h src/graphics/genericgraphic.cc src/graphics/genericgraphic.h include/stb_image.cc include/stb_image_write.cc src/math/line.h tests/timer.cc tests/timer.h src/graphics/pixmap.cc src/graphics/imageloader.cc src/graphics/imageutils.cc src/graphics/colorutils.cc src/graphics/imageconverter.cc)

add_subdirectory("${PROJECT_SOURCE_DIR}/src/graphics")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/graphics/filters")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/math")
add_executable(main ${SOURCE} ${HEADERS})