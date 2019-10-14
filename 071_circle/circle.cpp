#include "circle.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
double Circle::intersectionArea(const Circle & otherCircle) {
  double dis = center.distanceFrom(otherCircle.center);
  double sumr = radius + otherCircle.radius;
  if (dis > sumr) {
    return 0;
  }
  double minr = std::abs(radius - otherCircle.radius);
  if (dis <= minr) {
    if (radius <= otherCircle.radius) {
      return M_PI * radius * radius;
    }
    else {
      return M_PI * otherCircle.radius * otherCircle.radius;
    }
  }
  // std::printf("r = %f, or = %f, dis = %f\n", radius, otherCircle.radius, dis);
  double r2 = radius * radius;
  double or2 = otherCircle.radius * otherCircle.radius;
  double d2 = dis * dis;
  double a1 = std::acos((r2 + d2 - or2) / (2 * dis * radius));
  double a2 = std::acos((or2 + d2 - r2) / (2 * dis * otherCircle.radius));
  return r2 * a1 + or2 * a2 - std::sin(a1) * radius * dis;
}
