#include "../../include.hpp"

namespace Bounce::Render
{
	// Handles colors and transparency.
	BCLASS(Color)
	{
		BAPROPERTY(public, protected, uint32_t, HexValue);
		uint8_t CMax() { return R() > G() ? (R() > B() ? R() : (G() > B() ? G() : B())) : (G() > B() ? G() : B()); }
		uint8_t CMin() { return R() < G() ? (R() < B() ? R() : (G() < B() ? G() : B())) : (G() < B() ? G() : B()); }
	public:
		Color(uint32_t hexValue = 0) { HexValue = hexValue; }
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) { HexValue = (r << 24 + g << 16 + b << 8 + a); }
		Color(float r, float g, float b, float a = 1.f) { HexValue = (lround(r * 255) << 24 + lround(g * 255) << 16 + lround(b * 255) << 8 + lround(a * 255)); }

		// Returns the R (Red) component of this color.
		uint8_t R() { return HexValue & 0xFF000000; }
		// Returns the normalized (0..1) R (Red) component of this color.
		float nR() { return R() / 255.f; }
		// Returns the G (Green) component of this color.
		uint8_t G() { return HexValue & 0x00FF0000; }
		// Returns the normalized (0..1) G (Green) component of this color.
		float nG() { return G() / 255.f; }
		// Returns the B (Blue) component of this color.
		uint8_t B() { return HexValue & 0x0000FF00; }
		// Returns the normalized (0..1) B (Blue) component of this color.
		float nB() { return B() / 255.f; }
		// Returns the A (alpha) component of this color.
		uint8_t A() { return HexValue & 0x000000FF; }
		// Returns the normalized (0..1) A (Alpha) component of this color.
		float nA() { return A() / 255.f; }

		uint8_t Luminosity() { return (R() + G() + B()) / 3.f; }
		uint8_t Saturation()
		{
			uint8_t cmax = CMax();
			uint8_t cmin = CMin();
			return cmax ? (cmax - cmin) / (float)cmax : 0;
		}
	};
}