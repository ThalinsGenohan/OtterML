#ifndef OTER_COLOR_HPP
#define OTER_COLO_HPP

#include <OtterML/Common.hpp>

namespace oter
{

template <typename T>
struct Vector3;

template <typename T>
struct Vector4;

struct Color
{
public:
	u8 Red   = 0x00;
	u8 Green = 0x00;
	u8 Blue  = 0x00;
	u8 Alpha = 0x00;

	Color() {}

	Color(const u8 red, const u8 green, const u8 blue, const u8 alpha = 0xFF)
		: Red(red), Green(green), Blue(blue), Alpha(alpha) {}

	explicit operator Vector3<f32>() const;
	explicit operator Vector4<f32>() const;
};

}

#endif
