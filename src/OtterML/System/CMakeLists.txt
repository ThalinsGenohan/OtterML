set(HEADER_DIR "${OtterML_SOURCE_DIR}/include/OtterML/System")
set(HEADER_LIST
	"${OtterML_SOURCE_DIR}/include/OtterML/Common.hpp"
	"${HEADER_DIR}/Angle.hpp"
	"${HEADER_DIR}/FixedPoint.hpp"
	"${HEADER_DIR}/Matrix.hpp"
	"${HEADER_DIR}/Vector2.hpp"
	"${HEADER_DIR}/Vector3.hpp"
	"${HEADER_DIR}/Vector4.hpp"
	#"${HEADER_DIR}/Vector.hpp"
)

set(SOURCE_DIR "${OtterML_SOURCE_DIR}/src/OtterML/System")
set(SOURCE_LIST
	"${SOURCE_DIR}/Angle.cpp"
	"${SOURCE_DIR}/FixedPoint.cpp"
	"${SOURCE_DIR}/Matrix.cpp"
	"${SOURCE_DIR}/Vector2.cpp"
	"${SOURCE_DIR}/Vector3.cpp"
	"${SOURCE_DIR}/Vector4.cpp"
	#"${SOURCE_DIR}/Vector.cpp"
)

add_library(otterml-system ${SOURCE_LIST} ${HEADER_LIST})
add_library(OtterML::System ALIAS otterml-system)

target_include_directories(otterml-system PUBLIC "${OtterML_SOURCE_DIR}/include")

target_link_libraries(otterml-system PRIVATE glm::glm spdlog::spdlog yaml-cpp)

target_compile_features(otterml-system PUBLIC cxx_std_20)

target_precompile_headers(otterml-system PRIVATE "${OtterML_SOURCE_DIR}/src/OtterML/PCH.hpp")

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
