#ifdef IMX6
#include "pixel_surface_wayland.h"

wl_compositor *g_compositor;
wl_shell *g_shell;

void PixelSurfaceWayland::initDisplayClient() {
    this->display = wl_display_connect(NULL);
    if (this->display == NULL) {
		printf("Can't connect to display\n");
		exit(1);
    }
    printf("connected to display\n");
	this->registry = wl_display_get_registry(this->display);
	wl_registry_add_listener(this->registry, &this->listener, this->display); 
	wl_display_dispatch(this->display);
	wl_display_roundtrip(this->display);

	this->shell = g_shell;
	this->compositor = g_compositor;

	if (this->compositor == NULL)
	{
		std::cout << "error: no compositor" << std::endl;
		exit(1);
	}

	this->surface = wl_compositor_create_surface(this->compositor);
	if (this->surface == NULL)
	{	
		std::cout << "Cannot create surface " << std::endl;
		exit(1);
	}

	this->shell_surface = wl_shell_get_shell_surface(this->shell, this->surface);
	if (this->shell_surface == NULL)
	{	
		std::cout << "Cannot create shell surface " << std::endl;
		exit(1);   
	}
	wl_shell_surface_set_toplevel(this->shell_surface);	
	this->window = wl_egl_window_create(this->surface,this->windowWidth,this->windowHeight);
	std::cout << "done";
}


void PixelSurfaceWayland::global_object_available(void* data, struct wl_registry *registry, uint32_t name, const char* interface, uint32_t version)
{
	std::cout << "new wayland global object: interface=" << interface << ", name=" << name << std::endl;
	if (strcmp(interface,"wl_compositor")==0)
	{
		g_compositor = static_cast<wl_compositor*>(wl_registry_bind(registry, name, &wl_compositor_interface, version)); 
		printf("Compositor found \n");
		return;
	}
	if (strcmp(interface, "wl_shell")==0)
	{
		g_shell = static_cast<wl_shell*>(wl_registry_bind(registry, name, &wl_shell_interface, version));
		printf("Shell found\n");
		return;
	}
};

void PixelSurfaceWayland::global_object_removed(void* data, struct wl_registry *wl_registry, uint32_t name)
{
	printf("Wayland global object removed: name=%i\n", name);
};

void PixelSurfaceWayland::closeDisplayClient()
{
    wl_display_disconnect(this->display);
    std::cout << "disconnected from display" << std::endl;
};
 
#endif // IMX6
