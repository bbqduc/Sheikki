#include "entity.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(Model* model_)
	: model(model_),
	position(	1.0f),
	orientation(1.0f),
	velocity(0)
{
	movement_direction[0] = 0;
	movement_direction[1] = 0;
	movement_direction[2] = 1;
}

void Entity::setPos(float x, float y, float z)
{
	position[3][0] = x;
	position[3][1] = y;
	position[3][2] = z;
}

void Entity::rotateYaw(float yaw)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(orientation[1]));
	orientation = rotation * orientation;
	this->yaw += yaw;
}
	
void Entity::rotatePitch(float pitch)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(orientation[0]));
	orientation = rotation * orientation;
	this->pitch += pitch;
}

void Entity::rotateRoll(float roll)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), roll, glm::vec3(orientation[2]));
	orientation = rotation * orientation;
	this->roll += roll;
}

void Entity::move(float x, float y, float z)
{
	position[3][0] += x;
	position[3][1] += y;
	position[3][2] += z;
	this->x += x;
	this->y += y;
	this->z += z;
}

void Entity::thrusters(float force)
{
	position[3] += (orientation[1]*force);
}		


void Entity::tick()
{
	position[3][0] += (movement_direction[0] * velocity); // x
	position[3][1] += (movement_direction[1] * velocity); // y
	position[3][2] += (movement_direction[2] * velocity); // z
}

GLuint Entity::GetTexture() const
{
	return model->GetTexture();
}
