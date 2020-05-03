
MESSAGE("Deleting _build/CMakeFiles folder")
EXECUTE_PROCESS(COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
# Where is the target environment
cmake_minimum_required(VERSION 3.8)
project(pixel VERSION 1.0)

add_definitions(-DIMX6)
SET(CMAKE_C_FLAGS "-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard")
SET(CMAKE_C_FLAGS_INIT "-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard")
SET(CMAKE_CXX_FLAGS "-O2 -pipe -g -feliminate-unused-debug-types")
SET(CMAKE_CXX_FLAGS_INIT "-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard")
SET(CMAKE_C_COMPILER "/opt/fslc-xwayland/2.4.4/sysroots/x86_64-fslcsdk-linux/usr/bin/arm-fslc-linux-gnueabi/arm-fslc-linux-gnueabi-gcc" )
SET(CMAKE_CXX_COMPILER "/opt/fslc-xwayland/2.4.4/sysroots/x86_64-fslcsdk-linux/usr/bin/arm-fslc-linux-gnueabi/arm-fslc-linux-gnueabi-g++" )
SET(CMAKE_FIND_ROOT_PATH "/opt/fslc-xwayland/2.4.4/sysroots/armv7at2hf-neon-fslc-linux-gnueabi")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

ADD_EXECUTABLE(
			pixel 
			src/pixel_file_manager.cpp 
			src/pixel_mesh.cpp 	
			src/pixel_palette.cpp 
			src/pixel_animation.cpp 
			src/pixel.cpp 
			src/pixel_renderer.cpp 
			src/pixel_surface.cpp 
			src/pixel_surface_x11.cpp
			src/pixel_gl_program_manager.cpp 
			src/pixel_controller.cpp)
TARGET_LINK_LIBRARIES(pixel X11 EGL GLESv2)

