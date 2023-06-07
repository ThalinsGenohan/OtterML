#ifndef OTER_FIXEDPOINT_H
#define OTER_FIXEDPOINT_H

#include <compare>
#include <cstdint>

namespace oter
{
template <typename Tw, typename Tf>
struct FixedPoint
{
public:
	FixedPoint() : FixedPoint(static_cast<Tw>(0), static_cast<Tf>(0)) { }
	explicit FixedPoint(const Tw whole) : FixedPoint(whole, static_cast<Tf>(0)) { }
	FixedPoint(const Tw whole, const Tf fraction) : Whole(whole), Fraction(fraction)
	{
		static_assert(!std::is_floating_point_v<Tw>, "oter::FixedPoint only supports integers as wholes.");
		static_assert(std::is_unsigned_v<Tf>, "oter::FixedPoint only supports unsigned integers as fractions.");
	}

	template <typename U, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
	explicit FixedPoint(const U floatingPoint) : Whole(static_cast<Tw>(floor(floatingPoint)))
	{
		static_assert(!std::is_floating_point_v<Tw>, "oter::FixedPoint only supports integers as wholes.");
		static_assert(std::is_unsigned_v<Tf>, "oter::FixedPoint only supports unsigned integers as fractions.");

		const U fraction = floatingPoint - this->Whole;
		this->Fraction = static_cast<Tf>(floor(this->FRACTION_MAX * fraction));
	}

	FixedPoint(const FixedPoint& other) : Whole(other.Whole), Fraction(other.Fraction) { }

	explicit operator float() const
	{
		return static_cast<float>(this->Whole) + static_cast<float>(this->Fraction) / static_cast<float>(this->FRACTION_MAX);
	}

	explicit operator double() const
	{
		return static_cast<double>(this->Whole) + static_cast<double>(this->Fraction) / static_cast<double>(this->FRACTION_MAX);
	}

	[[nodiscard]] constexpr Tw Floor() const;
	[[nodiscard]] constexpr Tw Round() const;
	[[nodiscard]] constexpr Tw Ceiling() const;

	template <typename Uw, typename Uf>
	[[nodiscard]] constexpr std::strong_ordering operator<=>(const FixedPoint<Uw, Uf>& right) const
	{
		if (this->Whole > right.Whole)
			return std::strong_ordering::greater;
		if (this->Whole < right.Whole)
			return std::strong_ordering::less;

		if (this->Fraction > right.Fraction)
			return std::strong_ordering::greater;
		if (this->Fraction < right.Fraction)
			return std::strong_ordering::less;

		return std::strong_ordering::equal;
	}

	template <typename U>
	[[nodiscard]] constexpr std::strong_ordering operator<=>(const U& right) const;

	// Member operators
	// Unary operators
	friend FixedPoint operator-(const FixedPoint& right)
	{
		static_assert(std::is_signed_v<Tw>, "FixedPoint::operator-() is only supported for signed whole types.");

		if (right.Fraction == 0)
			return FixedPoint(-right.Whole, right.Fraction);

		const Tw negativeWhole = -right.Whole - 1;
		const Tf negativeFraction = right.FRACTION_MAX + 1 - right.Fraction;
		return FixedPoint(negativeWhole, negativeFraction);
	}

	// Binary operators
	FixedPoint& operator+=(const FixedPoint& right)
	{
		// Add wholes
		this->Whole += right.Whole;

		// Save fraction for overflow checking and add fractions
		const Tf tempFrac = this->Fraction;
		this->Fraction += right.Fraction;

		// Check overflow
		if (this->Fraction < tempFrac)
			this->Whole++;

		return *this;
	}
	FixedPoint& operator-=(const FixedPoint& right)
	{
		// Add wholes
		this->Whole -= right.Whole;

		// Save fraction for overflow checking and add fractions
		const Tf tempFrac = this->Fraction;
		this->Fraction -= right.Fraction;

		// Check overflow
		if (this->Fraction > tempFrac)
			this->Whole--;

		return *this;
	}
	FixedPoint& operator*=(const FixedPoint& right)
	{
		const uint64_t fractionProduct = this->Fraction * right.Whole + right.Fraction * this->Whole + (this->Fraction * right.Fraction / this->FRACTION_MAX);
		this->Whole *= right.Whole;
		if (fractionProduct > this->FRACTION_MAX)
			this->Whole += fractionProduct / this->FRACTION_MAX;
		this->Fraction = static_cast<Tf>(fractionProduct);

		return *this;
	}
	FixedPoint& operator/=(const FixedPoint& right);

	template <typename U>
	FixedPoint& operator+=(const U& right)
	{
		static_assert(!std::is_floating_point_v<U>);

		this->Whole += right;
		return *this;
	}
	template <typename U, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
	FixedPoint& operator+=(const U& right)
	{
		static_assert(std::is_floating_point_v<U>);

		return *this + FixedPoint(right);
	}

	template <typename U>
	FixedPoint& operator-=(const U& right)
	{
		static_assert(!std::is_floating_point_v<U>);

		this->Whole -= right;
		return *this;
	}
	template <typename U, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
	FixedPoint& operator-=(const U& right)
	{
		static_assert(std::is_floating_point_v<U>);

		return *this - FixedPoint(right);
	}

	template <typename U>
	FixedPoint& operator*=(const U& right)
	{
		static_assert(!std::is_floating_point_v<U>);

		if (right == 1)
			return *this;
		if (right == 0)
		{
			this->Whole = static_cast<Tw>(0);
			this->Fraction = static_cast<Tf>(0);
			return *this;
		}
		if (right == -1)
		{
			*this = -(*this);
			return *this;
		}

		U r = right;
		if (r < 0)
			r *= -1;

		const uint64_t fractionProduct = this->Fraction * right;
		this->Whole *= right;
		if (fractionProduct > this->FRACTION_MAX)
			this->Whole += fractionProduct / this->FRACTION_MAX;
		this->Fraction = static_cast<Tf>(fractionProduct);

		if (right < 0)
			*this = -(*this);

		return *this;
	}
	template <typename U, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
	FixedPoint& operator*=(const U& right)
	{
		static_assert(std::is_floating_point_v<U>);

		return *this * FixedPoint(right);
	}

	template <typename U>
	FixedPoint& operator/=(const U& right)
	{
		static_assert(!std::is_floating_point_v<U>);

		this->Whole /= right;
		return *this;
	}
	template <typename U, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
	FixedPoint& operator/=(const U& right)
	{
		static_assert(std::is_floating_point_v<U>);

		return *this / FixedPoint(right);
	}

	// Friend operators
	// Binary operators
	friend FixedPoint operator+(FixedPoint left, const FixedPoint& right)
	{
		left += right;
		return left;
	}
	friend FixedPoint operator-(FixedPoint left, const FixedPoint& right)
	{
		left -= right;
		return left;
	}
	friend FixedPoint operator*(FixedPoint left, const FixedPoint& right)
	{
		left *= right;
		return left;
	}
	friend FixedPoint operator/(FixedPoint left, const FixedPoint& right)
	{
		left /= right;
		return left;
	}

	template <typename U>
	friend FixedPoint operator+(FixedPoint left, const U& right)
	{
		return left += right;
	}
	template <typename U>
	friend FixedPoint operator-(FixedPoint left, const U& right)
	{
		return left -= right;
	}
	template <typename U>
	friend FixedPoint operator*(FixedPoint left, const U& right)
	{
		return left *= right;
	}
	template <typename U>
	friend FixedPoint operator/(FixedPoint left, const U& right)
	{
		return left /= right;
	}

	Tw Whole;
	Tf Fraction;

	static const Tf FRACTION_MAX = static_cast<Tf>(static_cast<Tf>(0) - 1);
};

}

#endif
