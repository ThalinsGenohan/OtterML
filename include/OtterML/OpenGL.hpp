#ifndef OTER_OPENGL_HPP
#define OTER_OPENGL_HPP

#if defined(OTTERML_SYSTEM_WINDOWS)

	#ifdef _MSC_VER
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN
		#endif
		#include <Windows.h>
	#endif

	#include <GL/GL.h>

#elif defined(OTTERML_SYSTEM_LINUX) || defined(OTTERML_SYSTEM_FREEBSD) || defined(OTTERML_SYSTEM_OPENBSD) || defined(OTTERML_SYSTEM_NETBSD)

	#if defined(OTTERML_OPENGL_ES)
		#include <GLES/gl.h>
		#include <GLES/glext.h>
	#else
		#include <GL/GL.h>
	#endif

#elif defined(OTTERML_SYSTEM_MACOS)

	#include <OpenGL/gl.h>

#elif defined(OTTERML_SYSTEM_IOS)

	#include <OpenGLES/ES1/gl.h>
	#include <OpenGLES/ES1/glext.h>

#elif defined(OTTERML_SYSTEM_ANDROID)

	#include <GLES/gl.h>
	#include <GLES/glext.h>

#endif

#endif
