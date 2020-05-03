#include  <sys/time.h>

#ifdef IMX6
#	include <wayland-client.h>
#	include <wayland-egl.h>
#else
#	include  <X11/Xlib.h>
#	include  <X11/Xatom.h>
#	include  <X11/Xutil.h>
#endif

#include  <GLES2/gl2.h>
#include  <EGL/egl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <stdlib.h>
