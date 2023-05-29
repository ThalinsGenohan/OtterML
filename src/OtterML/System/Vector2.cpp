#include <OtterML/System/Vector2.hpp>

#include <cmath>

namespace oter
{
template <typename T>
constexpr float Vector2<T>::GetLength()
{
	return std::sqrt(this->X * this->X + this->Y * this->Y);
}

template <typename T>
constexpr float Vector2<T>::GetLengthSquared()
{
	return this->X * this->X + this->Y * this->Y;
}

template <typename T>
Vector2<T> Vector2<T>::GetNormalized()
{
	return *this / this->GetLength();
}
}
