/*
 * Entity.h
 *
 *  Created on: 29/12/2017
 *      Author: robertnn
 */

#ifndef ENTITY_H_
#define ENTITY_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Shader/shader.h"
class Entity {
public:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	Entity();
	void initUniforms(Shader shader);
	void rotate(float rad, glm::vec3 axis);
	void translate(glm::vec3 move);
	void scale(glm::vec3 scale);
	virtual ~Entity();
};

#endif /* ENTITY_H_ */
