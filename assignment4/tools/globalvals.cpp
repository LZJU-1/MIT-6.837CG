#include "globalvals.h"


int thetaSteps = 100;
int phiSteps = 100;
bool gouraud = false;
bool shade_back = false;
bool gui = false;
int width = 100;
int height = 100;
float depth_min = 0;
float depth_max = 1;
char adData[50] = "./data/";
char adOut[50] = "./tout/";

void addPrex(char** address, int type) {
    if(type == 0) {
        strcat(adData, *address);
        *address = adData;
    }
    else {
        strcat(adOut, *address);
        *address = adOut;
    }

}