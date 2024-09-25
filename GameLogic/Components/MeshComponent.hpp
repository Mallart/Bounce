#include "Component.hpp"
#include "../../Geometry/Geometry.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Bounce::Components
{
	BCLASS(MeshComponent) : public Component
	{
		BAPROPERTY(public, protected, Geometry::Geometry, Shape)
		BAPROPERTY(public, protected, ::sf::Texture, Shape)
	public:
		MeshComponent();
	};
}