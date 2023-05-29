set(INCROOT ${PROJECT_SOURCE_DIR}/include/OtterML/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/OtterML/Graphics)

set(SRC
	${SRCROOT}/Transform.cpp
	${INCROOT}/Transform.hpp
)
source_group("" FILES ${SRC})

otterml_add_library(Graphics SOURCES ${SRC})

target_link_libraries(otterml-graphics PUBLIC OtterML::System)

#todo
