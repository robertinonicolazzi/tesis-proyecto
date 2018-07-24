/*
 * WrapperCV.cpp
 *
 *  Created on: 28/6/2018
 *      Author: rober
 */

#include <Common/WrapperAG.h>
using namespace std;


WrapperAG::WrapperAG(char* vconft, char* cparam) {
	vconf = vconft;
	cpara = cparam;
	drawAPI = ARG_API_None;
	rotate90 = false;
	flipH = false;
	flipV = false;
	gViewport[4] = {0};
	gModelLoaded[10] = {false};
	arController = NULL;
	markers[0] =  {"hiro.patt", 80.0};
	markers[1] = {"kanji.patt", 80.0};

}
void WrapperAG::ProcesarFrameUpdated(int contextWidth, int contextHeight, int32_t* viewport) {
	if (!arController->drawVideoInit(0)) {
		ARLOGe("Error in ARController::drawVideoInit().\n");
		//quit(-1);
	}
	if (!arController->drawVideoSettings(0, contextWidth, contextHeight, false, false, false, ARVideoView::HorizontalAlignment::H_ALIGN_CENTRE, ARVideoView::VerticalAlignment::V_ALIGN_CENTRE, ARVideoView::ScalingMode::SCALE_MODE_FIT, viewport)) {
		ARLOGe("Error in ARController::drawVideoSettings().\n");
		//quit(-1);
	}
	drawSetup(drawAPI, false, false, false);

	drawSetViewport(viewport);
	ARdouble projectionARD[16];
	arController->projectionMatrix(0, 10.0f, 10000.0f, projectionARD);
	for (int i = 0; i < 16; i++) projection[i] = (float)projectionARD[i];
	drawSetCamera(projection, NULL);

	for (int i = 0; i < markerCount; i++) {
		markerModelIDs[i] = drawLoadModel(NULL);
	}
}
int WrapperAG::drawLoadModel(const char *path)
{
    // Ignore path, we'll always draw a cube.
    for (int i = 0; i < 10; i++) {
        if (!gModelLoaded[i]) {
            gModelLoaded[i] = true;
            return i;
        }
    }
    return -1;
}
void WrapperAG::drawSetCamera(float projection[16], float view[16])
{
    if (projection) {
        if (flipH || flipV) {
            mtxLoadIdentityf(gProjection);
            mtxScalef(gProjection, flipV ? -1.0f : 1.0f,  flipH ? -1.0f : 1.0f, 1.0f);
            mtxMultMatrixf(gProjection, projection);
        } else {
            mtxLoadMatrixf(gProjection, projection);
        }
    } else {
        mtxLoadIdentityf(gProjection);
    }
    if (view) {
        mtxLoadMatrixf(gView, view);
    } else {
        mtxLoadIdentityf(gView);
    }
}
void WrapperAG::drawSetViewport(int32_t viewport[4])
{
    gViewport[0] = viewport[0];
    gViewport[1] = viewport[1];
    gViewport[2] = viewport[2];
    gViewport[3] = viewport[3];
}
void WrapperAG::drawSetup(ARG_API drawAPI_in, bool rotate90_in, bool flipH_in, bool flipV_in)
{

    drawAPI = drawAPI_in;
    rotate90 = rotate90_in;
    flipH = flipH_in;
    flipV = flipV_in;

    return;
}

bool WrapperAG::InicializarController(){
	// Initialise the ARController.
	arController = new ARController();
	if (!arController->initialiseBase()) {
		ARLOGe("Error initialising ARController.\n");
		return false;
	}

	#ifdef DEBUG
	arLogLevel = AR_LOG_LEVEL_DEBUG;
	#endif

	// Add trackables.
	int markerIDs[markerCount];
	int markerModelIDs[markerCount];
	#ifdef DEBUG
	char buf[MAXPATHLEN];
	ARLOGd("CWD is '%s'.\n", getcwd(buf, sizeof(buf)));
	#endif
	char *resourcesDir = arUtilGetResourcesDirectoryPath(AR_UTIL_RESOURCES_DIRECTORY_BEHAVIOR_USE_EXECUTABLE_DIR);
	for (int i = 0; i < markerCount; i++) {
		std::string markerConfig = "single;" + std::string(resourcesDir) + '/' + markers[i].name + ';' + std::to_string(markers[i].height);
		markerIDs[i] = arController->addTrackable(markerConfig);
		if (markerIDs[i] == -1) {
			ARLOGe("Error adding marker.\n");
			return false;
		}
	}
	arController->getSquareTracker()->setPatternDetectionMode(AR_TEMPLATE_MATCHING_MONO);
	arController->getSquareTracker()->setThresholdMode(AR_LABELING_THRESH_MODE_AUTO_BRACKETING);


	ARLOGd("vconf is '%s'.\n", vconf);

	// Start tracking.
	arController->startRunning(vconf, cpara, NULL, 0);
}
WrapperAG::~WrapperAG() {
	// TODO Auto-generated destructor stub
}

