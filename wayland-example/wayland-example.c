// cc -o wex wayland-example.c -lwayland-client -lEGL 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <EGL/egl.h>

EGLint major, minor;

struct wl_display *display = NULL;
struct wl_compositor *compositor = NULL;
struct wl_shell *shell = NULL;

// wl_display_get_registry
// wl_registry_add_listener
// wl_registry_listener
// wl_compositor

// wl_display_dispatch
// wl_display_roundtrip

// wl_compositor_create_surface
// wl_shell_get_shell_surface
// wl_shell_surface_set_toplevel

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

void egl_init()
{
	EGLDisplay eglDisplay = eglGetDisplay((EGLNativeDisplayType)display);

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

}

int main(int argc, char **argv) {

    display = wl_display_connect(NULL);
    if (display == NULL) {
		fprintf(stderr, "Can't connect to display\n");
		exit(1);
    }
    printf("connected to display\n");
	struct wl_regisry* registry = wl_display_get_registry(display);
	wl_registry_add_listener(registry, &listener, NULL); 

	wl_display_dispatch(display);
	wl_display_roundtrip(display);

	if (compositor == NULL)
	{
		printf("error: no compositor\n");
		return -1;
	}

	struct wl_surface* surface = wl_compositor_create_surface(compositor);
	if (surface == NULL)
	{	
		printf("Cannot create surface \n");
		return -1;
	}

	struct wl_shell_surface* shell_surface = wl_shell_get_shell_surface(shell, surface);

	if (shell_surface == NULL)
	{	
		printf("Cannot create shell surface \n");
		return -1;
	}

	wl_shell_surface_set_toplevel(shell_surface);	

	egl_init();
    wl_display_disconnect(display);
    printf("disconnected from display\n");
    
    exit(0);
}
