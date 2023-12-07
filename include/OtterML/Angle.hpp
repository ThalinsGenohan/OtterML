#ifndef OTER_ANGLE_HPP
#define OTER_ANGLE_HPP

#include <OtterML/Common.hpp>

namespace oter
{
constexpr auto PI = 3.141592653589793238462643383279502884L;

/**
* \brief Represents an angle, which can be defined as a value of degrees or radians. All ambiguous operations use degrees as default.
*/
class Angle
{
public:
	constexpr          Angle();
	constexpr explicit Angle(f32 degrees);

	[[nodiscard]] constexpr f32 GetDegrees() const;
	[[nodiscard]] constexpr f32 GetRadians() const;

	void SetDegrees(f32 degrees);
	void SetRadians(f32 radians);

	Angle& WrapSigned();
	Angle& WrapUnsigned();

	friend bool operator<(const Angle& left, const Angle& right) { return left._degrees < right._degrees; }
	friend bool operator>(const Angle& left, const Angle& right) { return right < left; }
	friend bool operator<=(const Angle& left, const Angle& right) { return !(left > right); }
	friend bool operator>=(const Angle& left, const Angle& right) { return !(left < right); }
	// TODO: Fix this to be proper f32 comparison
	friend bool operator==(const Angle& left, const Angle& right) { return left._degrees == right._degrees; }
	friend bool operator!=(const Angle& left, const Angle& right) { return !(left == right); }

	// Binary angle operators
	Angle& operator+=(const Angle& right);
	Angle& operator-=(const Angle& right);

	// Binary f32 operators
	Angle& operator+=(const f32& right);
	Angle& operator-=(const f32& right);
	Angle& operator*=(const f32& right);
	Angle& operator/=(const f32& right);

	// Friend operators
	friend Angle operator-(const Angle& right);

	friend Angle operator+(Angle left, const Angle& right);
	friend Angle operator-(Angle left, const Angle& right);

	friend Angle operator+(Angle left, const f32& right);
	friend Angle operator-(Angle left, const f32& right);
	friend Angle operator*(Angle left, const f32& right);
	friend Angle operator/(Angle left, const f32& right);

	static const Angle Zero;

private:
	f32 _degrees = 0.f;
	f32 _radians = 0.f;

	bool _changed = false;
};

Angle operator""_d(long double value);

constexpr Angle::Angle(f32 degrees) : _degrees(degrees) { }

[[nodiscard]] constexpr f32 Angle::GetDegrees() const { return this->_degrees; }
[[nodiscard]] constexpr f32 Angle::GetRadians() const	{ return this->_radians; }

}

#endif
