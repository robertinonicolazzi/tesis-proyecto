/*
 * Court.cpp
 *
 *  Created on: 20/1/2018
 *      Author: robertnn
 */

#include <Common/Lugar.h>

Lugar::Lugar() {
    Model ourModel("resources/untitled.obj");
    model = ourModel;


}
void Lugar::Draw(Shader shader) {
	model.Draw(shader);
}

Lugar::~Lugar() {
	// TODO Auto-generated destructor stub
}

