add_executable(gbae main.c)

if(APPLE)
    find_library(CORE_GRAPHICS CoreGraphics)
    find_library(CORE_FOUNDATION CoreFoundation)
    if(NOT (CORE_GRAPHICS AND CORE_FOUNDATION))
        message(FATAL_ERROR "CoreGraphics and CoreFoundation not found")
    endif(NOT (CORE_GRAPHICS AND CORE_FOUNDATION))
    target_link_libraries(gbae PRIVATE ${CORE_GRAPHICS} ${CORE_FOUNDATION})
endif(APPLE)

target_link_libraries(gbae PRIVATE emu)
