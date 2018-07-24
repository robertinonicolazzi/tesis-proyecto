/*
 * WindowManager.cpp
 *
 *  Created on: 18/7/2018
 *      Author: rober
 */

#include <Common/WindowManager.h>

WindowManager::WindowManager() {
	// TODO Auto-generated constructor stub

}

WindowManager::~WindowManager() {
	// TODO Auto-generated destructor stub
}
bool WindowManager::getContextWasUpdated(){
	return contextWasUpdated;
}
void WindowManager::setContextWasUpdated(bool value){
	contextWasUpdated = value;
}
char * WindowManager::getVconf(){
	return vconf;
}
char * WindowManager::getCpara(){
	return cpara;
}
void WindowManager::InicializarVentada(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ARLOGe("Error: SDL initialisation failed. SDL error: '%s'.\n", SDL_GetError());
		quit(1);
		return;
	}

	SDL_Window* gSDLWindow = SDL_CreateWindow("artoolkitX Square Tracking Example",
								  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								  1280, 720,
								  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
								  );

	if (!gSDLWindow) {
		ARLOGe("Error creating window: %s.\n", SDL_GetError());
		quit(-1);
	}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext gSDLContext = SDL_GL_CreateContext(gSDLWindow);
	if (gSDLContext) {
		drawAPI = ARG_API_GL3;
		ARLOGi("Created OpenGL 3.2+ context.\n");
	} else {
		ARLOGi("Unable to create OpenGL 3.2 context: %s. Will try OpenGL 1.5.\n", SDL_GetError());
	}
	if (drawAPI == ARG_API_None) {
		ARLOGe("No OpenGL context available. Giving up.\n", SDL_GetError());
		quit(-1);
	}

	int w, h;
	SDL_GL_GetDrawableSize(SDL_GL_GetCurrentWindow(), &w, &h);
	reshape(w, h);
}

void WindowManager::ProcesarArgumentos(int argc, char *argv[])
{
	int i, gotTwoPartOption;

	//
	// Command-line options.
	//
	vconf = "-dev=/dev/video1";
	i = 1; // argv[0] is name of app, so start at 1.
	while (i < argc) {
		gotTwoPartOption = FALSE;
		// Look for two-part options first.
		if ((i + 1) < argc) {
			if (strcmp(argv[i], "--vconf") == 0) {
				i++;
				vconf = argv[i];
				gotTwoPartOption = TRUE;
			} else if (strcmp(argv[i], "--cpara") == 0) {
				i++;
				cpara = argv[i];
				gotTwoPartOption = TRUE;
			}
		}
		if (!gotTwoPartOption) {
			// Look for single-part options.
			if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "-h") == 0) {
				usage(argv[0]);
			} else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-version") == 0 || strcmp(argv[i], "-v") == 0) {
				ARPRINT("%s version %s\n", argv[0], AR_HEADER_VERSION_STRING);
				exit(0);
			} else if( strncmp(argv[i], "-loglevel=", 10) == 0 ) {
				if (strcmp(&(argv[i][10]), "DEBUG") == 0) arLogLevel = AR_LOG_LEVEL_DEBUG;
				else if (strcmp(&(argv[i][10]), "INFO") == 0) arLogLevel = AR_LOG_LEVEL_INFO;
				else if (strcmp(&(argv[i][10]), "WARN") == 0) arLogLevel = AR_LOG_LEVEL_WARN;
				else if (strcmp(&(argv[i][10]), "ERROR") == 0) arLogLevel = AR_LOG_LEVEL_ERROR;
				else usage(argv[0]);
			} else {
				ARLOGe("Error: invalid command line argument '%s'.\n", argv[i]);
				usage(argv[0]);
			}
		}
		i++;
	}
}

void WindowManager::usage(char *com)
{
	ARPRINT("Usage: %s [options]\n", com);
	ARPRINT("Options:\n");
	ARPRINT("  --vconf <video parameter for the camera>\n");
	ARPRINT("  --cpara <camera parameter file for the camera>\n");
	ARPRINT("  --version: Print artoolkitX version and exit.\n");
	ARPRINT("  -loglevel=l: Set the log level to l, where l is one of DEBUG INFO WARN ERROR.\n");
	ARPRINT("  -h -help --help: show this message\n");
	exit(0);
}

bool WindowManager::ProcesarEventos(){
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
			return true;
			break;
		} else if (ev.type == SDL_WINDOWEVENT) {
			//ARLOGd("Window event %d.\n", ev.window.event);
			if (ev.window.event == SDL_WINDOWEVENT_RESIZED && ev.window.windowID == SDL_GetWindowID(gSDLWindow)) {
				//int32_t w = ev.window.data1;
				//int32_t h = ev.window.data2;
				int w, h;
				SDL_GL_GetDrawableSize(gSDLWindow, &w, &h);
				reshape(w, h);
			}
		} else if (ev.type == SDL_KEYDOWN) {
			if (ev.key.keysym.sym == SDLK_d) {
				//arController->getSquareTracker()->setDebugMode(!arController->getSquareTracker()->debugMode());
			}
		}
	 }
	return false;
}
void WindowManager::quit(int rc)
{
	//drawCleanup();
	//if (arController) {
	//	arController->drawVideoFinal(0);
	//	arController->shutdown();
	//	delete arController;
	//}
	if (gSDLContext) {
		SDL_GL_MakeCurrent(0, NULL);
		SDL_GL_DeleteContext(gSDLContext);
	}
	if (gSDLWindow) {
		SDL_DestroyWindow(gSDLWindow);
	}
	SDL_Quit();
	exit(rc);
}

void WindowManager::reshape(int w, int h)
{
	contextWidth = w;
	contextHeight = h;
	ARLOGd("Resized to %dx%d.\n", w, h);
	contextWasUpdated = true;
}

