cmake_minimum_required(VERSION 3.8)

project(
	OtterML
	VERSION 0.1
	LANGUAGES CXX
)

#set(CMAKE_MODULE_PATH ${OtterML_SOURCE_DIR}/cmake)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_EXTENSIONS OFF)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

#find_package(glm REQUIRED)
#find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)

add_subdirectory(src/OtterML)
