#ifndef ENTITY_H
#define ENTITY_H

#include "model.h"
#include <glm/glm.hpp>

class Shader;

class Entity{
	friend class Graphics; // Graphics needs access to model for drawing
	friend class Engine;
private:
	Shader* activeShader;
protected:
	const Model& model;
	glm::mat4 position, orientation;
	float velocity;
	glm::vec3 movement_direction;

	float x,y,z,yaw,pitch,roll;

public:
	Entity(const Model&);
	void setPos(float,float,float);
	void setVelocity(float);
	void setDirection(glm::vec3& dir);
	
	void move(float,float,float);
	void thrusters(float);
	void rotateYaw(float);
	void rotatePitch(float);
	void rotateRoll(float);
	void rotate(glm::mat4&);
	void tick();
	void tick(bool[]);
	GLuint GetTexture() const;
	//Entity fire();
};	
#endif
