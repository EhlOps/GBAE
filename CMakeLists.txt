cmake_minimum_required(VERSION 3.28.0)
project(gbae LANGUAGES C VERSION 0.0.1)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib)
add_subdirectory(gbae)

target_link_libraries(gbae PRIVATE emu)
