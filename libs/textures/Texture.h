#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture{
public:
  virtual Vector3 value(double u, double v, Point3& p) = 0;
};

#endif
