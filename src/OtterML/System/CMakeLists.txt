set(INCROOT ${PROJECT_SOURCE_DIR}/include/OtterML/System)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/OtterML/System)

set(SRC
	${SRCROOT}/Vector2.cpp
	${INCROOT}/Vector2.hpp
	${INCROOT}/Vector2.inl
)
source_group("" FILES ${SRC})

otterml_add_library(System SOURCES ${SRC})
