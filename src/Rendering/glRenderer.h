#pragma once
#include "../pch.h"
struct GLFWwindow;

class glRenderer
{
	GLuint m_vertexBuffer;
	GLuint m_uvbuffer;
	GLuint m_normalBuffer;
	GLuint m_elementBuffer;

	//for calculating fps
	double m_currentTime;
	double m_lastTime;
	unsigned int m_numFrames;

public:
	void render(GLFWwindow* windowToRenderTo);
};

