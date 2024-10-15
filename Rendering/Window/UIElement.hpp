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

		static const uint32_t DefaultBackgroundColor = 0x474747FF;
		static const uint32_t DefaultForegroundColor = 0xFFFFFFFF;
		static const uint32_t DefaultStrokeColor = 0x3E3E3EFF;
		static const uint32_t DefaultChildrenBackgroundColor = 0x2A2A2AFF;

		UIElement() : Origin{ 0, 0 }, Size{ 0, 0 }, StrokeSize{ 0 }, StrokeColor{ DefaultStrokeColor }, BackgroundColor{ DefaultBackgroundColor } {}
		// OpenGL draw.
		virtual void Draw()
		{
			size_t buffer_size = sizeof(GLubyte) * 4 * Size.x() * Size.y();
			GLubyte* pixels = (GLubyte*)malloc(buffer_size);
			if (!pixels)
				return;
			for (size_t i = 0; i + 3 < buffer_size;)
			{
				size_t
					x = i % (Size.x() * 4),
					y = llround((float)i / Size.x());
				// Draw Stroke
				if (
					x <= StrokeSize || x >= Size.x() * 4 - StrokeSize ||
					y <= StrokeSize || y >= Size.y() * 4 - StrokeSize
					)
				{
					pixels[i++] = StrokeColor.R();
					pixels[i++] = StrokeColor.G();
					pixels[i++] = StrokeColor.B();
					pixels[i++] = StrokeColor.A();
				}
				// Draw Background
				else
				{
					pixels[i++] = BackgroundColor.R();
					pixels[i++] = BackgroundColor.G();
					pixels[i++] = BackgroundColor.B();
					pixels[i++] = BackgroundColor.A();
				}
			}
			glWindowPos2i(Origin.x(), Origin.y());
			glDrawPixels(Size.x(), Size.y(), GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			free(pixels);
			for (RefUIElement ui : Children)
				ui->Draw();
		}
		void AddChild(RefUIElement ui) { Children.push_back(ui); }
		void RemoveChild(RefUIElement ui) { for (size_t i = 0; i < Children.size(); ++i) if (ui == Children[i]) { Children.erase(Children.begin() + i, Children.begin() + i + 1); return; } }
	};

	// Holds all the UI to render 
	BCLASS(UIHolder) : public Render::Renderable
	{
	public:
		UIHolder() {}
		UIHolder(::std::initializer_list<RefUIElement> uiList) { UIElements = uiList; }
		::std::vector<RefUIElement> UIElements;
		void Draw() override { for (RefUIElement ui : UIElements) ui->Draw(); }
		void AddElement(RefUIElement ui) { UIElements.push_back(ui); }
		void RemoveElement(RefUIElement ui) { for (size_t i = 0; i < UIElements.size(); ++i) if (ui == UIElements[i]) { UIElements.erase(UIElements.begin() + i, UIElements.begin() + i + 1); return; } }
	};
}