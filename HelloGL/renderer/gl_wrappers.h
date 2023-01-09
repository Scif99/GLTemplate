#pragma once
#include <memory>

/*
* Wrappers for various OpenGL things
*	- ID
*	- Primitives
*/

//GLID is a simple object that holds an opengl ID
//It allows for move semantics of any objects that contain an opengl ID (buffer objects, textures etc...)

/*

OpenGL objects should be non-copyable, but moveable
*/

class GLID
{

public:
	unsigned int m_ID{ 0 };

public:
	GLID() {}

	GLID(const GLID& other) = delete;
	GLID& operator=(const GLID& other) = delete;
	
	GLID(GLID&& other) noexcept
		: m_ID{other.m_ID}
	{
		other.m_ID = 0;
	}
	GLID& operator=(GLID&& other) noexcept
	{
		if (this != &other)
		{
			m_ID = 0;

			m_ID = other.m_ID;
			other.m_ID = 0;
		}
		return *this;
	}
};



enum class GLPrimitive
{
	TRIANGLE = GL_TRIANGLES,
	PATCHES = GL_PATCHES,
	POINTS = GL_POINTS
};