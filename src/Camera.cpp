#include <glm/gtc/matrix_transform.hpp>
#include "Debug.h"
#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSens(SENS), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatix()
{
	//return glm::lookAt(Position, Position + Front, Up);
	return LookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboardInput(ECameraDirection camDir, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	//glm::vec3 FrontXZ = glm::vec3(Front.x, 0.0f, Front.z);
	switch (camDir)
	{
		case ECameraDirection::Forward:
			Position += Front * velocity;
			break;
		case ECameraDirection::Backward:
			Position -= Front * velocity;
			break;
		case ECameraDirection::Left:
			Position -= Right * velocity;
			break;
		case ECameraDirection::Right:
			Position += Right * velocity;
			break;
		default:
			Debug::Log("Unexpected error! not a defined camera direction, please check the function");
			break;
	}
	Position.y = 0.0f;
}

void Camera::ProcessMouseInput(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= MouseSens;
	yOffset *= MouseSens;

	Yaw += xOffset;
	Pitch += yOffset;

	if(constrainPitch)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
	}

	UpdateCameraVectors();
}

void Camera::ProcessScrollInput(float yOffset)
{
	Zoom -= (float)yOffset;
	if (Zoom < 1.0f)
	{
		Zoom = 1.0f;
	}
	if (Zoom > 90.0f)
	{
		Zoom = 90.0f;
	}
}

glm::mat4 Camera::LookAt(glm::vec3 position, glm::vec3 target, glm::vec3 upAxis)
{
	glm::vec3 zAxis = glm::normalize(position - target);
	glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(upAxis), zAxis));
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);

	glm::mat4 translation = glm::mat4(1.0f);
	translation[3][0] = -position.x;
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = xAxis.x;
	rotation[1][0] = xAxis.y;
	rotation[2][0] = xAxis.z;

	rotation[0][1] = yAxis.x;
	rotation[1][1] = yAxis.y;
	rotation[2][1] = yAxis.z;

	rotation[0][2] = zAxis.x;
	rotation[1][2] = zAxis.y;
	rotation[2][2] = zAxis.z;

	return rotation * translation;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::cross(Right, Front);
}

