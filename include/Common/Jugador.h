/*
 * Jugador.h
 *
 *  Created on: 22/5/2018
 *      Author: rober
 */

#ifndef JUGADOR_H_
#define JUGADOR_H_
#include <Shader/shader.h>
#include <cstdlib>

#include <sstream>
#include <iostream>
#include <fstream>
class Jugador {
private:
	unsigned int VAO;
	unsigned int VBO;

public:
	Jugador();
	virtual ~Jugador();
	void Draw(Shader shader);

	float vertices [192] = {};
};

#endif /* JUGADOR_H_ */
