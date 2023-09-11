#include <iostream>
#include <cassert>
#include <cstring>

#include "./scene/scene_parser.h"
#include "./tools/image.h"
#include "./scene/camera.h"
#include "./scene/hit.h"
#include "./objects/group.h"
#include "./scene/material.h"
#include "./scene/render.h"

int main(int argc, char *argv[]) {
    char *input_file = nullptr;
    int width = 100;
    int height = 100;
    char *output_file = nullptr;
    char *normal_file = nullptr;
    float depth_min = 0;
    float depth_max = 1;
    char *depth_file = nullptr;
    bool shade_back = false;

    // sample command line:
    // raytracer -input scene1_1.txt -size 200 200 -output output1_1.tga -depth 9 10 depth1_1.tga

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-input")) {
            i++;
            assert(i < argc);
            input_file = argv[i];
        } else if (!strcmp(argv[i], "-size")) {
            i++;
            assert(i < argc);
            width = atoi(argv[i]);
            i++;
            assert(i < argc);
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-output")) {
            i++;
            assert(i < argc);
            output_file = argv[i];
        } else if (!strcmp(argv[i], "-depth")) {
            i++;
            assert(i < argc);
            depth_min = atof(argv[i]);
            i++;
            assert(i < argc);
            depth_max = atof(argv[i]);
            i++;
            assert(i < argc);
            depth_file = argv[i];
        } else if (!strcmp(argv[i], "-normals")){
            i++;
            assert(i < argc);
            normal_file = argv[i];
        } else if (!strcmp(argv[i], "-shade_back")){
            shade_back = true;
        } else {
            printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
            assert(0);
        }
    }

    SceneParser* total = new SceneParser(input_file);
    if(output_file) {
        Image* colorFile = new Image(width, height);
        Render* render = new DiffuseRender(colorFile, total, shade_back);
        render->RenderIt();
        colorFile->SaveTGA(output_file);
    }
    if(normal_file) {
        Image* nomalFile = new Image(width, height);
        Render* render = new NormalRender(nomalFile, total);
        render->RenderIt();
        nomalFile->SaveTGA(normal_file);
    }
    if(depth_file) {
        Image* deptFile = new Image(width, height);
        Render* render = new DepthRender(deptFile, total, depth_min, depth_min);
        render->RenderIt();
        deptFile->SaveTGA(depth_file);
    }


    cout << "All Task Finished!" << endl;
    return 0;
}