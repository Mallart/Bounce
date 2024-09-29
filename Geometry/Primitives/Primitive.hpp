#pragma once
#include "../../include.hpp"
#include <GL/glew.h>

namespace Bounce::Geometry::Primitive
{
	// Simple 3D shape
	BCLASS(Primitive)
	{
		BAPROPERTY(public, protected, float*, Vertices)
			// Vertex Buffer Object
		BAPROPERTY(public, protected, GLuint, VBO)
	public:
		Primitive(float* _Vertices, uint64_t _NumberOfVertices)
		{
			Vertices = _Vertices;
			glGenBuffers(1, &VBO);
		}
	};
}