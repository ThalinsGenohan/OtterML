#ifndef OTER_SHADER_H
#define OTER_SHADER_H

#include <string>
#include <glm/fwd.hpp>

#include <OtterML/System/Matrix.hpp>
#include <OtterML/System/Vector2.hpp>
#include <OtterML/System/Vector3.hpp>

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

	void SetFloat(const char* name, float value, bool useProgram = false) const;
	void SetVector2f(const char* name, float x, float y, bool useProgram = false) const;
	void SetVector2f(const char* name, const glm::vec2& value, bool useProgram = false) const;
	void SetVector2f(const char* name, const Vector2<float>& value, bool useProgram = false) const;
	void SetVector3f(const char* name, float x, float y, float z, bool useProgram = false) const;
	void SetVector3f(const char* name, const glm::vec3& value, bool useProgram = false) const;
	void SetVector3f(const char* name, const Vector3<float>& value, bool useProgram = false) const;
	void SetVector4f(const char* name, float x, float y, float z, float w, bool useProgram = false) const;
	void SetVector4f(const char* name, const glm::vec4& value, bool useProgram = false) const;

	void SetInt(const char* name, int32_t value, bool useProgram = false) const;
	void SetVector2i(const char* name, int32_t x, int32_t y, bool useProgram = false) const;
	void SetVector2i(const char* name, const glm::ivec2& value, bool useProgram = false) const;
	void SetVector2i(const char* name, const Vector2<int32_t>& value, bool useProgram = false) const;
	void SetVector3i(const char* name, int32_t x, int32_t y, int32_t z, bool useProgram = false) const;
	void SetVector3i(const char* name, const glm::ivec3& value, bool useProgram = false) const;
	void SetVector3i(const char* name, const Vector3<int32_t>& value, bool useProgram = false) const;
	void SetVector4i(const char* name, int32_t x, int32_t y, int32_t z, int32_t w, bool useProgram = false) const;
	void SetVector4i(const char* name, const glm::ivec4& value, bool useProgram = false) const;

	void SetUInt(const char* name, uint32_t value, bool useProgram = false) const;
	void SetVector2u(const char* name, uint32_t x, uint32_t y, bool useProgram = false) const;
	void SetVector2u(const char* name, const glm::uvec2& value, bool useProgram = false) const;
	void SetVector2u(const char* name, const Vector2<uint32_t>& value, bool useProgram = false) const;
	void SetVector3u(const char* name, uint32_t x, uint32_t y, uint32_t z, bool useProgram = false) const;
	void SetVector3u(const char* name, const glm::uvec3& value, bool useProgram = false) const;
	void SetVector3u(const char* name, const Vector3<uint32_t>& value, bool useProgram = false) const;
	void SetVector4u(const char* name, uint32_t x, uint32_t y, uint32_t z, uint32_t w, bool useProgram = false) const;
	void SetVector4u(const char* name, const glm::uvec4& value, bool useProgram = false) const;

	void SetMatrix3(const char* name, glm::mat3& matrix, bool useProgram = false) const;
	void SetMatrix3(const char* name, const Matrix<float, 3, 3>& matrix, bool useProgram = false) const;

	void SetMatrix4(const char* name, glm::mat4& matrix, bool useProgram = false) const;

	uint32_t GetID() const;

	explicit operator uint32_t() const;

private:
	uint32_t _id = NULL;

	static void CheckCompileErrors(uint32_t object, const char* type);
};
}

#endif //OTER_SHADER_H
