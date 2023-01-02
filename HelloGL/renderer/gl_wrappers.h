#pragma once
#include <memory>

/*

*/

//GLID is a simple object that holds an opengl ID
//It allows for move semantics of any objects that contain an opengl ID (buffer objects, textures etc...)
class GLID
{
private:
	std::unique_ptr<unsigned int> ptr_ID;

public:
	GLID() : ptr_ID{ std::make_unique<unsigned int>(0) } {}
	GLID(const GLID& other) = default;
	GLID& operator=(const GLID& other) = default;
	GLID(GLID&& other) = default;
	GLID& operator=(GLID&& other) = default;

	void Set(unsigned int i) { ptr_ID = std::make_unique<unsigned int>(i); }

	unsigned int* operator&() const noexcept { return ptr_ID.get(); }
	unsigned int& Value() const noexcept { return *ptr_ID; }
};
