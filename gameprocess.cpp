//PURELY DEMO FILLED FILE
//Main file for absolute freedom, all draw programming not opengl-core specifc should be done in here.
//Standard libraries
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
//External engine dependencies
#include "figureslib.hpp"
#include "cameralib.hpp"
#include "interfacelib.hpp"
#include "shaderslib.hpp"
#include "rocketcalc.hpp"
#include "metrics.hpp"
#include "barometric.h"
//CROSS-FILE VALUES: Freely change these
char VERTEXSHADERFILE[BUFSIZE] = "samplevs.vert";
char FRAGMENTSHADERFILE[BUFSIZE] = "samplefg.frag";
char WINDOWTITLE[BUFSIZE] = "Rocket Simulator";
unsigned int DISPLAYFLAGS = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA;
unsigned int ENABLEFLAGS = GL_DEPTH_TEST;

void falconheavy(void) {
    static int r = 0;
    fullrocket falcon9;
    falcon9.rbody.height = 70;
    falcon9.rbody.radius = 1.83f;
    falcon9.rbody.hullthickness = 0.0047;
    falcon9.rbody.accuratebodymass = 1420788;
    falcon9.rbody.totalbodymass = 6000000;
    falcon9.rbody.material = STAINLESSSTEEL;
    falcon9.rbody.rcylinder.xcoord = -35.0f * METER;
    falcon9.rbody.rcylinder.ycoord = -20.0f * METER;
    falcon9.rbody.rcylinder.zcoord = -3.0f * METER;
    falcon9.rbody.rcylinder.vertexnum = 90;
    falcon9.rstaging.payloadmass = 100;
    falcon9.rstaging.propellantmass[0] = 1222800;
    falcon9.rstaging.propellantmass[1] = 107200;
    falcon9.rstaging.structuremass[0] = 51000;
    falcon9.rstaging.structuremass[1] = 4500;
    falcon9.rstaging.specificimpulse = 312;
    falcon9.rbody.calcBodyHeight();
    falcon9.rstaging.calctotalmass(0);
    falcon9.rstaging.calctotalmass(1);
    falcon9.rbody.renderRocketCylinder(GL_TRIANGLE_STRIP);
    falcon9.rstaging.renderStaging(STAGINGTYPEPARALLEL, falcon9.rbody);
    falcon9.rpayload.height = 15.0f;
    falcon9.rpayload.renderRocketTip(GL_POLYGON, falcon9.rbody);
    falcon9.rfins.finheight = 25.0f;
    falcon9.rfins.finwidth = 10.0f;
    falcon9.rfins.finthickness = 0.2f;
    falcon9.rfins.renderFins(true, falcon9);
    if (r == 0) {
        std::cout << "SpaceX Falcon 9 Evaluation:\n";
        rocketdeltaveval(&falcon9.rstaging, 0);
        falcon9.rstaging.specificimpulse = 348;
        rocketdeltaveval(&falcon9.rstaging, 1);
        std::cout << "HEIGHT: " << falcon9.rbody.height << std::endl;
        std::cout << "TOTAL MASS: " << falcon9.rstaging.totalmass[0] << "\n";
        std::cout << "EXHAUST VELOCITY: " << falcon9.rstaging.exhaustvelocity << std::endl;
        std::cout << "SURFACE AREA: " << falcon9.calcSurfaceArea() << std::endl;
        falcon9.rfins.atmosphericDensity = 0.00052;
        falcon9.rfins.averagevelocity = (falcon9.rstaging.calcdeltav(0) / 2);
        falcon9.rfins.dragCoefficient = 0.716;
        falcon9.rfins.liftCoefficient = 0.85;
        std::cout << "LIFT FORCE: " << falcon9.rfins.calcliftforce(1000) << std::endl;
        std::cout << "DRAG FORCE: " << falcon9.rfins.calcdragforce(1000) << std::endl;
        r++;
    }
}
void glsetup (void) {
    return;
}

void bindinterface (void) {
    bindmousecontrol();
    bindarrowkeycontrol();
    bindnormalkeycontrol();
    return;
}

void eventhandler(void) {
    return;
}

void mainprocess (void) {
    gridlines(2);
    falconheavy();
    return;
}