#include "point.h"
class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & p, double r) : center(p), radius(r){};
  void move(double dx, double dy) { center.move(dx, dy); }
  double intersectionArea(const Circle & otherCircle);
};
