#pragma once
#include "pixel_common_headers.h"
#include "pixel_surface.h"

class PixelSurfaceWayland : public PixelSurface {
public:
private:
	void initDisplayClient() override;
	void closeDisplayClient() override;
	void static global_object_available(void* data, struct wl_registry *registry, uint32_t name, const char* interface, uint32_t version);

	void static global_object_removed(void* data, struct wl_registry *wl_registry, uint32_t name);
 	wl_registry_listener listener = {
		global_object_available,
		global_object_removed
	};
};

