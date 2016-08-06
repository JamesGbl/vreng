#ifndef EARTH_H
#define EARTH_H

#include "sphere.hpp"

class Earth : public Sphere {

public:
  Earth(char* _name,
       const Vect& _center = Vect::null,
       const Vect& _orientation = Vect::null,
       const Vect& _size = Vect::unit,
       const int _renderStyle = WIRED,
       const Color& _color = Color::white,
       const Tex& _tex = Tex(), const App& _app = App(),
       const int _slices = 10, const int _stacks = 10);

  virtual int     GetClassId() const {return EARTH;}
  virtual const char*   GetClassName() const {return "earth";}

  friend ostream& operator<<(ostream& out, const Earth& earth);

};

#endif
