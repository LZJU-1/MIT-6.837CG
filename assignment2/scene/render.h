#pragma once

#include "../tools/image.h"
#include "scene_parser.h"
#include "camera.h"
#include "material.h"
#include "../objects/group.h"
#include "light.h"
#include "hit.h"


class Render {
protected:
          Image* image;
          SceneParser* scene;
public:
          Render(Image *image = nullptr, SceneParser* scene = nullptr){
                    this->image = image;
                    this->scene = scene;
          }
          virtual void RenderIt(){
                    assert(image != nullptr);
                    image->SetAllPixels(scene->getBackgroundColor());
          };
};


class DepthRender : public Render {
private:
          float dMin, dMax;
public:
          DepthRender(Image *image = nullptr, SceneParser *scene = nullptr,
                           float depthMin = -1, float depthMax = 1) : 
                    dMin(depthMin), dMax(depthMax), Render(image, scene){}
          virtual void RenderIt(){
                    image->SetAllPixels(Vec3f(0, 0, 0));
                    int n = image->Width();
                    int m = image->Height();
                    for(int i = 0; i < n; i++){
                              for(int j = 0; j < m; j++){
;                                       Ray ray = scene->getCamera()->generateRay(
                                                  Vec2f((float)i / image->Width(),
                                                  (float) j / image->Height())
                                        );
                                        Hit h;
                                        if(!scene->getGroup()->
                                        intersect(ray, h, scene->getCamera()->getTMin())) continue;
                                        float t = h.getT();

                                        if(t >= dMin && t <= dMax){
                                                  float dcolor = (t - dMin) / (dMax - dMin);
                                                  image->SetPixel(i, j, Vec3f(dcolor, dcolor, dcolor));
                                        }

                              }
                    }
          }
};

class ColorRender : public Render {
public:
          ColorRender(Image *image = nullptr, SceneParser *scene = nullptr) :
            Render(image, scene) {}

          virtual void RenderIt(){
                    Render::RenderIt();
                    int n = image->Width();
                    int m = image->Height();
                    for(int i = 0; i < n; i++){
                              for(int j = 0; j < m; j++){
;                                       Ray ray = scene->getCamera()->generateRay(
                                                  Vec2f((float)i / image->Width(),
                                                  (float) j / image->Height())
                                        );
                                        Hit h;
                                        if(!scene->getGroup()->
                                        intersect(ray, h, scene->getCamera()->getTMin())) continue;
                                        
                                        image->SetPixel(i, j, h.getMaterial()->getDiffuseColor());     
                              }
                    }
          }
};

class NormalRender : public Render {
public:
          NormalRender(Image *image = nullptr, SceneParser *scene = nullptr) :
            Render(image, scene) {}

          virtual void RenderIt(){
                    image->SetAllPixels(Vec3f(0, 0, 0));
                    int n = image->Width();
                    int m = image->Height();
                    for(int i = 0; i < n; i++){
                              for(int j = 0; j < m; j++){
;                                       Ray ray = scene->getCamera()->generateRay(
                                                  Vec2f((float)i / image->Width(),
                                                  (float) j / image->Height())
                                        );
                                        Hit h;
                                        if(!scene->getGroup()->
                                        intersect(ray, h, scene->getCamera()->getTMin())) continue;
                                        
                                        Vec3f normal = h.getNormal();
                                        image->SetPixel(i, j, Vec3f(fabs(normal.x()), fabs(normal.y()), fabs(normal.z())));
                              }
                    }
          }
};

class DiffuseRender : public Render {
public:
           DiffuseRender(Image *image = nullptr, SceneParser *scene = nullptr, bool shadeBack = false) :
            Render(image, scene), shadeBack(shadeBack) {}

          virtual void RenderIt() {
                    Render::RenderIt();
                    int n = image->Width();
                    int m = image->Height();
                    for(int i = 0; i < n; i++){
                              for(int j = 0; j < m; j++){
;                                       Ray ray = scene->getCamera()->generateRay(
                                                  Vec2f((float)i / image->Width(),
                                                  (float) j / image->Height())
                                        );
                                        Hit h;
                                        if(!scene->getGroup()->
                                        intersect(ray, h, scene->getCamera()->getTMin())) continue;
                                        
                                        Vec3f color = Vec3f(0, 0 , 0);
                                        Vec3f diffColor = h.getMaterial()->getDiffuseColor();

                                        for(int k = 0; k < scene->getNumLights(); k++) {
                                                  Light* li = scene->getLight(k);
                                                  Vec3f liDir, liCol;
                                                  li->getIllumination(h.getIntersectionPoint(), liDir, liCol);

                                                  Vec3f n = h.getNormal();
                                                  if(shadeBack && ray.getDirection().Dot3(n) > 0){
                                                            n.Scale(-1, -1, -1);
                                                  }

                                                  float t = liDir.Dot3(n) > 0 ? liDir.Dot3(n) : 0;
                                                  liCol.Scale(t * diffColor.x(), t * diffColor.y(), t * diffColor.z());
                                                  color += liCol;
                                        }   

                                        Vec3f ambCol = scene->getAmbientLight();
                                        ambCol.Scale(diffColor.x(), diffColor.y(), diffColor.z());
                                        color += ambCol;
                                        color.Clamp();

                                        image->SetPixel(i, j, color);
                              }
                    }
          }

private:
          bool shadeBack;
};