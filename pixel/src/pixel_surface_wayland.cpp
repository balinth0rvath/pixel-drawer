#ifdef IMX6
#include "pixel_surface_wayland.h"

void PixelSurfaceWayland::initDisplayClient() {
    this->display = wl_display_connect(NULL);
    if (this->display == NULL) {
		std::cout << "Can't connect to display" << std::endl;
		
    }
    std::cout << "connected to display" << std::endl;
	this->registry = wl_display_get_registry(this->display);
	wl_registry_add_listener(this->registry, &this->listener, this->display); 
	wl_display_dispatch(this->display);
	wl_display_roundtrip(this->display);

	this->shell = PixelSurfaceWayland::shell;
	this->compositor = PixelSurfaceWayland::compositor;
	this->seat = PixelSurfaceWayland::seat;

	if (this->compositor == NULL)
	{
		std::cout << "error: no compositor" << std::endl;
		
	}

	this->surface = wl_compositor_create_surface(this->compositor);
	if (this->surface == NULL)
	{	
		std::cout << "Cannot create surface " << std::endl;
		
	}

	this->shell_surface = wl_shell_get_shell_surface(this->shell, this->surface);
	if (this->shell_surface == NULL)
	{	
		std::cout << "Cannot create shell surface " << std::endl;
		   
	}
	wl_shell_surface_set_toplevel(this->shell_surface);	
}

void PixelSurfaceWayland::closeDisplayClient()
{
    wl_display_disconnect(this->display);
    std::cout << "disconnected from display" << std::endl;
};

wl_shell* PixelSurfaceWayland::shell;
wl_seat* PixelSurfaceWayland::seat;
wl_compositor* PixelSurfaceWayland::compositor;

constexpr wl_registry_listener PixelSurfaceWayland::listener;
constexpr wl_seat_listener PixelSurfaceWayland::seatListener; 
constexpr wl_keyboard_listener PixelSurfaceWayland::keyboardListener; 
constexpr wl_pointer_listener PixelSurfaceWayland::pointerListener; 

void PixelSurfaceWayland::pointerEnter (	void *data, 	
							struct wl_pointer *pointer, 
							uint32_t serial, 
							struct wl_surface *surface, 
							wl_fixed_t surface_x, 
							wl_fixed_t surface_y)
{
	
}

void PixelSurfaceWayland::pointerLeave (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t serial, 
							struct wl_surface *surface)
{
	
} 

void PixelSurfaceWayland::pointerMotion (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t time, 
							wl_fixed_t x,
							wl_fixed_t y) 
{
	
}

void PixelSurfaceWayland::pointerButton (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t serial, 
							uint32_t time, 
							uint32_t button, 
							uint32_t state)
{
	
}
 
void PixelSurfaceWayland::pointerAxis (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t time, 
							uint32_t axis, 
							wl_fixed_t value)
{
	
} 

void PixelSurfaceWayland::keyboardKeymap (void *data, 	
							wl_keyboard *keyboard, 
							uint32_t format, 
							int32_t fd, 
							uint32_t size)
{
	
} 

void PixelSurfaceWayland::keyboardEnter (	void *data, 
							struct wl_keyboard *keyboard, 
							uint32_t serial, 
							struct wl_surface *surface, 
							struct wl_array *keys)
{
	
} 

void PixelSurfaceWayland::keyboardLeave (	void *data, 
							struct wl_keyboard *keyboard, 
							uint32_t serial, 
							struct wl_surface *surface)
{
	
} 

void PixelSurfaceWayland::keyboardKey (	void *data, 
							struct wl_keyboard *keyboard, 
							uint32_t serial, 
							uint32_t time, 
							uint32_t key, 
							uint32_t state)
{
	
}
 
void PixelSurfaceWayland::keyboardModifiers (	void *data, 
							struct wl_keyboard *keyboard, 
							uint32_t serial, 
							uint32_t mods_depressed, 
							uint32_t mods_latched, 
							uint32_t mods_locked, 
							uint32_t group)
{

} 


void PixelSurfaceWayland::objectAvailable(void* data, wl_registry *registry, uint32_t name, const char* interface, uint32_t version)
{
	std::cout << "new wayland global object: interface=" << interface << ", name=" << name << std::endl;
	if (strcmp(interface,"wl_compositor")==0)
	{
		PixelSurfaceWayland::compositor = static_cast<wl_compositor*>
			(wl_registry_bind(registry, name, &wl_compositor_interface, version)); 
		std::cout << "Compositor found" << std::endl;
		return;
	}
	if (strcmp(interface, "wl_shell")==0)
	{
		PixelSurfaceWayland::shell = static_cast<wl_shell*>
			(wl_registry_bind(registry, name, &wl_shell_interface, version));
		std::cout << "Shell found" << std::endl;
		return;
	}
	if (strcmp(interface, "wl_seat")==0)
	{
		PixelSurfaceWayland::seat = static_cast<wl_seat*>
			(wl_registry_bind(registry, name, &wl_seat_interface, version));
		wl_seat_add_listener(PixelSurfaceWayland::seat, &PixelSurfaceWayland::seatListener, NULL);
		std::cout << "Seat found" << std::endl;
		return;
	}
};

void PixelSurfaceWayland::objectRemoved(void* data, struct wl_registry *registry, uint32_t name)
{
	std::cout << "Wayland global object removed: name=" << name << std::endl;
};

void PixelSurfaceWayland::seatCapabilities(void* data, struct wl_seat *seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_POINTER) {
		std::cout << "WL_SEAT_CAPABILIT_POINTER listener added" << std::endl;
		struct wl_pointer *pointer = wl_seat_get_pointer (seat);
		wl_pointer_add_listener (pointer, &PixelSurfaceWayland::pointerListener, NULL);
	}
	
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) {
		std::cout << "WL_SEAT_CAPABILIT_KEYBOARD listener added" << std::endl;
		struct wl_keyboard *keyboard = wl_seat_get_keyboard (seat);
		wl_keyboard_add_listener (keyboard, &PixelSurfaceWayland::keyboardListener, NULL);
	}

}

void PixelSurfaceWayland::seatHandleName(void* data, wl_seat *seat, const char* name)
{
}
 
#endif // IMX6
