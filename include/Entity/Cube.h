/*
 * Plane.h
 *
 *  Created on: 29/12/2017
 *      Author: robertnn
 */

#ifndef CUBE_H_
#define CUBE_H_


#include "Entity.h"

class Cube: public Entity {
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
	Cube();
	virtual ~Cube();
};

#endif /* PLANE_H_ */
