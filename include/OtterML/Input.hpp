#ifndef OTER_INPUT_HPP
#define OTER_INPUT_HPP

#include <OtterML/Common.hpp>

namespace oter
{

class Input
{
public:
	constexpr auto MAX_KEYS = 1024;

	bool WasKeyJustPressed(u32 key);
	bool IsKeyHeld(u32 key);
	bool WasKeyJustReleased(u32 key);

	void SetKeyJustPressed(u32 key, bool state);
	void SetKeyHeld(u32 key, bool state);
	void SetKeyJustReleased(u32 key, bool state);

	bool GetKeyState(u32 key);

	void UpdateKeys();
};

}

#endif