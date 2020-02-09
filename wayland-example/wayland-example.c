//cc -g -o wex wayland-example.c -lwayland-client -lEGL -lGLESv2 -lwayland-egl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <GL/gl.h>

EGLint major, minor;

struct wl_display *display = NULL;
struct wl_compositor *compositor = NULL;
struct wl_shell *shell = NULL;
struct wl_egl_window * window = NULL;
struct wl_surface * surface = NULL;
struct wl_regisry* registry = NULL;
struct wl_shell_surface* shell_surface = NULL;
EGLDisplay eglDisplay;
EGLConfig* configs;
EGLContext ctx;
EGLSurface eglSurface; 

EGLint configList[] = {
					EGL_NONE
					};

static const EGLint context_attribs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

void global_object_available(void* data, struct wl_registry *registry, uint32_t name, const char* interface, uint32_t version)
{
	printf("new wayland global object: interface=%s, name=%i\n", interface, name);
	if (strcmp(interface,"wl_compositor")==0)
	{
		compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version); 
		printf("Compositor found \n");
		return;
	}
	if (strcmp(interface, "wl_shell")==0)
	{
		shell = wl_registry_bind(registry, name, &wl_shell_interface, version);
		printf("Shell found\n");
		return;
	}
};

void global_object_removed(void* data, struct wl_registry *wl_registry, uint32_t name)
{
	printf("Wayland global object removed: name=%i\n", name);
};

struct wl_registry_listener listener = {
	global_object_available,
	global_object_removed
};

int main(int argc, char **argv) {

    display = wl_display_connect(NULL);
    if (display == NULL) {
		fprintf(stderr, "Can't connect to display\n");
		exit(1);
    }
    printf("connected to display\n");
	registry = wl_display_get_registry(display);
	wl_registry_add_listener(registry, &listener, NULL); 

	wl_display_dispatch(display);
	wl_display_roundtrip(display);

	if (compositor == NULL)
	{
		printf("error: no compositor\n");
		return -1;
	}

	surface = wl_compositor_create_surface(compositor);
	if (surface == NULL)
	{	
		printf("Cannot create surface \n");
		return -1;
	}

	shell_surface = wl_shell_get_shell_surface(shell, surface);

	if (shell_surface == NULL)
	{	
		printf("Cannot create shell surface \n");
		return -1;
	}

	wl_shell_surface_set_toplevel(shell_surface);	

	eglDisplay = eglGetDisplay(display);

	if (eglDisplay == EGL_NO_DISPLAY)
	{
		printf("No egl display found\n");
		exit(1);
	}
	printf("Creating egl display\n");

	if (eglInitialize(eglDisplay, &major, &minor)!=EGL_TRUE)
	{
		printf("Cannot initialize egl\n");
		exit(1);
	}

	printf("EGL major %i, minor %i\n",major, minor);

	EGLint maxConfigs, numConfigs;
	numConfigs = 0;
	if (eglGetConfigs(eglDisplay, NULL, 0, &maxConfigs)!=EGL_TRUE)
	{
		printf("Error determining egl configs\n");
		exit(1);
	}

	printf("Max configs: %i\n", maxConfigs);
	configs = (EGLConfig*)calloc((int)maxConfigs,sizeof(EGLConfig));
	if (!eglChooseConfig(eglDisplay, configList, configs, maxConfigs,  &numConfigs))
	{
		GLenum e = glGetError();
		printf("Error choosing egl configs: %i num configs: %i \n", e, numConfigs); 
		exit(1);
	}

	ctx = eglCreateContext(eglDisplay, *configs, EGL_NO_CONTEXT, context_attribs);

	window = wl_egl_window_create(surface,800,600);
	eglSurface = eglCreateWindowSurface(eglDisplay, *configs, window, NULL);
	
	if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, ctx)==EGL_FALSE)
	{
		printf("Cant Make it current \n");
		exit(1);	
	} 	
	
	printf("success \n");

	glViewport(4,4,70,50);
	glClearColor(1.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	eglSwapBuffers(eglDisplay, eglSurface);
	getchar();
    wl_display_disconnect(display);
    printf("disconnected from display\n");
    
    exit(0);
}
