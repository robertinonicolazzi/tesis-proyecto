/*
 * WindowManager.h
 *
 *  Created on: 18/7/2018
 *      Author: rober
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_
#define ARX_TARGET_PLATFORM_LINUX 1
#include <ARX/ARController.h>
#include <ARX/ARUtil/time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

class WindowManager {
public:
	SDL_GLContext gSDLContext;
	int contextWidth = 0;
	int contextHeight = 0;
	bool contextWasUpdated = false;
	int32_t viewport[4];
	float projection[16];
	SDL_Window* gSDLWindow;
	ARG_API drawAPI = ARG_API_None;
	void ProcesarArgumentos(int argc, char *argv[]);
	WindowManager();
	void InicializarVentada();
	virtual ~WindowManager();
	char * getVconf();
	char * getCpara();
	bool ProcesarEventos();
	bool getContextWasUpdated();
	void setContextWasUpdated(bool value);
private:
	char *vconf = NULL;
	char *cpara = NULL;


	void reshape(int w, int h);
	void quit(int rc);
	void usage(char *com);
};

#endif /* WINDOWMANAGER_H_ */
