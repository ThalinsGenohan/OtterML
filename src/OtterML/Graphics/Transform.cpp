#include <OtterML/Graphics/Transform.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

namespace oter
{
Transform::Transform() {}

const Angle& Transform::GetRotation() const
{
	return this->_rotation;
}

const Vector2<float>& Transform::GetScale() const
{
	return this->_scale;
}

const Vector2<float>& Transform::GetSkew() const
{
	return this->_skew;
}

const Vector2<float>& Transform::GetTranslation() const
{
	return this->_translation;
}

void Transform::SetRotation(const Angle& newRotation)
{
	this->_rotation = newRotation;
	this->_changed = true;
}

void Transform::SetScale(const Vector2<float>& newScale)
{
	this->_scale   = newScale;
	this->_changed = true;
}

void Transform::SetScale(const float& newScaleScalar)
{
	this->_scale   = Vector2<float>(newScaleScalar);
	this->_changed = true;
}

void Transform::SetSkew(const Vector2<float>& newSkew)
{
	this->_skew    = newSkew;
	this->_changed = true;
}

void Transform::SetTranslation(const Vector2<float>& newTranslation)
{
	this->_translation = newTranslation;
	this->_changed     = true;
}

void Transform::Rotate(const Angle& rotationChange)
{
	this->SetRotation(this->_rotation + rotationChange);
}

void Transform::Scale(const Vector2<float>& scaleChange)
{
	this->SetScale(Vector2<float>(this->_scale.X * scaleChange.X, this->_scale.Y * scaleChange.Y));
}

void Transform::Scale(const float& scaleChangeScalar)
{
	this->SetScale(Vector2<float>(this->_scale.X * scaleChangeScalar, this->_scale.Y * scaleChangeScalar));
}

void Transform::Skew(const Vector2<float>& skewChange)
{
	this->SetSkew(this->_skew + skewChange);
}

void Transform::Translate(const Vector2<float>& translationChange)
{
	this->SetTranslation(this->_translation + translationChange);
}

Matrix<float, 3, 3>& Transform::GetMatrix()
{
	if (!this->_changed)
		return this->_matrix;

	const float radians = this->_rotation.GetRadians();

	const float m00 = std::cos(radians) * this->_scale.X;
	const float m01 = std::sin(radians) * this->_scale.Y;
	const float m02 = static_cast<float>(this->_translation.X);

	const float m10 = -std::sin(radians) * this->_scale.X;
	const float m11 = std::cos(radians) * this->_scale.Y;
	const float m12 = static_cast<float>(this->_translation.Y);

	constexpr float m20 = 0.f;
	constexpr float m21 = 0.f;
	constexpr float m22 = 1.f;

	this->_matrix = Matrix<float, 3, 3>(std::array{ m00, m01, m02, m10, m11, m12, m20, m21, m22 });

	this->_changed = false;

	return _matrix;
}

bool Transform::operator==(const Transform& right) const
{
	return (this->_rotation <=> right._rotation) == std::partial_ordering::equivalent &&
		this->_scale == right._scale &&
		this->_skew == right._skew &&
		this->_translation == right._translation;
}

}
