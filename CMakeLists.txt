cmake_minimum_required(VERSION 2.8)

project(ZEngine)

set(ZENGINE ZEngine)

set(ZENGINE_SRC_UTIL 
	src/utils/font.h 
	src/utils/font.cpp
	src/utils/log.h
	src/utils/log.cpp
	src/utils/memory.cpp
	src/utils/time.h
	src/utils/time.cpp)

set(ZENGINE_SRC_RENDERER 
	src/renderer/renderer.cpp 
	src/renderer/renderer.h)

set(ZENGINE_SRC_MAIN 
	src/game.cpp
	src/game.h
	src/main.cpp
	src/shader.h
	src/stb_image.h
	src/shadermanager.h
	src/shadermanager.cpp)

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
		libsoillib.dylib
		${OPENGL_LIB}
	)
endif()

if(WIN32)
	link_directories(${PROJECT_SOURCE_DIR}/lib/windows)
elseif(APPLE)
	link_directories(${PROJECT_SOURCE_DIR}/lib/mac)
endif()

include_directories(include)
include_directories(include/freetype)

source_group("utils" FILES ${ZENGINE_SRC_UTIL})
source_group("renderer" FILES ${ZENGINE_SRC_RENDERER})

add_executable(${ZENGINE} 
		${ZENGINE_SRC_UTIL} 
		${ZENGINE_SRC_RENDERER}
		${ZENGINE_SRC_MAIN})
if(WIN32)
	add_custom_command(TARGET ${ZENGINE} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E 		copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)

	add_definitions("/W3 /D_CRT_SECURE_NO_WARNINGS /wd4098 /wd4099 /nologo")
elseif(APPLE)
	add_custom_command(TARGET ${ZENGINE} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E 		copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/Debug/resources)
	add_custom_command(TARGET ${ZENGINE} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E 		copy_directory ${PROJECT_SOURCE_DIR}/lib/mac /usr/local/lib)
endif(WIN32)

target_link_libraries(${ZENGINE} ${ZENGINE_LINK_LIBRARIES})