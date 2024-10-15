#include "../include.hpp"
#include "./Errors.hpp"
#include "../Rendering/Window/Panel.hpp"
// This file is intended to provide an easy way to display textual data in-editor and in-game.
// Usually also known as the "Dev console".

namespace Bounce::Debug
{
	BSCLASS(Console) : public Render::UI::Panel
	{
	public:
		Console() {};
		void Draw() override {}
		//::std::stringstream log;
	};
}