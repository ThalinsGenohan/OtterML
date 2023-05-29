#include <OtterML/System/Angle.hpp>

namespace oter
{

const Angle Angle::Zero(0.f);

constexpr Angle::Angle() : _degrees(0.f) { }
constexpr Angle::Angle(float degrees) : _degrees(degrees) { }

void Angle::SetDegrees(float degrees)
{
	this->_degrees = degrees;
	this->_radians = degrees * (PI / 180.0);
}
void Angle::SetRadians(float radians)
{
	this->_radians = radians;
	this->_degrees = radians * (180.0 / PI);
}

[[nodiscard]] std::partial_ordering Angle::operator<=>(const Angle& right) const
{
	return this->_degrees <=> right._degrees;
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

Angle& Angle::operator+=(const float& right)
{
	this->SetDegrees(this->_degrees + right);
	return *this;
}
Angle& Angle::operator-=(const float& right)
{
	this->SetDegrees(this->_degrees - right);
	return *this;
}
Angle& Angle::operator*=(const float& right)
{
	this->SetDegrees(this->_degrees * right);
	return *this;
}
Angle& Angle::operator/=(const float& right)
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

Angle operator+(Angle left, const float& right)
{
	left += right;
	return left;
}
Angle operator-(Angle left, const float& right)
{
	left -= right;
	return left;
}
Angle operator*(Angle left, const float& right)
{
	left *= right;
	return left;
}
Angle operator/(Angle left, const float& right)
{
	left /= right;
	return left;
}

}
