#ifndef ENTITY_H
#define ENTITY_H

#include "model.h"
#include "mymatrix.h"
#include "vec.h"

class Entity{
	friend class Graphics; // Graphics needs access to model for drawing
	Model* model;
	MyMatrix position,
		 orientation; // Save position and orientation as matrices for efficiency
	float velocity;
	Vec<3> movement_direction;

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
