#ifndef __VECTOR_H__
  #define __VECTOR_H__

  #include <math.h>

  #ifndef PI2
    #define PI2 6.28318530717958647692528676655901
  #endif

  #define DELTA_A360_TO_A256 0.71111111111111111111111111111111111111111111
  #define DELTA_A256_TO_A360 1.40625
  #define DELTA_A360_TO_RAD 0.0174532925199432957692369076848861
  #define DELTA_A256_TO_RAD 0.0245436926061702596754894014318711
  #define DELTA_RAD_TO_A360 57.2957795130823208767981548141052
  #define DELTA_RAD_TO_A256 40.7436654315252059568342434233637
  
class Vector
{
  public:
    Vector() : x1(0),y1(0),angle(0),r(0),x2(0),y2(0) {}
    Vector(double _x1,double _y1,double _angle,double _r)
      : x1(_x1),y1(_y1),angle(_angle),r(_r),x2(0),y2(0)
    { Calc(); }
    ~Vector() {}
    void Calc()
    {
      x2 = x1 + cos(angle) * r;
      y2 = y1 + sin(angle) * r;  
    }
    double x1,y1,angle,r,x2,y2;
};  

static double a360_to_a256(double a360)
{
  return a360 * DELTA_A360_TO_A256;
}

static double a256_to_a360(double a256)
{
  return a256 * DELTA_A256_TO_A360;
}

static double a360_to_rad(double angle)
{
  return angle * DELTA_A360_TO_RAD;
}

static double a256_to_rad(double angle)
{
  return angle * DELTA_A256_TO_RAD;
}

static double rad_to_a360(double rad)
{
  return rad * DELTA_RAD_TO_A360;
}

static double rad_to_a256(double rad)
{
  return rad * DELTA_RAD_TO_A256;
}


#endif
