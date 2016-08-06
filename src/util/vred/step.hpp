#ifndef STEP_H
#define STEP_H

#include "box.hpp"

class Step : public Box {

public:
  Step(char* _name,
       const Vect& _center = Vect::null,
       const Vect& _orientation = Vect::null,
       const Vect& _size = Vect::unit,
       int _renderStyle = WIRED, const Color& _color = Color::white,
       const Tex& _tex = Tex(), const App& _app = App());

  virtual int GetClassId() const {return STEP;}
  virtual const char* GetClassName() const {return "step";}

  friend ostream& operator<<(ostream& out, const Step& s);

};

#endif
