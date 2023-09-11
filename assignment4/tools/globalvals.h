
#pragma once
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

extern int thetaSteps;
extern int phiSteps;
extern bool gouraud;
extern bool shade_back;
extern bool gui;
extern int width;
extern int height;
extern float depth_min;
extern float depth_max;
extern char adData[50];
extern char adOut[50];
extern void addPrex(char** address, int type);