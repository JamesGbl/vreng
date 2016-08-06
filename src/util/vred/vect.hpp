#ifndef VECT_H
#define VECT_H

class Vect {

public:
  Vect(const double x = 0, const double y = 0, const double z = 0);

  double operator[](const int n) const;
  double& operator[](const int n);
  Vect operator+(const Vect&) const;
  Vect& operator+=(const Vect&);
  Vect operator-(const Vect&) const;
  Vect& operator-=(const Vect& v);
  double operator*(const Vect& v) const;
  Vect operator^(const Vect& v) const;
  friend Vect operator*(const double d, const Vect& v);
  Vect& operator*=(const double d);
  bool operator==(const Vect&) const;

  double Norm() const {return (x * x + y * y + z * z);}
  void Print() const;

  const static Vect null, unit;

private:
  double  x, y, z;

};

#endif
