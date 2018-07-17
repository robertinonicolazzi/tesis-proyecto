/*
 * Partido.cpp
 *
 *  Created on: 16/7/2018
 *      Author: rober
 */

#include <Common/Partido.h>

Partido::Partido() {
	// TODO Auto-generated constructor stub
	Shader temp("7.4.camera.vs", "7.4.camera.fs");
	playerShader = temp;
	Shader temp("resources/shaders/model_light.vs", "resources/shaders/model_light.fs");
	courtShader = temp;
	Lugar court;
}

Partido::~Partido() {
	// TODO Auto-generated destructor stub
}

void Partido::DrawAll(){
	DrawPlayers();
	DrawCourt();
}
void Partido::DrawCourt() {
	glm::mat4 model=glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
	courtShader.use();
	courtShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	courtShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
	courtShader.setVec3("lightPos", 1.0f, 2.0f, 10.0f);
	courtShader.setMat4("projection", projection);
	courtShader.setMat4("view", view);
	courtShader.setMat4("model", model);
	court.Draw(courtShader);
}

void Partido::DrawPlayers() {
	playerShader.use();
	playerShader.setMat4("projection", projection);
	playerShader.setMat4("view", view);

	glm::mat4 model=glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f,1.4f,12.0f));
	model = glm::scale(model, glm::vec3(0.7f,0.7f,0.7f));
	for (unsigned int i = 0; i < list_personas.size(); i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		Jugador temp = list_personas[i];
		playerShader.setMat4("model", model);
		temp.Draw(playerShader);
	}
}

void Partido::LoadPlayers(int frame){
	this->ProcesarArchivo3dPose(frame);
}

void Partido::ProcesarArchivo3dPose(int frame){
	using namespace rapidjson;
	float relaciones[] = {1,2, 2,3, 3,4, 1,5,5,6,6,7, 1,8, 8,9, 9,10, 1,11, 11,12, 12, 13 };
	std::string path = "";
	std::string String = "";
	String = static_cast<std::ostringstream*>( &(std::ostringstream() << frame) )->str();
	path = "";
	path.append("/media/rober/DatosLinux/Tesis/output_3dpose/json/test");
	if(frame < 10){
		path.append("_00000000000");
	} else if (frame < 100) {
		path.append("_0000000000");
	} else if (frame < 1000) {
		path.append("_000000000");
	} else {
		path.append("_00000000");
	}
	path.append(String);
	path.append(".json");
	std::ifstream ifs { path.c_str() };
	if ( !ifs.is_open() )
	{
		return;
	}
	IStreamWrapper isw { ifs };
	Document doc {};
	doc.ParseStream( isw );
	/*Value& personas = doc["person"];
    assert(personas.IsArray());*/



	list_personas.clear();
/*
	for (SizeType i = 0; i < personas.Size(); i++){
		using namespace rapidjson;
		*/
	    Jugador eJugador;

		Value& original = doc["person"];
		int I [16] = {0,1,2,0,6,7,0,12,13,14,13,17,18,13,25,26};
		int J [16] = {1,2,3,6,7,8,12,13,14,15,17,18,19,25,26,27};
		float r = 0;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = 0;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = 0;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		int joint = 0;
		for(int k=0;k<16;k++){
			int j_i = I[k];
			int j_f = J[k];
			eJugador.vertices[joint]   = original[j_i*3].GetFloat();
			eJugador.vertices[joint+2] = (-1)*original[j_i*3+1].GetFloat();
			eJugador.vertices[joint+1] = original[j_i*3+2].GetFloat();


			eJugador.vertices[joint+3] = r;
			eJugador.vertices[joint+4] = g;
			eJugador.vertices[joint+5] = b;
			eJugador.vertices[joint+9] = r;
			eJugador.vertices[joint+10] = g;
			eJugador.vertices[joint+11] = b;

			eJugador.vertices[joint+6] = original[j_f*3].GetFloat();
			eJugador.vertices[joint+8] = (-1)*original[j_f*3+1].GetFloat();
			eJugador.vertices[joint+7] = original[j_f*3+2].GetFloat();
			joint+=12;
		}
		list_personas.push_back(eJugador);
	//}
}
void Partido::ProcesarArchivoOpenPose(int frame){
	using namespace rapidjson;
	float relaciones[] = {1,2, 2,3, 3,4, 1,5,5,6,6,7, 1,8, 8,9, 9,10, 1,11, 11,12, 12, 13 };
	std::string path = "";
	std::string String = "";
	String = static_cast<std::ostringstream*>( &(std::ostringstream() << frame) )->str();
	path = "";
	path.append("/home/rober/Test/output_tenis_dos_4/pruebados");
	if(frame < 10){
		path.append("_00000000000");
	} else if (frame < 100) {
		path.append("_0000000000");
	} else if (frame < 1000) {
		path.append("_000000000");
	} else {
		path.append("_00000000");
	}
	path.append(String);
	path.append("_keypoints.json");
	std::ifstream ifs { path.c_str() };
	if ( !ifs.is_open() )
	{
		return;
	}
	IStreamWrapper isw { ifs };
	Document doc {};
	doc.ParseStream( isw );
	Value& personas = doc["people"];
    assert(personas.IsArray());


	float parent;
	float child;
	int rel;
	list_personas.clear();

	for (SizeType i = 0; i < personas.Size(); i++){
		using namespace rapidjson;
		Jugador eJugador;
		parent = 0;
		child = 0;
		rel = 0;
		Value& keypoints = personas[i]["pose_keypoints_2d"];
		for(int j=0; j<24; j += 2){
			parent = relaciones[j];
			child = relaciones[j+1];
			if(keypoints[parent*3+2].GetFloat() >= 0.1f){
				eJugador.vertices[rel] = keypoints[parent*3].GetFloat();
				eJugador.vertices[rel+1] = keypoints[parent*3+1].GetFloat()*(-1);
			}
			eJugador.vertices[rel+2] = 0.0f;
			eJugador.vertices[rel+3] = 1.0f;
			eJugador.vertices[rel+4] = 0.0f;
			eJugador.vertices[rel+5] = 0.0f;
			rel += 6;

			if(keypoints[child*3+2].GetFloat() >= 0.1f){
				eJugador.vertices[rel] = keypoints[child*3].GetFloat();
				eJugador.vertices[rel+1] = keypoints[child*3+1].GetFloat()*(-1);
			}
			eJugador.vertices[rel+2] = 0.0f;
			eJugador.vertices[rel+3] = 1.0f;
			eJugador.vertices[rel+4] = 0.0f;
			eJugador.vertices[rel+5] = 0.0f;
			rel += 6;
		}
		list_personas.push_back(eJugador);
	}
}


