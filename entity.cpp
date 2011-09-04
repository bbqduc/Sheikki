#include "entity.h"
#include <iostream>

Entity::Entity(Model* model_)
	: model(model_),
	position(),
	orientation()
{}

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

	std::cerr << "New position matrix :\n";
	printMatrix(position);
}

GLuint Entity::GetTexture() const
{
	return model->GetTexture();
}
