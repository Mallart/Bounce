#include "../../include.hpp"
#include "../../Maths/Maths.hpp"
#include "../Misc/Color.hpp"
#include "../../GameLogic/Object.hpp"
#include "GL/glew.h"

// 2D rendering
namespace Bounce::Render::UI
{
	// Interface for all 2D elements that will be rendered on the screen
	BINTERFACE(UIElement)
	{
		BAPROPERTY(public, protected, Maths::Vector2, Origin);
		BAPROPERTY(public, protected, Maths::Vector2, Size);
		BAPROPERTY(public, protected, Color, BackgroundColor);
		BAPROPERTY(public, protected, Color, ForegroundColor);
		BAPROPERTY(public, protected, Color, StrokeColor);
		BAPROPERTY(public, protected, uint8_t, StrokeSize);

		BPROPERTY(protected, ::std::vector<RefUIElement>, Children);
	public:

		const Color DefaultBackgroundColor = 0x474747FF;
		const Color DefaultForegroundColor = 0xFFFFFFFF;
		const Color DefaultStrokeColor = 0x3E3E3EFF;
		const Color DefaultChildrenBackgroundColor = 0x2A2A2AFF;

		UIElement() : Origin{ 0, 0 }, Size{ 0, 0 }, StrokeSize{ 3 }, StrokeColor{ DefaultStrokeColor } {}
		// OpenGL draw.
		virtual void Draw() = 0;
		void AddChild(RefUIElement ui) { Children.push_back(ui); }
		void RemoveChild(RefUIElement ui) { for (size_t i = 0; i < Children.size(); ++i) if (ui == Children[i]) { Children.erase(Children.begin() + i, Children.begin() + i + 1); return; } }
	};

	// Holds all the UI to render 
	BCLASS(UIHolder) : public Object, public Render::Renderable
	{
	public:
		UIHolder() {}
		UIHolder(::std::initializer_list<RefUIElement> uiList) { UIElements = uiList; }
		::std::vector<RefUIElement> UIElements;
		void draw() override { for (RefUIElement ui : UIElements) ui->Draw(); }
		void AddElement(RefUIElement ui) { UIElements.push_back(ui); }
		void RemoveElement(RefUIElement ui) { for (size_t i = 0; i < UIElements.size(); ++i) if (ui == UIElements[i]) { UIElements.erase(UIElements.begin() + i, UIElements.begin() + i + 1); return; } }
	};
}