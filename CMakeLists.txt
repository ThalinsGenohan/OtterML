cmake_minimum_required (VERSION 3.8)

macro(otterml_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

otterml_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

if(NOT CMAKE_OSX_SYSROOT)
    # query the path to the default SDK, will fail on non-macOS, but it's okay.
    execute_process(COMMAND xcodebuild -sdk macosx -version Path
                    COMMAND head -n 1
                    COMMAND tr -d '\n'
                    OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
                    ERROR_QUIET)
endif()

project("OtterML" VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CSS_STANDARD_REQUIRED true)

set(VERSION_IS_RELEASE OFF)

include(cmake/Config.cmake)

include(GNUInstallDirs)

if(NOT (OTTERML_OS_IOS OR OTTERML_OS_ANDROID))
    otterml_set_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE to build OtterML as shared libraries, FALSE to build is as static libraries")
else()
    if(OTTERML_OS_IOS)
        set(BUILD_SHARED_LIBS FALSE)
    elseif(OTTERML_OS_ANDROID)
        set(BUILD_SHARED_LIBS TRUE)
    endif()
endif()

# module options here
otterml_set_option(OTTERML_BUILD_GRAPHICS TRUE BOOL "TRUE to build OtterML's Graphics module.")

if(OTTERML_OS_WINDOWS OR OTTERML_OS_IOS)
    set(DEFAULT_INSTALL_MISC_DIR .)
elseif(OTTERML_OS_LINUX)
    set(DEFAULT_INSTALL_MISC_DIR share/OtterML)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_subdirectory(src/OtterML)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT devel
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
