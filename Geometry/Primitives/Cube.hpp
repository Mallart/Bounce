#include "Primitive.hpp"

namespace Bounce::Geometry::Primitive
{
	BCLASS(Cube) : Primitive
	{
	public:
		Cube(float scale)
		{
			float vertices[] = 
			{
				-1, -1, -1, // a
				-1,  1, -1, // b
				 1,  1, -1, // c
				 1, -1, -1, // d
				 1, -1,  1, // e
				 1,  1,  1, // f
				-1,  1,  1, // g
				-1, -1,  1, // h

			};
			glGenBuffers(1, &VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}
	};
}