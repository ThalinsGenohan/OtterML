#ifndef OTER_VECTOR2_HPP
#define OTER_VECTOR2_HPP

#include <glm/vec2.hpp>
#include <yaml-cpp/yaml.h>

namespace oter
{
template <typename T, unsigned Tx, unsigned Ty>
class Matrix;

template <typename T>
struct Vector2
{
public:
	T X = static_cast<T>(0);
	T Y = static_cast<T>(0);

	/**
	 * \brief Default constructor
	 *
	 * Creates a Vector2(0, 0)
	 */
	Vector2();

	/**
	 * \brief Construct a Vector2 from coordinates
	 * \param x X coordinate
	 * \param y Y coordinate
	 */
	Vector2(T x, T y);

	/**
	 * \brief Construct a Vector2 from a scalar value
	 * \param scalar Scalar value for both coordinates
	 */
	explicit Vector2(T scalar);

	/**
	 * \brief Construct a Vector2 from a different Vector2
	 *
	 * Does not replace copy constructor
	 * \param other Vector to convert
	 */
	template <typename U>
	explicit Vector2(const Vector2<U>& other);

	/**
	* /brief Copy constructor
	*/
	Vector2(const Vector2& other);

	/**
	 * \brief Construct a Vector2 from a glm::vec<2, U>
	 * \param glmVec glm::vec<2, U> to convert
	 */
	template <typename U>
	explicit Vector2(const glm::vec<2, U>& glmVec) : Vector2(static_cast<T>(glmVec.x), static_cast<T>(glmVec.y)) { }

	/**
	 * \brief Convert to a glm::vec<2, U>
	 */
	template <typename U>
	explicit operator glm::vec<2, U>() const
	{
		return glm::vec<2, U>(static_cast<U>(this->X), static_cast<U>(this->Y));
	}
	
	/**
	 * \brief Convert to a 2x1 oter::Matrix
	 */
	explicit operator Matrix<T, 1, 2>() const;

	/**
	 * \brief Compares two Vector2s
	 * \param right Vector2 to compare to
	 * \return True if Vector2s are equal
	 */
	[[nodiscard]] constexpr bool operator==(const Vector2& right) const;

	[[nodiscard]] constexpr float GetLength();
	[[nodiscard]] constexpr float GetLengthSquared();

	[[nodiscard]] Vector2 GetNormalized();

	[[nodiscard]] T Dot(const Vector2& right);
	[[nodiscard]] T Cross(const Vector2& right);

	// Member operators
	// Unary operators
	Vector2 operator-(const Vector2& right);

	// Binary scalar operators
	Vector2& operator+=(const T& right);
	Vector2& operator-=(const T& right);
	Vector2& operator*=(const T& right);
	Vector2& operator/=(const T& right);

	// Binary vector operators
	template <typename U>
	Vector2& operator+=(const Vector2<U>& right);
	template <typename U>
	Vector2& operator-=(const Vector2<U>& right);
	template <typename U>
	Vector2& operator*=(const Vector2<U>& right);
	template <typename U>
	Vector2& operator/=(const Vector2<U>& right);

	// Friend operators
	// Binary scalar operators
	friend Vector2 operator+(Vector2 left, const T& right)
	{
		left += right;
		return left;
	}
	friend Vector2 operator-(Vector2 left, const T& right)
	{
		left -= right;
		return left;
	}
	friend Vector2 operator*(Vector2 left, const T& right)
	{
		left *= right;
		return left;
	}
	friend Vector2 operator/(Vector2 left, const T& right)
	{
		left /= right;
		return left;
	}

	// Binary vector operators
	template <typename U>
	friend Vector2 operator+(Vector2 left, const Vector2<U>& right)
	{
		left += right;
		return left;
	}
	template <typename U>
	friend Vector2 operator-(Vector2 left, const Vector2<U>& right)
	{
		left -= right;
		return left;
	}
	template <typename U>
	friend Vector2 operator*(Vector2 left, const Vector2<U>& right)
	{
		left *= right;
		return left;
	}
	template <typename U>
	friend Vector2 operator/(Vector2 left, const Vector2<U>& right)
	{
		left /= right;
		return left;
	}

	// Static declarations
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};
}

template <typename T>
oter::Vector2<T>::Vector2() : Vector2(static_cast<T>(0)) {}

template <typename T>
oter::Vector2<T>::Vector2(T x, T y) : X(x), Y(y) {}

template <typename T>
oter::Vector2<T>::Vector2(T scalar) : X(scalar), Y(scalar) {}

template <typename T>
template <typename U>
oter::Vector2<T>::Vector2(const oter::Vector2<U>& other) : X(static_cast<T>(other.X)), Y(static_cast<T>(other.Y)) {}

template <typename T>
oter::Vector2<T>::Vector2(const oter::Vector2<T>& other) : X(other.X), Y(other.Y) {}

template <typename T>
T oter::Vector2<T>::Dot(const oter::Vector2<T>& right)
{
	return this->X * right.X + this->Y * right.Y;
}

template <typename T>
T oter::Vector2<T>::Cross(const oter::Vector2<T>& right)
{
	return this->X * right.X - this->Y * right.Y;
}

template <typename T>
constexpr bool oter::Vector2<T>::operator==(const oter::Vector2<T>& right) const
{
	return this->X == right.X && this->Y == right.Y;
}

template <typename T>
oter::Vector2<T> oter::Vector2<T>::operator-(const Vector2<T>& right)
{
	return Vector2<T>(-right.X, -right.Y);
}

template <typename T>
oter::Vector2<T>& oter::Vector2<T>::operator+=(const T& right)
{
	this->X += right;
	this->Y += right;
	return *this;
}

template <typename T>
oter::Vector2<T>& oter::Vector2<T>::operator-=(const T& right)
{
	this->X -= right;
	this->Y -= right;
	return *this;
}

template <typename T>
oter::Vector2<T>& oter::Vector2<T>::operator*=(const T& right)
{
	this->X *= right;
	this->Y *= right;
	return *this;
}

template <typename T>
oter::Vector2<T>& oter::Vector2<T>::operator/=(const T& right)
{
	this->X /= right;
	this->Y /= right;
	return *this;
}

// I have no idea why this has to have two separate template definitions instead of a comma
template <typename T>
template <typename U>
oter::Vector2<T>& oter::Vector2<T>::operator+=(const oter::Vector2<U>& right)
{
	this->X += right.X;
	this->Y += right.Y;
	return *this;
}

template <typename T>
template <typename U>
oter::Vector2<T>& oter::Vector2<T>::operator-=(const oter::Vector2<U>& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	return *this;
}

template <typename T>
template <typename U>
oter::Vector2<T>& oter::Vector2<T>::operator*=(const oter::Vector2<U>& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	return *this;
}

template <typename T>
template <typename U>
oter::Vector2<T>& oter::Vector2<T>::operator/=(const oter::Vector2<U>& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	return *this;
}

// Static definitions
template <typename T>
const oter::Vector2<T> oter::Vector2<T>::Zero(static_cast<T>(0));
template <typename T>
const oter::Vector2<T> oter::Vector2<T>::UnitX(static_cast<T>(1), static_cast<T>(0));
template <typename T>
const oter::Vector2<T> oter::Vector2<T>::UnitY(static_cast<T>(0), static_cast<T>(1));

template <typename T>
struct YAML::convert<oter::Vector2<T>>
{
public:
	static Node encode(const oter::Vector2<T>& right)
	{
		Node node;
		node["x"] = right.X;
		node["y"] = right.Y;
		return node;
	}

	static bool decode(const Node& node, oter::Vector2<T>& right)
	{
		if (node.IsSequence())
			return decode_sequence(node, right);
		if (node.IsMap())
			return decode_map(node, right);

		return false;
	}

private:
	static bool decode_sequence(const Node& node, oter::Vector2<T>& right)
	{
		if (!node.IsSequence() || node.size() != 2)
			return false;

		right.X = node[0].as<T>();
		right.Y = node[1].as<T>();
		return true;
	}
	static bool decode_map(const Node& node, oter::Vector2<T>& right)
	{
		if (!node.IsMap() || node.size() != 2)
			return false;

		right.X = node["x"].as<T>();
		right.Y = node["y"].as<T>();
		return true;
	}
};

#endif
