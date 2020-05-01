
MESSAGE("Deleting _build/CMakeFiles folder")
EXECUTE_PROCESS(COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
# Where is the target environment
cmake_minimum_required(VERSION 3.10)
project(pixel VERSION 1.0)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)

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

