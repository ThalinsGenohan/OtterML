#ifndef OTER_SHADER_H
#define OTER_SHADER_H

//#include <glm/fwd.hpp>

#include <OtterML/System/Matrix.hpp>
#include <OtterML/System/Vector2.hpp>
#include <OtterML/System/Vector3.hpp>
#include <OtterML/System/Vector4.hpp>

namespace oter
{
class Shader
{
public:
	Shader();
	~Shader();

	void Delete();

	void Use() const;

	void Compile(const std::string& vertSource, const std::string& fragSource);
	void Compile(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);
	void Compile(const char* vertSource, const char* geomSource, const char* fragSource);

	void SetFloat(const char* name, f32 value, bool useProgram = false) const;
	void SetVector2f(const char* name, f32 x, f32 y, bool useProgram = false) const;
	void SetVector2f(const char* name, const Vector2<f32>& value, bool useProgram = false) const;
	void SetVector3f(const char* name, f32 x, f32 y, f32 z, bool useProgram = false) const;
	void SetVector3f(const char* name, const Vector3<f32>& value, bool useProgram = false) const;
	void SetVector4f(const char* name, f32 x, f32 y, f32 z, f32 w, bool useProgram = false) const;

	void SetInt(const char* name, i32 value, bool useProgram = false) const;
	void SetVector2i(const char* name, i32 x, i32 y, bool useProgram = false) const;
	void SetVector2i(const char* name, const Vector2<i32>& value, bool useProgram = false) const;
	void SetVector3i(const char* name, i32 x, i32 y, i32 z, bool useProgram = false) const;
	void SetVector3i(const char* name, const Vector3<i32>& value, bool useProgram = false) const;
	void SetVector4i(const char* name, i32 x, i32 y, i32 z, i32 w, bool useProgram = false) const;

	void SetUInt(const char* name, u32 value, bool useProgram = false) const;
	void SetVector2u(const char* name, u32 x, u32 y, bool useProgram = false) const;
	void SetVector2u(const char* name, const Vector2<u32>& value, bool useProgram = false) const;
	void SetVector3u(const char* name, u32 x, u32 y, u32 z, bool useProgram = false) const;
	void SetVector3u(const char* name, const Vector3<u32>& value, bool useProgram = false) const;
	void SetVector4u(const char* name, u32 x, u32 y, u32 z, u32 w, bool useProgram = false) const;

	void SetMatrix2(const char* name, const Matrix<f32, 2, 2>& matrix, bool useProgram = false) const;
	void SetMatrix3(const char* name, const Matrix<f32, 3, 3>& matrix, bool useProgram = false) const;
	void SetMatrix4(const char* name, const Matrix<f32, 4, 4>& matrix, bool useProgram = false) const;

	// GLM
	void SetVector2f(const char* name, const glm::vec2& value, bool useProgram = false) const;
	void SetVector3f(const char* name, const glm::vec3& value, bool useProgram = false) const;
	void SetVector4f(const char* name, const glm::vec4& value, bool useProgram = false) const;
	void SetVector2i(const char* name, const glm::ivec2& value, bool useProgram = false) const;
	void SetVector3i(const char* name, const glm::ivec3& value, bool useProgram = false) const;
	void SetVector4i(const char* name, const glm::ivec4& value, bool useProgram = false) const;
	void SetVector2u(const char* name, const glm::uvec2& value, bool useProgram = false) const;
	void SetVector3u(const char* name, const glm::uvec3& value, bool useProgram = false) const;
	void SetVector4u(const char* name, const glm::uvec4& value, bool useProgram = false) const;
	void SetMatrix3(const char* name, glm::mat3& matrix, bool useProgram = false) const;
	void SetMatrix4(const char* name, glm::mat4& matrix, bool useProgram = false) const;


	u32 GetID() const;

	explicit operator u32() const;

private:
	u32 _id = 0;

	static void CheckCompileErrors(u32 object, const char* type);
};
}

#endif //OTER_SHADER_H
