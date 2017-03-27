#pragma once
#include <string>
#include "GL/glew.h"
#include "Transform.h"
#include "Camera.h"
class Shader
{
public:
	Shader(const std::string& filename);
	~Shader(void);

	void Bind();
	void Update(const Transform& transform,const Camera& camera);
private: 
	static const unsigned int NUM_SHADER=2;
	enum 
	{
		TRANSFORM_U,
		NUM_UNIFORM
	};


	GLuint m_poragmram;
	GLuint m_shaders[NUM_SHADER];

	GLuint m_uniforms[NUM_UNIFORM];
};

