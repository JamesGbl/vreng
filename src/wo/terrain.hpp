//---------------------------------------------------------------------------
// VREng (Virtual Reality Engine)	http://vreng.enst.fr/
//
// Copyright (C) 1997-2009 Philippe Dax
// Telecom-ParisTech (Ecole Nationale Superieure des Telecommunications)
//
// VREng is a free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public Licence as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// VREng is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//---------------------------------------------------------------------------
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "wobject.hpp"

#define TERRAIN_TYPE	67
#define TERRAIN_NAME	"Terrain"

typedef struct {GLfloat x; GLfloat y; GLfloat z;} tVect;

/**
 * Terrain class
 */
class Terrain: public WObject {

protected:
  static const uint8_t DEF_LEVEL;
  static const GLfloat DEF_HEIGHT;
  static const GLfloat DEF_DIV;
  static const GLfloat DEF_SCALE;
  static const GLfloat DEF_COLOR[];

  GLfloat *mesh;	///< mesh
  tVect *normales;	///< normales
  uint8_t level;	///< number of iterations
  float height;		///< base height
  float div;		///< factor to divide height 
  float mul;		///< coeff to multiply div factor
  uint8_t size;
  GLfloat color[4];	///< basic color
  GLfloat scale;	///< scale factor
  GLint dlist;		///< display-list

public:
  static const OClass oclass;	///< class variable

  virtual const OClass* getOClass() {return &oclass;}

  static void funcs();	///< init funclist

  Terrain(char *l);	///< Constructor

  static WObject * (creator)(char *l);
  /**< Creates from fileline */

  virtual void render();
  /**< Renderer */

  virtual void quit();
  /**< Quits */

 private:
  virtual void parser(char *l);
  /**< Parses */

  virtual void defaults();
  /**< Sets defaults values */

  virtual void behavior();
  /**< Sets behavior */

  virtual void inits();
  /**< Do specific inits */

  virtual void heights(int it, int x, int y, float h, float f);
  /**< Compute heights */

  virtual void aux_heights(int x1, int y1, int x2, int y2, float f);
  /**< Compute aux heights */

  virtual void draw();
  /**< Draws the terrain */

  virtual void initNormales();
  /**< Inits normales */

  virtual void setColor(float z);
  /**< Sets color */

  virtual void prodvect(float x1, float y1, float z1, float x2, float y2, float z2, float *a, float *b, float *c);
  /**< Cross product */
};

#endif
