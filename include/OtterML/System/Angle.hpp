#ifndef OTER_ANGLE_HPP
#define OTER_ANGLE_HPP

namespace oter
{
class Angle
{
public:
	constexpr          Angle();
	constexpr explicit Angle(float degrees);

	[[nodiscard]] constexpr float GetDegrees() const;
	[[nodiscard]] constexpr float GetRadians() const;

	void SetDegrees();
	void SetRadians();

	Angle& WrapSigned();
	Angle& WrapUnsigned();

	auto operator<=>(const Angle&) const;

	static const Angle Zero;

private:
	float _degrees;
};

constexpr Angle::Angle() : _degrees(0.f) {}

constexpr Angle::Angle(float degrees) : _degrees(degrees) { }

constexpr float Angle::GetDegrees() const
{
	return this->_degrees;
}
}

#endif
