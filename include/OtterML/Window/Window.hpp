#ifndef OTER_WINDOW_HPP
#define OTER_WINDOW_HPP

namespace oter
{

class Color;

template <typename T>
struct Vector2;

class Window
{
public:
	Window(u16 width, u16 height, const std::string& title);
	Window(Vector2<u16> size, const std::string& title);
	~Window();

	void Clear(const Color& color);
	void Draw(void* object);
	void Display();
}

}

#endif
