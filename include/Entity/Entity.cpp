/*
 * Entity.cpp
 *
 *  Created on: 29/12/2017
 *      Author: robertnn
 */

#include "Entity.h"

Entity::Entity() {
	// TODO Auto-generated constructor stub
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f,100.f);
}
void Entity::initUniforms(Shader shader){
	shader.setMat4("model",model);
	shader.setMat4("view",view);
	shader.setMat4("projection",projection);
}
Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

void Entity::rotate(float rad, glm::vec3 axis){

	model = glm::rotate(model, glm::radians(rad), axis);

}
void Entity::scale(glm::vec3 scale){

	model = glm::scale(model, scale);

}
void Entity::translate(glm::vec3 move){
	view = glm::translate(view, move);
}

