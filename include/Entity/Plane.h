/*
 * Plane.h
 *
 *  Created on: 29/12/2017
 *      Author: robertnn
 */

#ifndef PLANE_H_
#define PLANE_H_


#include "Entity.h"

class Plane: public Entity {
private:
	unsigned int VAO;
	unsigned int EBO;
	unsigned int VBO;
public:
	unsigned int getVAO();
	unsigned int getVBO();
	unsigned int* getRVAO();
	unsigned int* getRVBO();
	void Draw();
	Plane();
	virtual ~Plane();
};

#endif /* PLANE_H_ */
