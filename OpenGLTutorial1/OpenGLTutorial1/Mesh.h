#pragma once
#include "glm/glm.hpp"
#include "gl/glew.h"
#include <string>
#include "obj_loader.h"
class Vertex
{
public:
	Vertex(const glm::vec3& pos,const glm::vec2 texCoord,const glm::vec3& normal=glm::vec3(0,0,0))
	{
		this->pos=pos;

		this->texCoord=texCoord;
		this->normals=normal;

	};
	inline glm::vec3* GetPos(){return &pos;}
	inline glm::vec2* GetTexCoord(){return &texCoord;}

	inline glm::vec3* GetNormal(){return &normals;}
private:
	glm::vec3 pos;
	glm::vec2 texCoord;

	glm::vec3 normals;
};


class Mesh
{
private:
	enum{
		POSITION_VB,
		TexCoord_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	GLuint	m_vertexArrayObject;
	GLuint  m_vertexArrayBuffer[NUM_BUFFERS];
	unsigned int m_drawCount;

	void InitMesh(const IndexedModel& model);

public:
	Mesh(Vertex*  vertices,unsigned int numVertices,unsigned int * indices,unsigned int numindices);
	Mesh(const std::string& filename);
	~Mesh(void);

	void Draw();
};

