#include <OtterML/Color.hpp>

#include <OtterML/Vector3.hpp>
#include <OtterML/Vector4.hpp>

namespace oter
{

Color::operator Vector3<f32>() const
{
	return Vector3<f32>(
		static_cast<f32>(this->Red) / UINT8_MAX,
		static_cast<f32>(this->Green) / UINT8_MAX,
		static_cast<f32>(this->Blue) / UINT8_MAX
	);
}

Color::operator Vector4<f32>() const
{
	return Vector4<f32>(
		static_cast<f32>(this->Red) / UINT8_MAX,
		static_cast<f32>(this->Green) / UINT8_MAX,
		static_cast<f32>(this->Blue) / UINT8_MAX,
		static_cast<f32>(this->Alpha) / UINT8_MAX
	);
}

}
