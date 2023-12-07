#include <OtterML/Angle.hpp>

namespace oter
{

const Angle Angle::Zero(0.f);

constexpr Angle::Angle() : _degrees(0.f) { }

void Angle::SetDegrees(f32 degrees)
{
	this->_degrees = degrees;
	this->_radians = static_cast<f32>(degrees * (PI / 180.0));
}
void Angle::SetRadians(f32 radians)
{
	this->_radians = radians;
	this->_degrees = static_cast<f32>(radians * (180.0 / PI));
}

Angle& Angle::WrapSigned()
{
	this->SetDegrees(fmodf(this->_degrees + 180.f, 360.f) - 180.f);
	return *this;
}
Angle& Angle::WrapUnsigned()
{
	this->SetDegrees(fmodf(this->_degrees, 360.f));
	return *this;
}

Angle& Angle::operator+=(const Angle& right)
{
	this->SetDegrees(this->_degrees + right._degrees);
	return *this;
}
Angle& Angle::operator-=(const Angle& right)
{
	this->SetDegrees(this->_degrees - right._degrees);
	return *this;
}

Angle& Angle::operator+=(const f32& right)
{
	this->SetDegrees(this->_degrees + right);
	return *this;
}
Angle& Angle::operator-=(const f32& right)
{
	this->SetDegrees(this->_degrees - right);
	return *this;
}
Angle& Angle::operator*=(const f32& right)
{
	this->SetDegrees(this->_degrees * right);
	return *this;
}
Angle& Angle::operator/=(const f32& right)
{
	this->SetDegrees(this->_degrees / right);
	return *this;
}

Angle operator-(const Angle& right)
{
	return Angle(-right._degrees);
}

Angle operator+(Angle left, const Angle& right)
{
	left += right;
	return left;
}
Angle operator-(Angle left, const Angle& right)
{
	left -= right;
	return left;
}

Angle operator+(Angle left, const f32& right)
{
	left += right;
	return left;
}
Angle operator-(Angle left, const f32& right)
{
	left -= right;
	return left;
}
Angle operator*(Angle left, const f32& right)
{
	left *= right;
	return left;
}
Angle operator/(Angle left, const f32& right)
{
	left /= right;
	return left;
}

Angle operator""_d(long double value)
{
	return Angle(static_cast<f32>(value));
}

}
