#pragma once
#include <string>
#include <gl/glew.h>
class Texture
{
public:
	Texture(const std::string& filename);
	
	void Bind();
	~Texture(void);
private:
	GLuint m_texture;
};

