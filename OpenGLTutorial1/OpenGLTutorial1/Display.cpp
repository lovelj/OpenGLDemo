#include "Display.h"
#include "GL/glew.h"
#include <iostream>
Display::Display(float w,float h,const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	
	m_Window=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_OPENGL);
	m_glContext=SDL_GL_CreateContext(m_Window);

	GLenum status=glewInit();
	if(status!=GLEW_OK)
	{
		std::cerr<<"glew init failure"<<std::endl;
	}
	m_isClosed=false;


	glEnable(GL_DEPTH_TEST);
}


Display::~Display(void)
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_Window);
	Clear();

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type==SDL_QUIT)
		{
			m_isClosed=true;
		}
	
	}
}
void Display::Clear()
{
	glClearColor(0.0f,0.15f,0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	
}

bool Display::IsClosed()
{
	return m_isClosed;
}