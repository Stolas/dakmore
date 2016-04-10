project(Dungeons-of-Dakmor)
cmake_minimum_required(VERSION 2.8)

SET(LIBTCOD_ROOT libtcod)
INCLUDE_DIRECTORIES(${LIBTCOD_ROOT}/include)
# TODO: Fix
LINK_DIRECTORIES(/home/robin/projects/Dungeons-of-Dakmor/libtcod/)

aux_source_directory(. SRC_LIST)


add_definitions(-Wall)
add_executable(dungeon ${SRC_LIST})
get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "DIR: ${OUT_VAR}")
target_link_libraries(dungeon tcod)
target_link_libraries(dungeon tcodxx)


file(COPY ${LIBTCOD_ROOT}/terminal.png DESTINATION .)
