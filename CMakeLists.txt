cmake_minimum_required(VERSION 2.8)

project(ZEngine)

set(ZENGINE ZEngine)
set(SAMPLE_CUBES Sample_Cubes)
set(SAMPLE_LIGHT Sample_Light)
set(SAMPLE_BASIC_LIGHTING Sample_BasicLighting)
set(SAMPLE_MATERIALS Sample_Materials)
set(SAMPLE_LIGHTING_MAP Sample_LightingMap)
set(SAMPLE_SHADOW_MAPPING Sample_ShadowMapping)

set(ZENGINE_SRC_UTIL 
	src/zengine/utils/font.h 
	src/zengine/utils/font.cpp
	src/zengine/utils/log.h
	src/zengine/utils/log.cpp
	src/zengine/utils/memory.cpp
	src/zengine/utils/time.h
	src/zengine/utils/time.cpp)

set(ZENGINE_SRC_RENDERER 
	src/zengine/renderer/renderer.cpp 
	src/zengine/renderer/renderer.h)

set(ZENGINE_SRC_MAIN 
	src/zengine/game.cpp
	src/zengine/game.h
	src/zengine/main.cpp
	src/zengine/shader.h
	src/zengine/stb_image.h
	src/zengine/shadermanager.h
	src/zengine/shadermanager.cpp)

set(SAMPLE_CUBES_SRC src/samples/cubes/main.cpp)
set(SAMPLE_LIGHT_SRC src/samples/light/main.cpp)
set(SAMPLE_BASIC_LIGHTING_SRC src/samples/basic_lighting/main.cpp)
set(SAMPLE_MATERIALS_SRC src/samples/materials/main.cpp)
set(SAMPLE_LIGHTING_MAP_SRC src/samples/lighting_map/main.cpp)
set(SAMPLE_SHADOW_MAPPING_SRC src/samples/shadow_mapping/main.cpp)

if(WIN32)
	set(ZENGINE_LINK_LIBRARIES
		glew32sd.lib
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
include_directories(src/zengine)

source_group("utils" FILES ${ZENGINE_SRC_UTIL})
source_group("renderer" FILES ${ZENGINE_SRC_RENDERER})

#add_executable(${ZENGINE} ${ZENGINE_SRC_UTIL} ${ZENGINE_SRC_RENDERER} ${ZENGINE_SRC_MAIN})

add_library(${ZENGINE} ${ZENGINE_SRC_UTIL} ${ZENGINE_SRC_RENDERER} ${ZENGINE_SRC_MAIN})
add_executable(${SAMPLE_CUBES} ${SAMPLE_CUBES_SRC})
add_executable(${SAMPLE_LIGHT} ${SAMPLE_LIGHT_SRC})
add_executable(${SAMPLE_BASIC_LIGHTING} ${SAMPLE_BASIC_LIGHTING_SRC})
add_executable(${SAMPLE_MATERIALS} ${SAMPLE_MATERIALS_SRC})
add_executable(${SAMPLE_LIGHTING_MAP} ${SAMPLE_LIGHTING_MAP_SRC})
add_executable(${SAMPLE_SHADOW_MAPPING} ${SAMPLE_SHADOW_MAPPING_SRC})

if(WIN32)
	add_custom_command(TARGET ${ZENGINE} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E 		copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)

	add_definitions("/W3 /D_CRT_SECURE_NO_WARNINGS /wd4819 /nologo")
elseif(APPLE)
	add_custom_command(TARGET ${ZENGINE} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E 		copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/Debug/resources)
	add_custom_command(TARGET ${ZENGINE} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E 		copy_directory ${PROJECT_SOURCE_DIR}/lib/mac /usr/local/lib)
endif(WIN32)

target_link_libraries(${SAMPLE_CUBES} ${ZENGINE_LINK_LIBRARIES} ${ZENGINE})
target_link_libraries(${SAMPLE_LIGHT} ${ZENGINE_LINK_LIBRARIES} ${ZENGINE})
target_link_libraries(${SAMPLE_BASIC_LIGHTING} ${ZENGINE_LINK_LIBRARIES} ${ZENGINE})
target_link_libraries(${SAMPLE_MATERIALS} ${ZENGINE_LINK_LIBRARIES} ${ZENGINE})
target_link_libraries(${SAMPLE_LIGHTING_MAP} ${ZENGINE_LINK_LIBRARIES} ${ZENGINE})
target_link_libraries(${SAMPLE_SHADOW_MAPPING} ${ZENGINE_LINK_LIBRARIES} ${ZENGINE})