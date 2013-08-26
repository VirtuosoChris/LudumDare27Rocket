cmake_minimum_required(VERSION 2.8)
project(EveryonePanic)

if(NOT MSVC)
set(CMAKE_CXX_FLAGS "--std=c++0x")
endif(NOT MSVC)

add_executable(rocketGame 
	main.cpp
	stb_image_write.h
	stb_image.h
	stb_image.c
	Texture.cpp
	Texture.h
	MovieState.h
	MovieState.cpp
	Timer.h
	GameCode.cpp
	GameCode.h
)

find_package(GLUT)
find_package(OpenGL)



set(OPENAL_INCLUDE_DIR "" CACHE PATH "")

set(AVBIN_DIR "" CACHE PATH "")
set(AVBIN_LIB "" CACHE FILEPATH "" )

set(ALUT_INCLUDE_PATH "" CACHE PATH "")
set(ALUT_LIB "" CACHE FILEPATH "" )

set(OPENAL_LIB "" CACHE FILEPATH "" )


add_executable(vidTest  vidTest.cpp)
target_link_libraries(vidTest ${AVBIN_LIB})
target_link_libraries(vidTest ${ALUT_LIB})

if(GLUT_FOUND AND OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${VIRTUOSO_CONSOLE_INCLUDE_PATH} ${AVBIN_DIR} ${ALUT_INCLUDE_PATH} ${OPENAL_INCLUDE_DIR}
	)
	target_link_libraries(rocketGame ${OPENAL_LIB})
	target_link_libraries(rocketGame ${ALUT_LIB})
	target_link_libraries(rocketGame ${GLUT_glut_LIBRARY})
	target_link_libraries(rocketGame ${OPENGL_gl_LIBRARY})
	target_link_libraries(rocketGame ${OPENGL_glu_LIBRARY}) 
	target_link_libraries(rocketGame ${AVBIN_LIB})
	 
endif()