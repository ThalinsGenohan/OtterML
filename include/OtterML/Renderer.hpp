#ifndef OTER_RENDERER_HPP
#define OTER_RENDERER_HPP

#include <OtterML/Common.hpp>

#include <unordered_map>
#include <vector>

namespace oter
{
class Shader;

template <typename T>
class Renderer
{
public:
	Renderer() {}
	~Renderer()
	{
		std::vector<u32> buffers = std::vector<u32>(this->_vbos.size());
		for (auto iter = this->_vbos.begin(); iter != this->_vbos.end(); ++iter)
		{
			buffers.push_back(iter->second);
		}
		glDeleteBuffers(this->_vbos.size(), buffers.data());
		glDeleteVertexArrays(1, &this->_vao);
	}

	void Init()
	{
		glGenVertexArrays(1, &this->_vao);
		glBindVertexArray(this->_vao);
	}

	void BindVAO();
	void CreateVBO(T* drawable);
	void BindVBO(T* drawable);

	void Draw(T& drawable, const Shader& shader);

private:
	u32                         _vao  = 0;
	std::unordered_map<T*, u32> _vbos = {};
};

}

#endif
