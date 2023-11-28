cmake_minimum_required(VERSION 2.6)
#NAME
project (utictactoe)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
set(CMAKE_INSTALL_PREFIX ".")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
#PROGRAM
add_executable (utictactoe utictactoe.c)
#LIBRARY
add_library(model model.c)
add_library(view view.c)
add_library(ia ia.c)
target_link_libraries(view ${CURSES_LIBRARIES})
target_link_libraries (utictactoe model)
target_link_libraries (utictactoe view)
target_link_libraries (utictactoe ia)
install(TARGETS utictactoe DESTINATION ./bin)
