/*
 * Court.h
 *
 *  Created on: 20/1/2018
 *      Author: robertnn
 */

#ifndef LUGAR_H_
#define LUGAR_H_
#include <Definiciones.h>
#include <Model/model.h>

class Lugar {
public:
	Lugar();
	virtual ~Lugar();
	void Draw(Shader shader);
private:
	Model model;
};

#endif /* COURT_H_ */
