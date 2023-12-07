#include <OtterML/Renderer.hpp>
#include <OtterML/Shader.hpp>

#include <glad/gl.h>

namespace oter
{
class FrameBuffer;

template <typename T>
void Renderer<T>::BindVAO()
{
	glBindVertexArray(this->_vao);
}
template <typename T>
void Renderer<T>::CreateVBO(T* drawable)
{
	this->_vbos[drawable] = 0;
	glGenBuffers(1, &this->_vbos[drawable]);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[drawable]);
	// TODO: Fix this
	//glBufferData(GL_ARRAY_BUFFER, sizeof )
	//glVertexAttrib
	//glEnableVertexAttribArray
}
template <typename T>
void Renderer<T>::BindVBO(T* drawable)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[drawable]);
}

template <>
void Renderer<FrameBuffer>::Draw(FrameBuffer& frameBuffer, const Shader& shader)
{
	constexpr f32 vertices[16] = {
		-1.f, -1.f, 0.f, 0.f,
		-1.f, 1.f, 0.f, 1.f,
		1.f, -1.f, 1.f, 0.f,
		1.f, 1.f, 1.f, 1.f,
	};

	this->BindVAO();

	if (!this->_vbos.contains(&frameBuffer))
		this->CreateVBO(&frameBuffer);
	this->BindVBO(&frameBuffer);

	shader.Use();


}
}
