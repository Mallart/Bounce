#pragma once
#include "../include.hpp"

namespace Bounce::Geometry
{
	BCLASS(Geometry)
	{
		BAPROPERTY(public, protected, sf::VertexArray, Vertices)
	public:
		Geometry(sf::VertexArray _Vertices)
		{
			Vertices = _Vertices;
			for (size_t i = 0; i < Vertices.getVertexCount(); ++i)
				Vertices[i].color = sf::Color::Magenta;
		}
	};
}