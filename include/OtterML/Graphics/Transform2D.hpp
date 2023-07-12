#ifndef OTER_TRANSFORM_H
#define OTER_TRANSFORM_H

#include <OtterML/System/Angle.hpp>
#include <OtterML/System/Matrix.hpp>
#include <OtterML/System/Vector2.hpp>

namespace oter
{

class Transform2D
{
public:
	Transform2D();

	const Angle&          GetRotation() const;
	const Vector2<f32>& GetScale() const;
	const Vector2<f32>& GetSkew() const;
	const Vector2<f32>& GetTranslation() const;

	void SetRotation(const Angle& newRotation);
	void SetScale(const Vector2<f32>& newScale);
	void SetScale(const f32& newScaleScalar);
	void SetSkew(const Vector2<f32>& newSkew);
	void SetTranslation(const Vector2<f32>& newTranslation);

	void Rotate(const Angle& rotationChange);
	void Scale(const Vector2<f32>& scaleChange);
	void Scale(const f32& scaleChangeScalar);
	void Skew(const Vector2<f32>& skewChange);
	void Translate(const Vector2<f32>& translationChange);

	Matrix<f32, 3, 3>& GetMatrix();

	bool operator==(const Transform2D& right) const;

private:
	Angle          _rotation    = Angle(0.f);
	Vector2<f32> _scale       = Vector2<f32>(1.f);
	Vector2<f32> _skew        = Vector2<f32>(0.f);
	Vector2<f32> _translation = Vector2<f32>(0.f);

	bool _changed = true;

	Matrix<f32, 3, 3> _matrix = Matrix<f32, 3, 3>::IdentityMatrix;
};
}

#endif
