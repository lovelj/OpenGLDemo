#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex*  vertices,unsigned int numVertices,unsigned int * indices,unsigned int numindices)
{
	IndexedModel model;

	/*m_drawCount=numindices;

	glGenVertexArrays(1,&m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> texCoords;

	pos.reserve(numVertices);
	texCoords.reserve(numVertices);*/
	for(unsigned int i=0;i<numVertices;i++)
	{
		model.positions.push_back((*vertices[i].GetPos()));
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for(unsigned int i=0;i<numindices ;i++)
	{
		model.indices.push_back(indices[i]);
	}

	/*glGenBuffers(NUM_BUFFERS,m_vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER,numVertices*sizeof(pos[0]),&pos[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffer[TexCoord_VB]);
	glBufferData(GL_ARRAY_BUFFER,numVertices*sizeof(texCoords[0]),&texCoords[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2, GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_vertexArrayBuffer[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,numindices*sizeof(indices[0]),&indices[0],GL_STATIC_DRAW);


	glBindVertexArray(0);*/
	InitMesh(model);



}

Mesh::Mesh(const std::string& filename)
{
	IndexedModel model=OBJModel(filename).ToIndexedModel();

	InitMesh(model);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	//glDrawArrays(GL_TRIANGLES,0,m_drawCount);

	glDrawElements(GL_TRIANGLES,m_drawCount,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}

void Mesh::InitMesh(const IndexedModel& model)
{

	m_drawCount=model.indices.size();

	glGenVertexArrays(1,&m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	glGenBuffers(NUM_BUFFERS,m_vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER,model.positions.size()*sizeof(model.positions[0]),&model.positions[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffer[TexCoord_VB]);
	glBufferData(GL_ARRAY_BUFFER,model.positions.size()*sizeof(model.texCoords[0]),&model.texCoords[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2, GL_FLOAT,GL_FALSE,0,0);

	//
	glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffer[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER,model.normals.size()*sizeof(model.normals[0]),&model.normals[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3, GL_FLOAT,GL_FALSE,0,0);

	//

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_vertexArrayBuffer[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,model.indices.size()*sizeof(model.indices[0]),&model.indices[0],GL_STATIC_DRAW);


	glBindVertexArray(0);

}

Mesh::~Mesh(void)
{
	glDeleteVertexArrays(1,& m_vertexArrayObject);
}
