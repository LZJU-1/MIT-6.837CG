#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../tools/vectors.h"
#include "ray.h"
#include "light.h"
#include "hit.h"
#include "glCanvas.h" 
#include "GL/glut.h"

#ifdef SPECULAR_FIX
// OPTIONAL:  global variable allows (hacky) communication 
// with glCanvas::display
extern int SPECULAR_FIX_WHICH_PASS;
#endif


// ====================================================================
// ====================================================================

// You will extend this class in later assignments

class Material {

public:

  // CONSTRUCTORS & DESTRUCTOR
  Material(const Vec3f &d_color) { diffuseColor = d_color; }
  virtual ~Material() {}

  // ACCESSORS
  virtual Vec3f getDiffuseColor() const { return diffuseColor; }
  virtual Vec3f Shade
    (const Ray &ray, const Hit &hit, const Vec3f &dirToLight, 
     const Vec3f &lightColor) const = 0;
  virtual void glSetMaterial() const = 0;

protected:

  // REPRESENTATION
  Vec3f diffuseColor;
  
};

class PhongMaterial : public Material {
private:
    Vec3f specularColor;
    float exponent;
public:
    PhongMaterial(const Vec3f &diffuseColor, 
     const Vec3f &specularColor, float exponent) : Material(diffuseColor), specularColor(specularColor), exponent(exponent) {}
    virtual Vec3f Shade
    (const Ray &ray, const Hit &hit, const Vec3f &dirToLight, 
     const Vec3f &lightColor) const;
    virtual void glSetMaterial() const;
    virtual Vec3f getSpecularColor() const {return specularColor;}
};

// ====================================================================
// ====================================================================

#endif