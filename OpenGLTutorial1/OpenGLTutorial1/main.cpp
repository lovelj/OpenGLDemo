#include "Display.h"
#include <iostream>
#include "GL/glew.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define  WIDTH 800
#define  HEIGHT 600
int main(int argc,char** argv)
{	
	Display display(800,600,"test");

	Vertex vers[]={Vertex(glm::vec3(-0.5,-0.5,0),glm::vec2(0,0)),
	Vertex(glm::vec3(0,0.5,0),glm::vec2(0.5,1.0)),
	Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,0))
	};
	
	unsigned int indice[]={0,1,2};




	Mesh mesh(vers,sizeof(vers)/sizeof(vers[0]),
		indice,sizeof(indice)/sizeof(indice[0]));

	Mesh mesh2("./res/monkey3.obj");

	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0,0,-3),70.0f,(float) WIDTH/(float)HEIGHT,0.01f,1000.0f);
	Transform transform;

	float counter =0.0f;
	while (!display.IsClosed())
	{		
		display.Clear();
		float sinCounter=sinf(counter);
		transform.GetPos()->x=sinCounter;

		transform.GetPos()->z=sinCounter;
/*
		transform.GetRot()->z=counter*5;
*/
		shader.Bind();
		texture.Bind();

		shader.Update(transform,camera);

		mesh.Draw();

		mesh2.Draw();
		display.Update();

		counter+=0.01f;
	}

	return 0;

}