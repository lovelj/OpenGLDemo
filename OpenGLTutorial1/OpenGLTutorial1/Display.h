#pragma once
#include <iostream>
#include "sdl\SDL.h"
class Display
{
public:
	Display(float w,float h,const std::string& title);
	~Display(void);
	void Update();
	void Clear();
	bool IsClosed();
private :
	SDL_Window* m_Window;
	SDL_GLContext m_glContext;
	bool m_isClosed;


};

