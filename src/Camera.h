#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

//Defines possible options for camera movement. Used as a abstraction to stay away from window system specific input methods
enum ECameraDirection
{
	Forward,
	Backward,
	Left,
	Right
};

//Default Camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENS = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up = glm::vec3(0.0f);
	glm::vec3 Right = glm::vec3(0.0f);
	glm::vec3 WorldUp = glm::vec3(0.0f);

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSens;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	glm::mat4 GetViewMatix();
	void ProcessKeyboardInput(ECameraDirection camDir, float deltaTime);
	void ProcessMouseInput(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void ProcessScrollInput(float yOffset);
	glm::mat4 LookAt(glm::vec3 position, glm::vec3 target, glm::vec3 upAxis);
private:
	void UpdateCameraVectors();
};