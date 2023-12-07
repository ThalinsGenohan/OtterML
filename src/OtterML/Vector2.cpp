#include <OtterML/Vector2.hpp>

namespace oter
{

// Static definitions
template <typename T>
const Vector2<T> Vector2<T>::Zero(static_cast<T>(0));
template <typename T>
const Vector2<T> Vector2<T>::UnitX(static_cast<T>(1), static_cast<T>(0));
template <typename T>
const Vector2<T> Vector2<T>::UnitY(static_cast<T>(0), static_cast<T>(1));

template <typename T>
Vector2<T>::Vector2() : Vector2(static_cast<T>(0)) {}

template <typename T>
Vector2<T>::Vector2(T x, T y) : X(x), Y(y) {}

template <typename T>
Vector2<T>::Vector2(T scalar) : X(scalar), Y(scalar) {}

template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& other) : X(static_cast<T>(other.X)), Y(static_cast<T>(other.Y)) {}

template <typename T>
Vector2<T>::Vector2(const Vector2<T>& other) : X(other.X), Y(other.Y) {}

template <typename T>
Vector2<T>::Vector2(T array[2]) : X(array[0]), Y(array[1]) {}

template <typename T>
Vector2<T>::Vector2(std::array<T, 2> array) : X(array[0]), Y(array[1]) {}



template<typename T>
template<typename U>
Vector2<T>::Vector2(const glm::vec<2, U>& glmVec) : X(static_cast<T>(glmVec.x)), Y(static_cast<T>(glmVec.y)) {}

template <typename T>
T Vector2<T>::Dot(const Vector2<T>& right)
{
	return this->X * right.X + this->Y * right.Y;
}

template <typename T>
T Vector2<T>::Cross(const Vector2<T>& right)
{
	return this->X * right.X - this->Y * right.Y;
}

template <typename T>
constexpr bool Vector2<T>::operator==(const Vector2<T>& right) const
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
	this->X += right;
	this->Y += right;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const T& right)
{
	this->X -= right;
	this->Y -= right;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const T& right)
{
	this->X *= right;
	this->Y *= right;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const T& right)
{
	this->X /= right;
	this->Y /= right;
	return *this;
}

// I have no idea why this has to have two separate template definitions instead of a comma
template <typename T>
template <typename U>
Vector2<T>& Vector2<T>::operator+=(const Vector2<U>& right)
{
	this->X += right.X;
	this->Y += right.Y;
	return *this;
}

template <typename T>
template <typename U>
Vector2<T>& Vector2<T>::operator-=(const Vector2<U>& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	return *this;
}

template <typename T>
template <typename U>
Vector2<T>& Vector2<T>::operator*=(const Vector2<U>& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	return *this;
}

template <typename T>
template <typename U>
Vector2<T>& Vector2<T>::operator/=(const Vector2<U>& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	return *this;
}

template <typename T>
constexpr f32 Vector2<T>::GetLength()
{
	return std::sqrt(this->X * this->X + this->Y * this->Y);
}

template <typename T>
constexpr f32 Vector2<T>::GetLengthSquared()
{
	return this->X * this->X + this->Y * this->Y;
}

template <typename T>
Vector2<T> Vector2<T>::GetNormalized()
{
	return *this / this->GetLength();
}
}
