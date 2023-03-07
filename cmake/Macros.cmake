# include the compiler warnings helpers
include(${CMAKE_CURRENT_LIST_DIR}/CompilerWarnings.cmake)

# helper function to tweak visibility of public symbols
function(set_public_symbols_hidden target)
    # ensure public symbols are hidden by default (exported ones are explicitly marked)
    set_target_properties(${target} PROPERTIES
                          CXX_VISIBILITY_PRESET hidden
                          VISIBILITY_INLINES_HIDDEN YES)
endfunction()

# set the appropriate standard library on each platform for the given target
# example: otterml_set_stdlib(otterml-system)
function(otterml_set_stdlib target)
    # for gcc on Windows, apply the OTTERML_USE_STATIC_STD_LIBS option if it is enabled
    if(OTTERML_OS_WINDOWS AND OTTERML_COMPILER_GCC)
        if(OTTERML_USE_STATIC_STD_LIBS AND NOT OTTERML_COMPILER_GCC_TDM)
            target_link_libraries(${target} PRIVATE "-static-libgcc" "-static-libstdc++")
        elseif(NOT OTTERML_USE_STATIC_STD_LIBS AND OTTERML_COMPILER_GCC_TDM)
            target_link_libraries(${target} PRIVATE "-shared-libgcc" "-shared-libstdc++")
        endif()
    endif()

    if(OTTERML_OS_MACOSX)
        if(${CMAKE_GENERATOR} MATCHES "Xcode")
            otterml_set_xcode_property(${target} CLANG_CXX_LIBRARY "libc++")
        elseif(NOT OTTERML_COMPILER_CLANG)
            message(FATAL_ERROR "Clang is the only supported compiler on macOS")
        endif()
    endif()
endfunction()

# add a new target which is a OtterML library
# example: otterml_add_library(Graphics
#                           SOURCES sprite.cpp image.cpp ...
#                           [STATIC]) # Always create a static library and ignore BUILD_SHARED_LIBS
macro(otterml_add_library module)

    # parse the arguments
    cmake_parse_arguments(THIS "STATIC" "" "SOURCES" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling otterml_add_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create the target
    string(TOLOWER otterml-${module} target)
    if(THIS_STATIC)
        add_library(${target} STATIC ${THIS_SOURCES})
    else()
        add_library(${target} ${THIS_SOURCES})
    endif()
    add_library(OtterML::${module} ALIAS ${target})

    # enable C++17 support
    target_compile_features(${target} PUBLIC cxx_std_17)

    # Add required flags for GCC if coverage reporting is enabled
    if(OTTERML_ENABLE_COVERAGE AND (OTTERML_COMPILER_GCC OR OTTERML_COMPILER_CLANG))
        target_compile_options(${target} PUBLIC $<$<CONFIG:DEBUG>:-O0> $<$<CONFIG:DEBUG>:-g> $<$<CONFIG:DEBUG>:-fprofile-arcs> $<$<CONFIG:DEBUG>:-ftest-coverage>)
        target_link_options(${target} PUBLIC $<$<CONFIG:DEBUG>:--coverage>)
    endif()

    set_target_warnings(${target})
    set_public_symbols_hidden(${target})

    # enable precompiled headers
    if (OTTERML_ENABLE_PCH AND (NOT ${target} STREQUAL "otterml-system"))
        message(VERBOSE "enabling PCH for OtterML library '${target}'")
        target_precompile_headers(${target} REUSE_FROM otterml-system)
    endif()

    # define the export symbol of the module
    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    # define the export name of the module
    set_target_properties(${target} PROPERTIES EXPORT_NAME OtterML::${module})

    # adjust the output file prefix/suffix to match our conventions
    if(BUILD_SHARED_LIBS AND NOT THIS_STATIC)
        if(OTTERML_OS_WINDOWS)
            # include the major version number in Windows shared library names (but not import library names)
            set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
            set_target_properties(${target} PROPERTIES SUFFIX "-${PROJECT_VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")

            # fill out all variables we use to generate the .rc file
            string(TIMESTAMP RC_CURRENT_YEAR "%Y")
            string(REGEX REPLACE "otterml-([a-z])([a-z]*)" "\\1" RC_MODULE_NAME_HEAD "${target}")
            string(REGEX REPLACE "otterml-([a-z])([a-z]*)" "\\2" RC_MODULE_NAME_TAIL "${target}")
            string(TOUPPER "${RC_MODULE_NAME_HEAD}" RC_MODULE_NAME_HEAD)
            set(RC_MODULE_NAME "${RC_MODULE_NAME_HEAD}${RC_MODULE_NAME_TAIL}")
            set(RC_VERSION_SUFFIX "") # Add something like the git revision short SHA-1 in the future
            set(RC_PRERELEASE "0") # Set to 1 to mark the DLL as a pre-release DLL
            set(RC_TARGET_NAME "${target}")
            set(RC_TARGET_FILE_NAME_SUFFIX "-${PROJECT_VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")

            # generate the .rc file
            #configure_file(
            #    "${PROJECT_SOURCE_DIR}/tools/windows/resource.rc.in"
            #    "${CMAKE_CURRENT_BINARY_DIR}/${target}.rc"
            #    @ONLY
            #)
            #target_sources(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${target}.rc")
            #source_group("" FILES "${CMAKE_CURRENT_BINARY_DIR}/${target}.rc")

            if(OTTERML_COMPILER_GCC OR OTTERML_COMPILER_CLANG)
                # on Windows + gcc/clang get rid of "lib" prefix for shared libraries,
                # and transform the ".dll.a" suffix into ".a" for import libraries
                set_target_properties(${target} PROPERTIES PREFIX "")
                set_target_properties(${target} PROPERTIES IMPORT_SUFFIX ".a")
            endif()
        else()
            set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        endif()
    else()
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -s-d)
        set_target_properties(${target} PROPERTIES RELEASE_POSTFIX -s)
        set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX -s)
        set_target_properties(${target} PROPERTIES RELWITHDEBINFO_POSTFIX -s)

        if(OTTERML_USE_STATIC_STD_LIBS)
            set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        endif()
    endif()

    # set the version and soversion of the target (for compatible systems -- mostly Linuxes)
    # except for Android which strips soversion suffixes
    if(NOT OTTERML_OS_ANDROID)
        set_target_properties(${target} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
        set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})
    endif()

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "OtterML")

    # set the target flags to use the appropriate C++ standard library
    otterml_set_stdlib(${target})

    # For Visual Studio on Windows, export debug symbols (PDB files) to lib directory
    if(OTTERML_GENERATE_PDB)
        # PDB files are only generated in Debug and RelWithDebInfo configurations, find out which one
        if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(OTTERML_PDB_POSTFIX "-d")
        else()
            set(OTTERML_PDB_POSTFIX "")
        endif()

        if(BUILD_SHARED_LIBS AND NOT THIS_STATIC)
            # DLLs export debug symbols in the linker PDB (the compiler PDB is an intermediate file)
            set_target_properties(${target} PROPERTIES
                                  PDB_NAME "${target}${OTTERML_PDB_POSTFIX}"
                                  PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
        else()
            if(OTTERML_ENABLE_PCH)
                message(VERBOSE "overriding PDB name for '${target}' with \"otterml-s${OTTERML_PDB_POSTFIX}\" due to PCH being enabled")

                # For PCH builds with PCH reuse, the PDB name must be the same as the target that's being reused
                set_target_properties(${target} PROPERTIES
                                      COMPILE_PDB_NAME "otterml-system"
                                      COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
            else()
                # Static libraries have no linker PDBs, thus the compiler PDBs are relevant
                set_target_properties(${target} PROPERTIES
                                      COMPILE_PDB_NAME "${target}-s${OTTERML_PDB_POSTFIX}"
                                      COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
            endif()
        endif()
    endif()

    # build frameworks or dylibs
    if(OTTERML_OS_MACOSX AND BUILD_SHARED_LIBS AND NOT THIS_STATIC)
        if(OTTERML_BUILD_FRAMEWORKS)
            # adapt target to build frameworks instead of dylibs
            set_target_properties(${target} PROPERTIES
                                  FRAMEWORK TRUE
                                  FRAMEWORK_VERSION ${PROJECT_VERSION}
                                  MACOSX_FRAMEWORK_IDENTIFIER org.otterml-dev.${target}
                                  MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
                                  MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION})
        endif()

        # adapt install directory to allow distributing dylibs/frameworks in user's frameworks/application bundle
        # but only if cmake rpath options aren't set
        if(NOT CMAKE_SKIP_RPATH AND NOT CMAKE_SKIP_INSTALL_RPATH AND NOT CMAKE_INSTALL_RPATH AND NOT CMAKE_INSTALL_RPATH_USE_LINK_PATH AND NOT CMAKE_INSTALL_NAME_DIR)
            set_target_properties(${target} PROPERTIES INSTALL_NAME_DIR "@rpath")
            if(NOT CMAKE_SKIP_BUILD_RPATH)
                set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_NAME_DIR TRUE)
            endif()
        endif()
    endif()

    if(OTTERML_OS_IOS)
        otterml_set_common_ios_properties(${target})
    endif()

    # otterml-activity library is our bootstrap activity and must not depend on stlport_shared
    # (otherwise Android will fail to load it)
    if(OTTERML_OS_ANDROID)
        if(${target} MATCHES "otterml-activity")
            set_target_properties(${target} PROPERTIES COMPILE_FLAGS -fpermissive)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-landroid -llog")
            set(CMAKE_CXX_CREATE_SHARED_LIBRARY ${CMAKE_CXX_CREATE_SHARED_LIBRARY_WITHOUT_STL})
        else()
            set(CMAKE_CXX_CREATE_SHARED_LIBRARY ${CMAKE_CXX_CREATE_SHARED_LIBRARY_WITH_STL})
        endif()
    endif()

    # add the install rule
    install(TARGETS ${target} EXPORT OtterMLConfigExport
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT bin
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
            FRAMEWORK DESTINATION "." COMPONENT bin)

    # add <project>/include as public include directory
    target_include_directories(${target}
                               PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                               PRIVATE ${PROJECT_SOURCE_DIR}/src)

    if(OTTERML_BUILD_FRAMEWORKS)
        target_include_directories(${target} INTERFACE $<INSTALL_INTERFACE:OtterML.framework>)
    else()
        target_include_directories(${target} INTERFACE $<INSTALL_INTERFACE:include>)
    endif()

    # define OTTERML_STATIC if the build type is not set to 'shared'
    if(NOT BUILD_SHARED_LIBS)
        target_compile_definitions(${target} PUBLIC "OTTERML_STATIC")
    endif()

endmacro()
