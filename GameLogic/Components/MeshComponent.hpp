#include "Component.hpp"
#include "../../Geometry/Geometry.hpp"

namespace Bounce::Components
{
	BCLASS(MeshComponent) : public Component
	{
		BAPROPERTY(public, protected, Geometry::Geometry, Shape)
	public:
		MeshComponent();
		virtual void Init() {};
		virtual void Start() {};
		virtual void End() {};
		virtual void Update() {};
	};
}