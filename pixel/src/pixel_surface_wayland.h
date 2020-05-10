#pragma once
#include "pixel_common_headers.h"
#include "pixel_surface.h"

class PixelSurfaceWayland : public PixelSurface {
public:
	static void seatCapabilities(void* data, wl_seat *seat, uint32_t capabilities);
private:
	void initDisplayClient() override;
	void closeDisplayClient() override;
	static void objectAvailable(void* data, wl_registry *registry, uint32_t name, const char* interface, uint32_t version);

	static void objectRemoved(void* data, wl_registry *registry, uint32_t name);

 	wl_registry_listener listener = {
		objectAvailable,
		objectRemoved
	};
public:
	static void pointerEnter (	void *data, 	
								struct wl_pointer *pointer, 
								uint32_t serial, 
								struct wl_surface *surface, 
								wl_fixed_t surface_x, 
								wl_fixed_t surface_y);
	static void pointerLeave (	void *data, 
								struct wl_pointer *pointer, 
								uint32_t serial, 
								struct wl_surface *surface); 
	static void pointerMotion (	void *data, 
								struct wl_pointer *pointer, 
								uint32_t time, 
								wl_fixed_t x,
								wl_fixed_t y); 
	static void pointerButton (	void *data, 
								struct wl_pointer *pointer, 
								uint32_t serial, 
								uint32_t time, 
								uint32_t button, 
								uint32_t state); 
	static void pointerAxis (	void *data, 
								struct wl_pointer *pointer, 
								uint32_t time, 
								uint32_t axis, 
								wl_fixed_t value); 

	static void keyboardKeymap (void *data, 	
								wl_keyboard *keyboard, 
								uint32_t format, 
								int32_t fd, 
								uint32_t size); 

	static void keyboardEnter (	void *data, 
								struct wl_keyboard *keyboard, 
								uint32_t serial, 
								struct wl_surface *surface, 
								struct wl_array *keys); 
	
	static void keyboardLeave (	void *data, 
								struct wl_keyboard *keyboard, 
								uint32_t serial, 
								struct wl_surface *surface); 
	
	static void keyboardKey (	void *data, 
								struct wl_keyboard *keyboard, 
								uint32_t serial, 
								uint32_t time, 
								uint32_t key, 
								uint32_t state); 
	static void keyboardModifiers (	void *data, 
								struct wl_keyboard *keyboard, 
								uint32_t serial, 
								uint32_t mods_depressed, 
								uint32_t mods_latched, 
								uint32_t mods_locked, 
								uint32_t group); 



};

static wl_keyboard_listener keyboardListener = {
							&PixelSurfaceWayland::keyboardKeymap, 
							&PixelSurfaceWayland::keyboardEnter, 
							&PixelSurfaceWayland::keyboardLeave, 
							&PixelSurfaceWayland::keyboardKey, 
							&PixelSurfaceWayland::keyboardModifiers};

static wl_pointer_listener pointerListener = {
							&PixelSurfaceWayland::pointerEnter, 
							&PixelSurfaceWayland::pointerLeave, 
							&PixelSurfaceWayland::pointerMotion, 
							&PixelSurfaceWayland::pointerButton, 			
							&PixelSurfaceWayland::pointerAxis};
