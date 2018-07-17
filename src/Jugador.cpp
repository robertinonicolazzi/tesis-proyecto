/*
 * Jugador.cpp
 *
 *  Created on: 22/5/2018
 *      Author: rober
 */

#include <Common/Jugador.h>
using namespace std;
Jugador::Jugador() {

	// TODO Auto-generated constructor stub
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Jugador::Draw(Shader shader){
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindVertexArray(VAO);
	glLineWidth(3.0f);
	glDrawArrays(GL_LINES, 0, 200);
}
Jugador::~Jugador() {
	// TODO Auto-generated destructor stub
}

