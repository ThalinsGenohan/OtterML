set(INCROOT ${PROJECT_SOURCE_DIR}/include/OtterML/System)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/OtterML/System)

set(SRC
	${SRCROOT}/Angle.cpp
	${INCROOT}/Angle.hpp
	${SRCROOT}/FixedPoint.cpp
	${INCROOT}/FixedPoint.hpp
	${SRCROOT}/Matrix.cpp
	${INCROOT}/Matrix.hpp
	${SRCROOT}/Vector2.cpp
	${INCROOT}/Vector2.hpp
)
source_group("" FILES ${SRC})

otterml_add_library(System SOURCES ${SRC})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)

target_link_libraries(otterml-system glfw glm::glm spdlog::spdlog yaml-cpp)

target_include_directories(otterml-system PUBLIC ${PROJECT_SOURCE_DIR}/lib/include)
