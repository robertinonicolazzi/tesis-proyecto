/*
 * WrapperCV.h
 *
 *  Created on: 28/6/2018
 *      Author: rober
 */

#ifndef WRAPPERAG_H_
#define WRAPPERAG_H_
#define ARX_TARGET_PLATFORM_LINUX 1
#include <ARX/ARController.h>
#include <ARX/ARUtil/time.h>
#include <ARX/ARG/mtx.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

class WrapperAG {

private:
	ARG_API drawAPI;
	bool rotate90;
	bool flipH;
	bool flipV;
	int32_t gViewport[4];
	float projection[16];
	float gProjection[16];
	float gView[16];
	bool gModelLoaded[10];
	float gModelPoses[10][16];
	bool gModelVisbilities[10];





	struct marker {
	    const char *name;
	    float height;
	};
	const char *vconf;
	const char *cpara;
	struct marker markers[2];
	static const int markerCount = (sizeof(markers)/sizeof(markers[0]));
	int markerIDs[markerCount];
	int markerModelIDs[markerCount];
	int drawLoadModel(const char *path);
	void drawSetCamera(float projection[16], float view[16]);
	void drawSetViewport(int32_t viewport[4]);
	void drawSetup(ARG_API drawAPI_in, bool rotate90_in, bool flipH_in, bool flipV_in);
public:
	ARController* arController;
	WrapperAG(char *vconft,char *cpara);
	virtual ~WrapperAG();
	bool InicializarController();
	void ProcesarFrameUpdated(int contextWidth, int contextHeight, int32_t* viewport);
};

#endif /* WRAPPERCV_H_ */
