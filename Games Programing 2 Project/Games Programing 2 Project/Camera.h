#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

//Simple first person camera class
struct Camera
{
public:
	//Constructor
	Camera()
	{
	}

	//Init
	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	//Getters
	glm::vec3 getPos()
	{
		return this->pos;
	}
	inline glm::mat4 getViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}
	inline glm::mat4 getProjection() const
	{
		return projection;
	}
	inline glm::mat4 getView() const
	{
		return glm::lookAt(pos, pos + forward, up);
	}

	//Setters
	void setLook(glm::vec3 modelPos)
	{
		forward = glm::vec3(glm::normalize(modelPos - pos));
	}

	void setPos(glm::vec3 Pos)
	{
		pos = Pos;
	}

	void setUp(glm::vec3 Up)
	{
		up = Up;
	}

	//Movement
	void MoveForward(float amt)
	{
		pos += forward * amt;
	}
	void MoveRight(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}
	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}
	void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};