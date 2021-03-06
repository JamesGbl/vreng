#ifndef COLOR_H
#define COLOR_H

#include "vect.hpp"

class Color {

public:
  Color(const GLfloat* _color);
  Color(const float r, const float g, const float b, const float a);
  operator const GLfloat* const() const {return color;}
  bool operator==(const Color&) const;

  void Apply() const {glMaterialfv(GL_FRONT, GL_AMBIENT, color);}
  void Print() const;

  const static Color black, white, red, green, blue;

private:
  GLfloat color[4];

};

#endif


