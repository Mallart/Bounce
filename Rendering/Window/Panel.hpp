#include "./UIElement.hpp"

// 2D rendering
namespace Bounce::Render::UI
{
	BCLASS(Panel) : public UIElement
	{
	public:
		Panel() {};
		void Draw() override
		{
			UIElement::Draw();
		}
	};
}