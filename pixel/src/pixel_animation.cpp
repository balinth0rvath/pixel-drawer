#include "src/pixel_animation.h"

PixelAnimation::PixelAnimation(const GLuint& windowWidth, const GLuint& windowHeight)
{
	this->spherePosition = { 0.0f, 0.0f, -14.0f};
	this->sphereProjection = glm::perspective(45.0f, (GLfloat)windowWidth/(GLfloat)windowHeight, 0.1f, 100.0f);
	this->pixelAnimationState = PixelAnimationState::stoppedAway; 

}

void PixelAnimation::pushSphereBack()
{
	pixelAnimationState = PixelAnimationState::goingAway;	
}

void PixelAnimation::pullSphereFront()
{
	pixelAnimationState = PixelAnimationState::approaching;
}

void PixelAnimation::animateSphere()
{
	if (pixelAnimationState == PixelAnimationState::stoppedAway ||
		pixelAnimationState == PixelAnimationState::stoppedFront)
		return;

	switch (pixelAnimationState)
	{
		case PixelAnimationState::approaching:
			if (spherePosition.z >= minDistance)
			{
				pixelAnimationState = PixelAnimationState::stoppedFront;
			} else
			{
				spherePosition.z+=animationSpeed;
			}
			break;
		case PixelAnimationState::goingAway:
			if (spherePosition.z <= maxDistance)
			{
				pixelAnimationState = PixelAnimationState::stoppedAway;
			} else
			{
				spherePosition.z-=animationSpeed;
			}

		break;

		default:
		break;
	}
}

