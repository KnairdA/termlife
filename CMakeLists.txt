cmake_minimum_required(VERSION 2.8)
project(life)

set(
	CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	src/
)

add_executable(
	life
		life.cc
)

target_link_libraries(
	life
		termbox
)
