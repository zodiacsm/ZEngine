set(ZENGINE_SRC_UTIL 
	utils/font.h 
	utils/font.cpp
	utils/log.h
	utils/log.cpp
	utils/memory.cpp
	utils/time.h
	utils/time.cpp)

set(ZENGINE_SRC_RENDERER 
	renderer/renderer.cpp 
	renderer/renderer.h)

set(ZENGINE_SRC_MAIN 
	game.cpp
	game.h
	main.cpp
	shader.h
	stb_image.h
	shadermanager.h
	shadermanager.cpp)

if(WIN32)
	set(ZENGINE_LINK_LIBRARIES
		glew32s.lib
		glfw3.lib
		OpenGL32.Lib
		SOIL.lib
		freetyped.lib
	)
elseif(APPLE)
	FIND_LIBRARY(OPENGL_LIB OpenGL)

	set(ZENGINE_LINK_LIBRARIES
		libfreetype.6.dylib
		libglfw3.3.1.dylib
		libGLEW.1.13.0.dylib
		${OPENGL_LIB}
	)
endif()

if(WIN32)
	link_directories(${PROJECT_SOURCE_DIR}/lib/windows)
elseif(APPLE)
	link_directories(${PROJECT_SOURCE_DIR}/lib/mac)
endif()

include_directories(../include)
include_directories(../include/freetype)

source_group("utils" FILES ${ZENGINE_SRC_UTIL})
source_group("renderer" FILES ${ZENGINE_SRC_RENDERER})

add_executable(zengine 
		${ZENGINE_SRC_UTIL} 
		${ZENGINE_SRC_RENDERER}
		${ZENGINE_SRC_MAIN})

target_link_libraries(zengine ${ZENGINE_LINK_LIBRARIES})