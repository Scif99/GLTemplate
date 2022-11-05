#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
private:
	glm::vec3 m_position; 
	glm::vec3 m_forward; // (opposite of direction in opengl)
	glm::vec3 m_up; //up vector in camera basis
	glm::vec3 m_right; //right vector in camera basis
	glm::mat4 m_view{ glm::mat4(1.0f) }; //stores the view matrix
	glm::vec3 WORLD_UP; //We use this vector along with m_forward to construct an orthonormal basis

	//euler angles
	float pitch{ 0.f };
	float yaw{ -90.f };

	const float sensitivity{ 0.1f };


public:
	~Camera() = default;
	Camera() = delete;
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 up);

	void processKeyboardInput(GLFWwindow* window);
	void processMouseInput(GLFWwindow* window, float dx, float dy);

	void update();

	const glm::vec3& position() const { return m_position; }
	void setPosition(glm::vec3 v) { m_position = v; }; //sets absolute position
	void move(glm::vec3 v) { m_position += v; }; //moves relative to current pos

	glm::mat4 getView() const { return m_view; }


};

#endif // !CAMERA_H


