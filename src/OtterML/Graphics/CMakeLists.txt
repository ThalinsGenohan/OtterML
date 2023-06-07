set(INCROOT ${PROJECT_SOURCE_DIR}/include/OtterML/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/OtterML/Graphics)
set(LIBROOT ${PROJECT_SOURCE_DIR}/lib/include)

set(SRC
	${LIBROOT}/glad/glad.c
	${LIBROOT}/glad/glad.h
	${LIBROOT}/KHR/khrplatform.h

	${SRCROOT}/Shader.cpp
	${INCROOT}/Shader.hpp
	${SRCROOT}/Transform.cpp
	${INCROOT}/Transform.hpp
)
source_group("" FILES ${SRC})

otterml_add_library(Graphics SOURCES ${SRC})

target_link_libraries(otterml-graphics PUBLIC OtterML::System ${CMAKE_DL_LIBS})

#todo
