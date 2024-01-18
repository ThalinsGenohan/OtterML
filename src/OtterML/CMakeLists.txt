set(HEADER_DIR "${OtterML_SOURCE_DIR}/include/OtterML")
set(HEADER_LIST
	"${HEADER_DIR}/Common.hpp"
	"${HEADER_DIR}/Angle.hpp"
	"${HEADER_DIR}/Color.hpp"
	"${HEADER_DIR}/FixedPoint.hpp"
	"${HEADER_DIR}/Matrix.hpp"
	"${HEADER_DIR}/Renderer.hpp"
	"${HEADER_DIR}/Shader.hpp"
	"${HEADER_DIR}/Texture2D.hpp"
	"${HEADER_DIR}/Transform2D.hpp"
	"${HEADER_DIR}/Vector2.hpp"
	"${HEADER_DIR}/Vector3.hpp"
	"${HEADER_DIR}/Vector4.hpp"
)

set(SOURCE_DIR "${OtterML_SOURCE_DIR}/src/OtterML")
set(SOURCE_LIST
	"${SOURCE_DIR}/Angle.cpp"
	"${SOURCE_DIR}/Color.cpp"
	"${SOURCE_DIR}/FixedPoint.cpp"
	"${SOURCE_DIR}/Matrix.cpp"
	"${SOURCE_DIR}/Renderer.cpp"
	"${SOURCE_DIR}/Shader.cpp"
	"${SOURCE_DIR}/Texture2D.cpp"
	"${SOURCE_DIR}/Transform2D.cpp"
	"${SOURCE_DIR}/Vector2.cpp"
	"${SOURCE_DIR}/Vector3.cpp"
	"${SOURCE_DIR}/Vector4.cpp"
)

add_library(otterml ${SOURCE_LIST} ${HEADER_LIST})
add_library(OtterML::OtterML ALIAS otterml)

target_include_directories(otterml PUBLIC "${OtterML_SOURCE_DIR}/include")

target_compile_features(otterml PUBLIC cxx_std_20)

target_precompile_headers(otterml PUBLIC "${OtterML_SOURCE_DIR}/src/OtterML/PCH.hpp")

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
