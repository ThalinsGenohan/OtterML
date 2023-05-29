#ifndef OTER_TRANSFORM_H
#define OTER_TRANSFORM_H

#include <OtterML/System/Angle.hpp>
#include <OtterML/System/Matrix.hpp>
#include <OtterML/System/Vector2.hpp>

namespace oter
{
class Transform
{
public:
	Transform();

	const Angle&          GetRotation() const;
	const Vector2<float>& GetScale() const;
	const Vector2<float>& GetSkew() const;
	const Vector2<float>& GetTranslation() const;

	void SetRotation(const Angle& newRotation);
	void SetScale(const Vector2<float>& newScale);
	void SetScale(const float& newScaleScalar);
	void SetSkew(const Vector2<float>& newSkew);
	void SetTranslation(const Vector2<float>& newTranslation);

	void Rotate(const Angle& rotationChange);
	void Scale(const Vector2<float>& scaleChange);
	void Scale(const float& scaleChangeScalar);
	void Skew(const Vector2<float>& skewChange);
	void Translate(const Vector2<float>& translationChange);

	Matrix<float, 3, 3>& GetMatrix();

	bool operator==(const Transform& right) const;

private:
	Angle          _rotation    = Angle(0.f);
	Vector2<float> _scale       = Vector2<float>(1.f);
	Vector2<float> _skew        = Vector2<float>::Zero;
	Vector2<float> _translation = Vector2<float>::Zero;

	bool _changed = true;

	Matrix<float, 3, 3> _matrix = Matrix<float, 3, 3>::IdentityMatrix;
};
}

#endif
