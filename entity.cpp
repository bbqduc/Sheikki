#include "entity.h"
#include "engine.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(const Model& model_)
	: 
	model(model_),
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

void Entity::setVelocity(float velocity)
{
	this->velocity = velocity;
}

void Entity::rotate(glm::mat4& mat)
{
	orientation = mat * orientation;
}

void Entity::setDirection(glm::vec3& dir)
{
	movement_direction = dir;
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

void Entity::tick(bool keysDown[])
{
	if(keysDown[Engine::UP])
		rotatePitch(0.1f);
	if(keysDown[Engine::DOWN])
		rotatePitch(-0.1f);
	if(keysDown[Engine::Q])
		rotateRoll(-0.1f);
	if(keysDown[Engine::E])
		rotateRoll(0.1f);
	if(keysDown[Engine::LEFT])
		rotateYaw(-0.1f);
	if(keysDown[Engine::RIGHT])
		rotateYaw(0.1f);
	if(keysDown[Engine::A])
		thrusters(0.005f);
	if(keysDown[Engine::Z])
		thrusters(-0.005f);
}

GLuint Entity::GetTexture() const
{
	return model.GetTexture();
}
