

cmake_minimum_required(VERSION 3.8)
project(simple_openCV)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable( simple_opencv lib.cpp)

target_link_libraries(simple_opencv ${OpenCV_LIBS} )
add_compile_options(-s ALLOW_MEMORY_GROWTH
	
	)

target_link_options(simple_opencv PUBLIC --bind
	PUBLIC -s ALLOW_MEMORY_GROWTH
)
