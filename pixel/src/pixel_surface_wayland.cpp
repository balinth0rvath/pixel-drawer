#ifdef IMX6
#include "pixel_surface_wayland.h"
#include "pixel_controller.h"

void PixelSurfaceWayland::initDisplayClient() {
    this->display = wl_display_connect(NULL);
    if (this->display == NULL) {
		std::cout << "Can't connect to display" << std::endl;
		
    }
    std::cout << "connected to display" << std::endl;
	this->registry = wl_display_get_registry(this->display);
	wl_registry_add_listener(this->registry, &this->listener, this); 
	wl_display_dispatch(this->display);
	wl_display_roundtrip(this->display);

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

constexpr wl_registry_listener PixelSurfaceWayland::listener;
constexpr wl_seat_listener PixelSurfaceWayland::seatListener; 
constexpr wl_keyboard_listener PixelSurfaceWayland::keyboardListener; 
constexpr wl_pointer_listener PixelSurfaceWayland::pointerListener; 
constexpr wl_touch_listener PixelSurfaceWayland::touchListener; 

void PixelSurfaceWayland::pointerEnter (	void *data, 	
							struct wl_pointer *pointer, 
							uint32_t serial, 
							struct wl_surface *surface, 
							wl_fixed_t surface_x, 
							wl_fixed_t surface_y)
{
	std::cout << "pointer enter " << std::endl;
	
}

void PixelSurfaceWayland::pointerLeave (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t serial, 
							struct wl_surface *surface)
{
	std::cout << "pointer leave " << std::endl;
} 

void PixelSurfaceWayland::pointerMotion (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t time, 
							wl_fixed_t x,
							wl_fixed_t y) 
{
	std::cout << "motion x=" << x << " y=" << y << std::endl;
}

void PixelSurfaceWayland::pointerButton (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t serial, 
							uint32_t time, 
							uint32_t button, 
							uint32_t state)
{
	std::cout << "pointer button " << std::endl;

}
 
void PixelSurfaceWayland::pointerAxis (	void *data, 
							struct wl_pointer *pointer, 
							uint32_t time, 
							uint32_t axis, 
							wl_fixed_t value)
{
	std::cout << "pointer axis " << std::endl;
	
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
	PixelSurfaceWayland* pixelSurfaceWayland = reinterpret_cast<PixelSurfaceWayland*>(data);
	if (state)
	{
		pixelSurfaceWayland->pixelController->processKeyCode(key);
	}
}
 
void PixelSurfaceWayland::keyboardModifiers (void *data, 
							struct wl_keyboard *keyboard, 
							uint32_t serial, 
							uint32_t mods_depressed, 
							uint32_t mods_latched, 
							uint32_t mods_locked, 
							uint32_t group)
{

} 

void PixelSurfaceWayland::touchDown(void *data, 	
								struct wl_touch *wl_touch,
		  						uint32_t serial, 
								uint32_t time, 
								struct wl_surface *surface,
		  						int32_t id, 
								wl_fixed_t x_w, 
								wl_fixed_t y_w)
{
	uint32_t x = x_w >> 8;
	uint32_t y = y_w >> 8;
	std::cout << "DOWN@"  << x << " " << y << std::endl;
	
}

void PixelSurfaceWayland::touchUp(void *data, 
								struct wl_touch *wl_touch,
								uint32_t serial, 
								uint32_t time, 
								int32_t id)
{

}
	
void PixelSurfaceWayland::touchMotion(void *data, 
								struct wl_touch *wl_touch,
		    					uint32_t time, 
								int32_t id, 	
								wl_fixed_t x_w, 
								wl_fixed_t y_w)
{
	uint32_t x = x_w >> 8;
	uint32_t y = y_w >> 8;
	PixelSurfaceWayland* pixelSurfaceWayland = reinterpret_cast<PixelSurfaceWayland*>(data);
	pixelSurfaceWayland->pixelController->processButton(x,y,0);
}

void PixelSurfaceWayland::touchFrame(void *data, 
								struct wl_touch *wl_touch)
{

}

void PixelSurfaceWayland::touchCancel(void *data, 
								struct wl_touch *wl_touch)
{

}

void PixelSurfaceWayland::objectAvailable(void* data, wl_registry *registry, uint32_t name, const char* interface, uint32_t version)
{
	PixelSurfaceWayland* pixelSurfaceWayland = reinterpret_cast<PixelSurfaceWayland*>(data);
	std::cout << "new wayland global object: interface=" << interface << ", name=" << name << std::endl;
	if (strcmp(interface,"wl_compositor")==0)
	{
		pixelSurfaceWayland->compositor = static_cast<wl_compositor*>
			(wl_registry_bind(registry, name, &wl_compositor_interface, version)); 
		std::cout << "Compositor found" << std::endl;
		return;
	}
	if (strcmp(interface, "wl_shell")==0)
	{
		pixelSurfaceWayland->shell = static_cast<wl_shell*>
			(wl_registry_bind(registry, name, &wl_shell_interface, version));
		std::cout << "Shell found" << std::endl;
		return;
	}
	if (strcmp(interface, "wl_seat")==0)
	{
		pixelSurfaceWayland->seat = static_cast<wl_seat*>
			(wl_registry_bind(registry, name, &wl_seat_interface, version));
		wl_seat_add_listener(pixelSurfaceWayland->seat, &PixelSurfaceWayland::seatListener, data);
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
		wl_pointer_add_listener (pointer, &PixelSurfaceWayland::pointerListener, data);
	}
	
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) {
		std::cout << "WL_SEAT_CAPABILIT_KEYBOARD listener added" << std::endl;
		struct wl_keyboard *keyboard = wl_seat_get_keyboard (seat);
		wl_keyboard_add_listener (keyboard, &PixelSurfaceWayland::keyboardListener, data);
	}
	if (capabilities & WL_SEAT_CAPABILITY_TOUCH) {
		std::cout << "WL_SEAT_CAPABILIT_TOUCH listener added" << std::endl;
		struct wl_touch *touch = wl_seat_get_touch(seat);
		wl_touch_add_listener(touch, &PixelSurfaceWayland::touchListener, data);
	}

}

void PixelSurfaceWayland::seatHandleName(void* data, wl_seat *seat, const char* name)
{
}
 
#endif // IMX6
