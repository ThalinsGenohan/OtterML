#include <OtterML/Transform2D.hpp>

#define _USE_MATH_DEFINES

namespace oter
{
Transform2D::Transform2D() {}

const Angle& Transform2D::GetRotation() const
{
	return this->_rotation;
}

const Vector2<f32>& Transform2D::GetScale() const
{
	return this->_scale;
}

const Vector2<f32>& Transform2D::GetSkew() const
{
	return this->_skew;
}

const Vector2<f32>& Transform2D::GetTranslation() const
{
	return this->_translation;
}

void Transform2D::SetRotation(const Angle& newRotation)
{
	this->_rotation = newRotation;
	this->_changed = true;
}

void Transform2D::SetScale(const Vector2<f32>& newScale)
{
	this->_scale   = newScale;
	this->_changed = true;
}

void Transform2D::SetScale(const f32& newScaleScalar)
{
	this->_scale   = Vector2<f32>(newScaleScalar);
	this->_changed = true;
}

void Transform2D::SetSkew(const Vector2<f32>& newSkew)
{
	this->_skew    = newSkew;
	this->_changed = true;
}

void Transform2D::SetTranslation(const Vector2<f32>& newTranslation)
{
	this->_translation = newTranslation;
	this->_changed     = true;
}

void Transform2D::Rotate(const Angle& rotationChange)
{
	this->SetRotation(this->_rotation + rotationChange);
}

void Transform2D::Scale(const Vector2<f32>& scaleChange)
{
	this->SetScale(Vector2<f32>(this->_scale.X * scaleChange.X, this->_scale.Y * scaleChange.Y));
}

void Transform2D::Scale(const f32& scaleChangeScalar)
{
	this->SetScale(Vector2<f32>(this->_scale.X * scaleChangeScalar, this->_scale.Y * scaleChangeScalar));
}

void Transform2D::Skew(const Vector2<f32>& skewChange)
{
	this->SetSkew(this->_skew + skewChange);
}

void Transform2D::Translate(const Vector2<f32>& translationChange)
{
	this->SetTranslation(this->_translation + translationChange);
}

Matrix<f32, 3, 3>& Transform2D::GetMatrix()
{
	if (!this->_changed)
		return this->_matrix;

	const f32 radians = this->_rotation.GetRadians();

	const f32 m00 = std::cos(radians) * this->_scale.X;
	const f32 m01 = std::sin(radians) * this->_scale.Y;
	const f32 m02 = static_cast<f32>(this->_translation.X);

	const f32 m10 = -std::sin(radians) * this->_scale.X;
	const f32 m11 = std::cos(radians) * this->_scale.Y;
	const f32 m12 = static_cast<f32>(this->_translation.Y);

	constexpr f32 m20 = 0.f;
	constexpr f32 m21 = 0.f;
	constexpr f32 m22 = 1.f;

	this->_matrix = Matrix<f32, 3, 3>(std::array{ m00, m01, m02, m10, m11, m12, m20, m21, m22 });

	this->_changed = false;

	return _matrix;
}

bool Transform2D::operator==(const Transform2D& right) const
{
	return (this->_rotation == right._rotation) &&
		this->_scale == right._scale &&
		this->_skew == right._skew &&
		this->_translation == right._translation;
}

}
