// . /opt/fslc-xwayland/2.5.3/environment-setup-armv7at2hf-neon-fslc-linux-gnueabi
// ${CC} -DLINUX -g -o wex wayland-example.c lX11 -lwayland-client -lwayland-egl -lEGL -lGLESv2 

// ${CC} -DLINUX -g -o wex wayland-example.c -lwayland-client -lEGL -lGLESv2 -lwayland-egl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <GL/gl.h>

struct display {
	struct wl_display *display;
	struct wl_compositor *compositor;
	struct wl_shell *shell;
	struct wl_regisry* registry;
	struct wl_egl_window * window;
	struct wl_surface * surface;
	struct wl_shell_surface* shell_surface;
};

struct egl {
	EGLDisplay eglDisplay;
	EGLConfig* configs;
	EGLContext ctx;
	EGLSurface eglSurface;
	EGLint major, minor; 
};

EGLint configList[] = {
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,	
			EGL_NONE
		};

static const EGLint context_attribs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

void global_object_available(void*, struct wl_registry*, uint32_t, const char*, uint32_t);
void global_object_removed(void*, struct wl_registry*, uint32_t);

struct wl_registry_listener listener = {
	global_object_available,
	global_object_removed
};

void global_object_available(void* data, struct wl_registry *registry, uint32_t name, const char* interface, uint32_t version)
{
	struct display* display = data;
	printf("new wayland global object: interface=%s, name=%i\n", interface, name);
	if (strcmp(interface,"wl_compositor")==0)
	{
		display->compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version); 
		printf("Compositor found \n");
		return;
	}
	if (strcmp(interface, "wl_shell")==0)
	{
		display->shell = wl_registry_bind(registry, name, &wl_shell_interface, version);
		printf("Shell found\n");
		return;
	}
};

void global_object_removed(void* data, struct wl_registry *wl_registry, uint32_t name)
{
	printf("Wayland global object removed: name=%i\n", name);
};

void initDisplayClient(struct display* display)
{
    display->display = wl_display_connect(NULL);
    if (display->display == NULL) {
		printf("Can't connect to display\n");
		exit(1);
    }
    printf("connected to display\n");
	display->registry = wl_display_get_registry(display->display);
	wl_registry_add_listener(display->registry, &listener, display); 
	wl_display_dispatch(display->display);
	wl_display_roundtrip(display->display);

	if (display->compositor == NULL)
	{
		printf("error: no compositor\n");
		exit(1);
	}

	display->surface = wl_compositor_create_surface(display->compositor);
	if (display->surface == NULL)
	{	
		printf("Cannot create surface \n");
		exit(1);
	}

	display->shell_surface = wl_shell_get_shell_surface(display->shell, display->surface);
	if (display->shell_surface == NULL)
	{	
		printf("Cannot create shell surface \n");
		exit(1);   
	}
	wl_shell_surface_set_toplevel(display->shell_surface);	
}

void initEGL(struct display* display, struct egl* egl)
{
	egl->eglDisplay = eglGetDisplay((EGLNativeDisplayType)display->display);
	if (egl->eglDisplay == EGL_NO_DISPLAY)
	{
		printf("No egl display found\n");
		exit(1);
	}

	if (eglInitialize(egl->eglDisplay, &egl->major, &egl->minor)!=EGL_TRUE)
	{
		printf("Cannot initialize egl\n");
		exit(1);
	}

	printf("EGL major %i, minor %i\n",egl->major, egl->minor);

	EGLint maxConfigs, numConfigs;
	numConfigs = 0;
	if (eglGetConfigs(egl->eglDisplay, NULL, 0, &maxConfigs)!=EGL_TRUE)
	{
		printf("Error determining egl configs\n");
		exit(1);
	}

	printf("Max configs: %i\n", maxConfigs);
	egl->configs = (EGLConfig*)calloc((int)maxConfigs,sizeof(EGLConfig));
	if (!eglChooseConfig(egl->eglDisplay, configList, egl->configs, maxConfigs,  &numConfigs))
	{
		GLenum e = glGetError();
		printf("Error choosing egl configs: %i num configs: %i \n", e, numConfigs); 
		exit(1);
	}

	egl->ctx = eglCreateContext(egl->eglDisplay, *egl->configs, EGL_NO_CONTEXT, context_attribs);
	display->window = wl_egl_window_create(display->surface,800,600);
	egl->eglSurface = eglCreateWindowSurface(egl->eglDisplay, *egl->configs, display->window, NULL);
	
	if (eglMakeCurrent(egl->eglDisplay, egl->eglSurface, egl->eglSurface, egl->ctx)==EGL_FALSE)
	{
		printf("Cant Make it current \n");
		exit(1);	
	} 	
}

void closeDisplayClient(struct display* display)
{
    wl_display_disconnect(display->display);
    printf("disconnected from display\n");
}

void closeEGL()
{
}

void render(struct egl* egl)
{
	glViewport(0,0,700,500);
	glClearColor(0.0f,1.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	eglSwapBuffers(egl->eglDisplay, egl->eglSurface);
	getchar();
}

int main(int argc, char **argv) {

	struct display display = { 0 };
	struct egl egl = { 0 };
	initDisplayClient(&display);
	initEGL(&display, &egl);
	render(&egl);
	closeDisplayClient(&display);
	
	return 0;
}
