#ifndef ENTITY_H
#define ENTITY_H

#include "model.h"
#include <glm/glm.hpp>

class Entity{
	friend class Graphics; // Graphics needs access to model for drawing
	Model* model;
	glm::mat4 position, orientation;
	float velocity;
	glm::vec3 movement_direction;

	float x,y,z,yaw,pitch,roll;

	public:
	Entity(Model*);
	void setPos(float,float,float);
	void move(float,float,float);
	void thrusters(float);
	void rotateYaw(float);
	void rotatePitch(float);
	void rotateRoll(float);
	void tick();
	GLuint GetTexture() const;
};	
#endif
