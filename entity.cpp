#include "entity.h"
#include <iostream>

Entity::Entity(Model* model_)
	: model(model_),
	position(),
	orientation(),
	velocity(0),
	movement_direction(0,0,1)
{
}

void Entity::setPos(float x, float y, float z)
{
	position[3] = x;
	position[7] = y;
	position[11] = z;
}

void Entity::rotateYaw(float yaw)
{
	MyMatrix rotation = rotationMatrix(yaw, orientation[1], orientation[5], orientation[9]);
	orientation = rotation * orientation;
}
	
void Entity::rotatePitch(float pitch)
{
	MyMatrix rotation = rotationMatrix(pitch, orientation[0], orientation[4], orientation[8]);
	orientation = rotation * orientation;
}

void Entity::rotateRoll(float roll)
{
	MyMatrix rotation = rotationMatrix(roll, orientation[2], orientation[6], orientation[10]);
	orientation = rotation * orientation;
}

void Entity::move(float x, float y, float z)
{
//	std::cerr << "HERP DERP ENTITY IS MOVING!\n";
	position[3] += x;
	position[7] += y;
	position[11] += z;
}

void Entity::thrusters(float force)
{
	position[3] += (orientation[2] * force);
	position[7] += (orientation[6] * force);
	position[11] += (orientation[10] * force);
}

void tick()
{
	position[3] += (movement_direction[0] * velocity); // x
	position[7] += (movement_direction[1] * velocity); // y
	position[11] += (movement_direction[2] * velocity); // z
}

GLuint Entity::GetTexture() const
{
	return model->GetTexture();
}
