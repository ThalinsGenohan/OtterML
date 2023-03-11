#ifndef OTER_VECTOR2_HPP
#define OTER_VECTOR2_HPP

namespace glm
{
class vec2;
class ivec2;
class uvec2;
}

namespace oter
{
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
	 * \brief Construct a Vector2 from a glm::vec2
	 * \param glmVec glm::vec2 to convert
	 */
	explicit Vector2(const glm::vec2& glmVec);

	/**
	 * \brief Construct a Vector2 from a glm::ivec2
	 * \param glmVec glm::ivec2 to convert
	 */
	explicit Vector2(const glm::ivec2& glmVec);

	/**
	 * \brief Construct a Vector2 from a glm::uvec2
	 * \param glmVec glm::uvec2 to convert
	 */
	explicit Vector2(const glm::uvec2& glmVec);

	/**
	 * \brief Convert to a glm::vec2
	 */
	explicit operator glm::vec2() const;

	/**
	 * \brief Convert to a glm::uvec2
	 */
	explicit operator glm::uvec2() const;

	/**
	 * \brief Convert to a glm::ivec2
	 */
	explicit operator glm::ivec2() const;

	/**
	 * \brief Compares two Vector2s
	 * \param right Vector2 to compare to
	 * \return True if Vector2s are equal
	 */
	bool operator==(const Vector2& right) const;

	float GetLength();

	Vector2 GetNormalized();

	T Dot(const Vector2& right);
	T Cross(const Vector2& right);

	// Member operators
	// Unary operators
	Vector2 operator-(const Vector2<T>& right);

	// Binary scalar operators
	Vector2& operator+=(const T& right);
	Vector2& operator-=(const T& right);
	Vector2& operator*=(const T& right);
	Vector2& operator/=(const T& right);

	// Friend operators
	// Binary scalar operators
	friend Vector2 operator+(Vector2<T> left, const T& right);
	friend Vector2 operator-(Vector2<T> left, const T& right);
	friend Vector2 operator*(Vector2<T> left, const T& right);
	friend Vector2 operator/(Vector2<T> left, const T& right);

	// Static declarations
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};

template <typename T>
Vector2<T>::Vector2() : Vector2(0) {}

template <typename T>
Vector2<T>::Vector2(T x, T y) : X(x), Y(y) {}

template <typename T>
Vector2<T>::Vector2(T scalar) : X(scalar), Y(scalar) {}

template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& other) : X(static_cast<T>(other.X)), Y(static_cast<T>(other.Y)) {}

template <typename T>
T Vector2<T>::Dot(const Vector2& right)
{
	return this->X * right.X + this->Y * right.Y;
}

template <typename T>
T Vector2<T>::Cross(const Vector2& right)
{
	return this->X * right.X - this->Y * right.Y;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2& right) const
{
	return this->X == right.X && this->Y == right.Y;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& right)
{
	return Vector2<T>(-right.X, -right.Y);
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const T& right)
{
	this->X += right.X;
	this->Y += right.Y;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const T& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const T& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const T& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	return *this;
}

template <typename T>
Vector2<T> operator+(Vector2<T> left, const T& right)
{
	left += right;
	return left;
}

template <typename T>
Vector2<T> operator-(Vector2<T> left, const T& right)
{
	left -= right;
	return left;
}

template <typename T>
Vector2<T> operator*(Vector2<T> left, const T& right)
{
	left *= right;
	return left;
}

template <typename T>
Vector2<T> operator/(Vector2<T> left, const T& right)
{
	left /= right;
	return left;
}

// Static definitions
template <typename T>
const Vector2<T> Vector2<T>::Zero(static_cast<T>(0));
template <typename T>
const Vector2<T> Vector2<T>::UnitX(static_cast<T>(1), static_cast<T>(0));
template <typename T>
const Vector2<T> Vector2<T>::UnitY(static_cast<T>(0), static_cast<T>(1));
}

#endif
