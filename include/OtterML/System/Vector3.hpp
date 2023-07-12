#ifndef OTER_VECTOR3_HPP
#define OTER_VECTOR3_HPP

#include <OtterML/Common.hpp>

namespace oter
{
template <typename T, unsigned Tx, unsigned Ty>
class Matrix;

template <typename T>
struct Vector3
{
public:
	T X = static_cast<T>(0);
	T Y = static_cast<T>(0);
	T Z = static_cast<T>(0);

	/**
	 * \brief Default constructor
	 *
	 * Creates a Vector3(0, 0, 0)
	 */
	Vector3();

	/**
	 * \brief Construct a Vector3 from coordinates
	 * \param x X coordinate
	 * \param y Y coordinate
	 * \param z Z coordinate
	 */
	Vector3(T x, T y, T z);

	/**
	 * \brief Construct a Vector3 from a scalar value
	 * \param scalar Scalar value for all three coordinates
	 */
	explicit Vector3(T scalar);

	/**
	 * \brief Construct a Vector3 from a different Vector3
	 *
	 * Does not replace copy constructor
	 * \param other Vector to convert
	 */
	template <typename U>
	explicit Vector3(const Vector3<U>& other);

	/**
	 * \brief Construct a Vector3 from a glm::vec3
	 * \param glmVec glm::vec3 to convert
	 */
	explicit Vector3(const glm::vec3& glmVec);

	/**
	 * \brief Construct a Vector3 from a glm::ivec3
	 * \param glmVec glm::ivec3 to convert
	 */
	explicit Vector3(const glm::ivec3& glmVec);

	/**
	 * \brief Construct a Vector3 from a glm::uvec3
	 * \param glmVec glm::uvec3 to convert
	 */
	explicit Vector3(const glm::uvec3& glmVec);

	/**
	 * \brief Convert to a glm::vec3
	 */
	explicit operator glm::vec3() const;

	/**
	 * \brief Convert to a glm::uvec3
	 */
	explicit operator glm::uvec3() const;

	/**
	 * \brief Convert to a glm::ivec3
	 */
	explicit operator glm::ivec3() const;

	/**
	 * \brief Convert to a 3x1 oter::Matrix
	 */
	explicit operator Matrix<T, 1, 3>() const;

	/**
	 * \brief Compares two Vector3s
	 * \param right Vector3 to compare to
	 * \return True if Vector3s are equal
	 */
	[[nodiscard]] constexpr bool operator==(const Vector3& right) const;

	[[nodiscard]] constexpr f32 GetLength();
	[[nodiscard]] constexpr f32 GetLengthSquared();

	[[nodiscard]] Vector3 GetNormalized();

	[[nodiscard]] T Dot(const Vector3& right);
	[[nodiscard]] T Cross(const Vector3& right);

	// Member operators
	// Unary operators
	Vector3 operator-(const Vector3& right);

	// Binary scalar operators
	Vector3& operator+=(const T& right);
	Vector3& operator-=(const T& right);
	Vector3& operator*=(const T& right);
	Vector3& operator/=(const T& right);

	// Binary vector operators
	template <typename U>
	Vector3& operator+=(const Vector3<U>& right);
	template <typename U>
	Vector3& operator-=(const Vector3<U>& right);
	template <typename U>
	Vector3& operator*=(const Vector3<U>& right);
	template <typename U>
	Vector3& operator/=(const Vector3<U>& right);

	// Friend operators
	// Binary scalar operators
	friend Vector3 operator+(Vector3 left, const T& right)
	{
		throw;
	}
	friend Vector3 operator-(Vector3 left, const T& right)
	{
		throw;
	}
	friend Vector3 operator*(Vector3 left, const T& right)
	{
		throw;
	}
	friend Vector3 operator/(Vector3 left, const T& right)
	{
		throw;
	}

	// Binary vector operators
	template <typename U>
	friend Vector3 operator+(Vector3 left, const Vector3<U>& right);
	template <typename U>
	friend Vector3 operator-(Vector3 left, const Vector3<U>& right);
	template <typename U>
	friend Vector3 operator*(Vector3 left, const Vector3<U>& right);
	template <typename U>
	friend Vector3 operator/(Vector3 left, const Vector3<U>& right);

	// Static declarations
	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
};

template <typename T>
Vector3<T>::Vector3() : Vector3(0) {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) : X(x), Y(y), Z(z) {}

template <typename T>
Vector3<T>::Vector3(T scalar) : X(scalar), Y(scalar), Z(scalar) {}

template <typename T>
template <typename U>
Vector3<T>::Vector3(const Vector3<U>& other) : X(static_cast<T>(other.X)), Y(static_cast<T>(other.Y)), Z(static_cast<T>(other.Z)) {}

template <typename T>
T Vector3<T>::Dot(const Vector3& right)
{
	return this->X * right.X + this->Y * right.Y + this->Z * right.Z;
}

template <typename T>
T Vector3<T>::Cross(const Vector3& right)
{
	return this->X * right.X - this->Y * right.Y - this->Z * right.Z;
}

template <typename T>
constexpr bool Vector3<T>::operator==(const Vector3& right) const
{
	return this->X == right.X && this->Y == right.Y && this->Z == right.Z;
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& right)
{
	return Vector3<T>(-right.X, -right.Y, -right.Z);
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const T& right)
{
	this->X += right.X;
	this->Y += right.Y;
	this->Z += right.Z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const T& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	this->Z -= right.Z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const T& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	this->Z *= right.Z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const T& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	this->Z /= right.Z;
	return *this;
}

template <typename T>
Vector3<T> operator+(Vector3<T> left, const T& right)
{
	left += right;
	return left;
}

template <typename T>
Vector3<T> operator-(Vector3<T> left, const T& right)
{
	left -= right;
	return left;
}

template <typename T>
Vector3<T> operator*(Vector3<T> left, const T& right)
{
	left *= right;
	return left;
}

template <typename T>
Vector3<T> operator/(Vector3<T> left, const T& right)
{
	left /= right;
	return left;
}

// Static definitions
template <typename T>
const Vector3<T> Vector3<T>::Zero(static_cast<T>(0));
template <typename T>
const Vector3<T> Vector3<T>::UnitX(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const Vector3<T> Vector3<T>::UnitY(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
template <typename T>
const Vector3<T> Vector3<T>::UnitZ(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

#endif
