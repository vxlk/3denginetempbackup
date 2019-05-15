#pragma once
#include "../pch.h"
#include "Object.h"
/*
A world contains :
Skybox
Lights
Objects
*/

class World final
{
	std::vector<GLuint> m_lightIDs;
	std::map<std::string, Object> m_objects;
};