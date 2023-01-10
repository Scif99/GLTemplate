#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
private:
	glm::vec3 m_position; 
	
	//Basis vectors in camera space
	glm::vec3 m_forward; //Note this points in the *reverse* z direction in camera basis
	glm::vec3 WORLD_UP; //We use this vector along with m_forward to construct an orthonormal basis
	glm::vec3 m_right; //right vector in camera basis
	glm::vec3 m_up; //up vector in camera basis
	
	//euler angles
	float pitch{ 0.f };
	float yaw{ -90.f };

	const float sensitivity{ 0.1f };
	float m_speed{s_default_speed};

	inline static glm::vec3 s_default_pos = glm::vec3(0.0f, 0.0f, 1.0f);
	inline static glm::vec3 s_default_target = glm::vec3(0.0f, 0.f, 0.0f);
	inline static glm::vec3 s_default_up = glm::vec3(0.0f, 1.0f, 0.0f);
	inline static float s_default_speed{ 2.5f };

public:
	float lastX{800.f/2.f}; //SCREEN_WIDTH
	float lastY{600.f/2.f}; //SCREEN_HEIGHT
	bool firstMouse{true};

public:
	Camera(const glm::vec3& pos = Camera::s_default_pos, const glm::vec3& centre = Camera::s_default_target, const glm::vec3&  up = Camera::s_default_up);

	//Reset the camera basis
	void Reset(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

	void ProcessKeyboardInput(GLFWwindow* window, float dt);
	void ProcessMouseInput(GLFWwindow* window, float dx, float dy);
	void Update();

	//Setters
	void setPosition(const glm::vec3& v) { m_position = v; }; 
	void Move(const glm::vec3& v) { m_position += v; }; //move relative to current pos
	void SetSpeed(float v) { m_speed = v; }
	//Getters
	const glm::vec3& Position() const { return m_position; }
	glm::mat4 GetView() const { return glm::lookAt(m_position, m_position + m_forward, WORLD_UP); } //can get the centre back using vector arithmetic


};



