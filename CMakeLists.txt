project(Dungeons-of-Dakmor)
cmake_minimum_required(VERSION 2.8)

# -DCMAKE_PREFIX_PATH=C:\Users\robin\Source\Repos\dakmore\external_libs\
set(SDL2_PATH "SDL2")

find_package(SDL2 REQUIRED >=2.0.0)
find_package(SDL2_Image REQUIRED >=2.0.0)
# find_package(SDL2_ttf REQUIRED >=2.0.0)

aux_source_directory(. SRC_LIST)

add_definitions(-Wall -ggdb)
add_executable(dungeon ${SRC_LIST})

message(STATUS ${SDL2_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(dungeon ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

file(COPY tiles1.png DESTINATION .)
