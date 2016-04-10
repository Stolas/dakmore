project(Dungeons-of-Dakmor)
cmake_minimum_required(VERSION 2.8)

# SET(LIBTCOD_ROOT libtcod)
# INCLUDE_DIRECTORIES(${LIBTCOD_ROOT}/include)
# # TODO: Fix
# LINK_DIRECTORIES(/home/robin/projects/Dungeons-of-Dakmor/libtcod/)

aux_source_directory(. SRC_LIST)


add_definitions(-Wall -ggdb)
add_executable(dungeon ${SRC_LIST})


include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(dungeon ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# target_link_libraries(dungeon tcod)
# target_link_libraries(dungeon tcodxx)


file(COPY tiles1.png DESTINATION .)
