#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

// TODO: Probably add more to this when making a scene camera
namespace Cobalt
{
	struct PerspectiveProps
	{
		float FOV;
		float AspectRatio;
		float Near, Far;
	};

	class Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

	protected:
		
	};
}