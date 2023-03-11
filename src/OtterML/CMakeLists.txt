include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(System)

if(OTTERML_BUILD_GRAPHICS)
    add_subdirectory(Graphics)
endif()
