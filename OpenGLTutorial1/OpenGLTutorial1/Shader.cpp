#include "Shader.h"
#include <fstream>
#include <iostream>

static void CheckShaderError(GLuint shader,GLuint flag,bool isProgram,const std::string& errorMessage);
static std::string LoadShader(const std::string& filename);
static GLuint CreateShader(const std::string text,GLenum shadertype);


Shader::Shader(const std::string& filename)
{
	m_poragmram=glCreateProgram();
	
	m_shaders[0]=CreateShader(LoadShader(filename+".vs"),GL_VERTEX_SHADER);//定点着色器
	m_shaders[1]=CreateShader(LoadShader(filename+".fs"),GL_FRAGMENT_SHADER);

	for(unsigned int i=0 ;i<NUM_SHADER;i++)
	{
		glAttachShader(m_poragmram,m_shaders[i]);
	}


	glBindAttribLocation(m_poragmram,0,"position");
	glBindAttribLocation(m_poragmram,1,"texCoord");
	glBindAttribLocation(m_poragmram,2,"normal");

	glLinkProgram(m_poragmram);
	CheckShaderError(m_poragmram,GL_LINK_STATUS,true,"Error: link error");
	glValidateProgram(m_poragmram);
	CheckShaderError(m_poragmram,GL_VALIDATE_STATUS,true,"Error: validate error");

	m_uniforms[TRANSFORM_U]=glGetUniformLocation(m_poragmram,"transform");
}

Shader::~Shader(void)
{
	for(unsigned int i=0 ;i<NUM_SHADER;i++)
	{
		glDetachShader(m_poragmram,m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_poragmram);
}

void Shader::Bind()
{
	glUseProgram(m_poragmram);
}
void Shader::Update(const Transform& transform,const Camera& camera)
{
	glm::mat4 model=camera.GetViewProjection()*transform.GetModel(); 
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1,GL_FALSE,&model[0][0]);
}


static std::string LoadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	std::string output;
	std::string line;
	if(file.is_open())
	{
		while (file.good())
		{
			getline(file,line);
			output.append(line+"\n");
		}
	}
	else
	{
		std::cerr<<"Unable to load shader"<<filename<<std::endl;
	}
	return output;

}

static void CheckShaderError(GLuint shader,GLuint flag,bool isProgram,const std::string& errorMessage)
{
	GLint success=0;
	GLchar error[1024] ={0};
	if(isProgram)
	{
		glGetProgramiv(shader,flag,&success);	
	}
	else
	{
		glGetShaderiv(shader,flag,&success);
	}
	if(success==GL_FALSE)
	{
	
		if(isProgram)
		{
			glGetProgramInfoLog(shader,sizeof(error),NULL,error);
		}
		else
		{
			glGetShaderInfoLog(shader,sizeof(error),NULL,error);
		}
		std::cerr<<errorMessage<<";"<<error<<";"<<std::endl;
	}
}
static GLuint CreateShader(const std::string text,GLenum shadertype)
{
	GLuint shader=glCreateShader(shadertype);
	if(shader==0)
	{
		std::cerr<<"Error:Shader creation failure"<<std::endl;
	}
	const GLchar* shaderSourceString[1];
	GLint shaderSourceStringLength[1];
	shaderSourceString[0]=text.c_str();
	shaderSourceStringLength[0]=text.length();
	glShaderSource(shader,1,shaderSourceString,shaderSourceStringLength);
	glCompileShader(shader);
	CheckShaderError(shader,GL_COMPILE_STATUS,false,"error::shader ");
	return shader;
}
