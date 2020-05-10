cmake_minimum_required(VERSION 3.8)

SET(CMAKE_SYSTEM_NAME Linux)

if ("${TARGET_SDK}" STREQUAL "IMX6")
	SET(CMAKE_SYSTEM_PROCESSOR arm)

	SET(CMAKE_FIND_ROOT_PATH /opt/fslc-xwayland/2.5.3/sysroots/armv7at2hf-neon-fslc-linux-gnueabi)
	SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
	SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

	SET(CMAKE_SYSROOT /opt/fslc-xwayland/2.5.3/sysroots/armv7at2hf-neon-fslc-linux-gnueabi)

	SET(CMAKE_C_COMPILER /opt/fslc-xwayland/2.5.3/sysroots/x86_64-fslcsdk-linux/usr/bin/arm-fslc-linux-gnueabi/arm-fslc-linux-gnueabi-gcc )
	SET(CMAKE_C_FLAGS_INIT "-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard --sysroot=${CMAKE_FIND_ROOT_PATH}")

	SET(CMAKE_CXX_COMPILER /opt/fslc-xwayland/2.5.3/sysroots/x86_64-fslcsdk-linux/usr/bin/arm-fslc-linux-gnueabi/arm-fslc-linux-gnueabi-g++ )
	SET(CMAKE_CXX_FLAGS_INIT "-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard --sysroot=${CMAKE_FIND_ROOT_PATH}")

	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
	SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
	SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
	add_definitions(-DIMX6)

ENDIF()

project(wex VERSION 1.0)

add_definitions(-DLINUX)
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

SET(CMAKE_VERBOSE_MAKEFILE ON)
ADD_EXECUTABLE(
			wex 
			wayland-example.c) 
TARGET_LINK_LIBRARIES(wex X11 wayland-client EGL GLESv2 wayland-egl)

