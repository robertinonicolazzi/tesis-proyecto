/*
 * Partido.h
 *
 *  Created on: 16/7/2018
 *      Author: rober
 */

#ifndef PARTIDO_H_
#define PARTIDO_H_

#include <Common/Lugar.h>
#include <Common/Jugador.h>
#include <Shader/shader.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
const double maxFPS = 60.0;
const double maxPeriod = 1.0 / maxFPS;
class Partido {
private:
	std::vector<Jugador> list_personas;
	Lugar court;
	Shader playerShader;
	Shader courtShader;
	void ProcesarArchivo3dPose(int frame);
	void ProcesarArchivoOpenPose(int frame);
public:
	Partido();
	virtual ~Partido();
	void DrawPlayers();
	void DrawCourt();
	void DrawAll();
	void LoadPlayers(int frame);

};

#endif /* PARTIDO_H_ */
