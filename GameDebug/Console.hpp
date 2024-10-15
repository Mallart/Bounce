#include "../include.hpp"
#include "./Errors.hpp"
#include "../Rendering/Window/Panel.hpp"

#define BLOG(_warnLevel, _message) Log(_warnLevel, __FILE__ + "(" + __LINE__ + "): " + _message)

// This file is intended to provide an easy way to display textual data in-editor and in-game.
// Usually also known as the "Dev console".

namespace Bounce::Debug
{
  
	BSCLASS(Console) : public Render::UI::Panel
	{
		BPROPERTY(protected, ::std::string, Logs)
	public:
  enum MessageType
		{
			// Casual messages, logs without any real importance.
			Message,
			// Important informations regarding the program.
			Info,
			// Warnings about the engine, runtime or any component.
			Warning,
			// Error that prevents the engine, game or simulation to work properly.
			Error,
		};
		Console() { Size = {512, 256}; StrokeSize = 20; BackgroundColor = {UIElement::DefaultBackgroundColor}; };
    void Draw() override 
		{
			Panel::Draw();
		}

		// Adds a message in that console.
		void Log(MessageType warnLevel, ::std::string message)
		{
			::std::string _mt;
			switch (warnLevel)
			{
			case Message: _mt = "Message"; break;
			case Info: _mt = "Info"; break;
			case Warning: _mt = "Warning"; break;
			case Error: _mt = "Error"; break;
			}
			Logs.append('\n' + _mt + ": " + message);
		}

		// Saves the content of this console in a file and clears it.
		void Flush()
		{
			IO::Log("./console_out.log", Logs);
			Logs.clear();
		}
		
		//::std::stringstream log;
	};
}