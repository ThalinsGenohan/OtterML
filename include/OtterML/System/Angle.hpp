#ifndef OTER_ANGLE_HPP
#define OTER_ANGLE_HPP

#include <compare>

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
	constexpr explicit Angle(float degrees);

	[[nodiscard]] constexpr float GetDegrees() const;
	[[nodiscard]] constexpr float GetRadians() const;

	void SetDegrees(float degrees);
	void SetRadians(float radians);

	Angle& WrapSigned();
	Angle& WrapUnsigned();

	[[nodiscard]] std::partial_ordering operator<=>(const Angle& right) const;


	// Binary angle operators
	Angle& operator+=(const Angle& right);
	Angle& operator-=(const Angle& right);

	// Binary float operators
	Angle& operator+=(const float& right);
	Angle& operator-=(const float& right);
	Angle& operator*=(const float& right);
	Angle& operator/=(const float& right);

	// Friend operators
	friend Angle operator-(const Angle& right);

	friend Angle operator+(Angle left, const Angle& right);
	friend Angle operator-(Angle left, const Angle& right);

	friend Angle operator+(Angle left, const float& right);
	friend Angle operator-(Angle left, const float& right);
	friend Angle operator*(Angle left, const float& right);
	friend Angle operator/(Angle left, const float& right);

	static const Angle Zero;

private:
	float _degrees = 0.f;
	float _radians = 0.f;

	bool _changed = false;
};

constexpr Angle::Angle(float degrees) : _degrees(degrees) { }

[[nodiscard]] constexpr float Angle::GetDegrees() const { return this->_degrees; }
[[nodiscard]] constexpr float Angle::GetRadians() const	{ return this->_radians; }

}

#endif
