set(HEADER_DIR "${OtterML_SOURCE_DIR}/include/OtterML/Graphics")
set(HEADER_LIST
	"${OtterML_SOURCE_DIR}/include/OtterML/Common.hpp"
	"${HEADER_DIR}/Color.hpp"
	"${HEADER_DIR}/Renderer.hpp"
	"${HEADER_DIR}/Shader.hpp"
	"${HEADER_DIR}/Texture2D.hpp"
	"${HEADER_DIR}/Transform2D.hpp"
)

set(SOURCE_DIR "${OtterML_SOURCE_DIR}/src/OtterML/Graphics")
set(SOURCE_LIST
	"${SOURCE_DIR}/Color.cpp"
	"${SOURCE_DIR}/Renderer.cpp"
	"${SOURCE_DIR}/Shader.cpp"
	"${SOURCE_DIR}/Texture2D.cpp"
	"${SOURCE_DIR}/Transform2D.cpp"
)

add_library(otterml-graphics ${SOURCE_LIST} ${HEADER_LIST})
add_library(OtterML::Graphics ALIAS otterml-graphics)

target_include_directories(otterml-graphics PUBLIC "${OtterML_SOURCE_DIR}/include")
target_include_directories(otterml-graphics PRIVATE "${OtterML_SOURCE_DIR}/lib/glad/include")

# TODO: Remove dependency on unnecessary libraries by abstracting more?
target_link_libraries(otterml-graphics PRIVATE OtterML::System glm::glm spdlog::spdlog yaml-cpp)

target_compile_features(otterml-graphics PUBLIC cxx_std_20)

target_precompile_headers(otterml-graphics REUSE_FROM otterml-system)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
