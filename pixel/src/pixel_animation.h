#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_surface.h"

enum class PixelAnimationState;

class PixelAnimation {
public:
	PixelAnimation(const std::unique_ptr<PixelSurface>& pixelSurface);
	void pushSphereBack();
	void pullSphereFront();
	PixelAnimationState getSphereAnimationState() const { return this->pixelAnimationState; };
	void animateSphere();
	glm::vec3 getSpherePosition() const { return this->spherePosition; };
	GLfloat getSphereRotation() const { return this->sphereRotation; };
	glm::mat4 getSphereProjection() const { return this->sphereProjection; };
	void rotateSphere();

private:
	glm::vec3 spherePosition;
	GLfloat sphereRotation = 0;
	glm::mat4 sphereProjection;
	PixelAnimationState pixelAnimationState;
	const GLfloat animationSpeed = 0.4f;
	const GLfloat maxDistance = -14.0f;
	const GLfloat minDistance = -3.0f;
};

enum class PixelAnimationState : int
{
	stoppedFront	= 0,
	approaching 	= 1,
	stoppedAway 	= 2,
	goingAway 		= 3
};
