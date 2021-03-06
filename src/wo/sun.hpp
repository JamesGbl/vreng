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
#ifndef SUN_HPP
#define SUN_HPP

#include "wobject.hpp"

#define SUN_TYPE	69
#define SUN_NAME	"Sun"

/**
 * Sun class
 */
class Sun: public WObject {

protected:
  static const GLfloat DEF_SCALE;
  static const GLfloat DEF_RADIUS;
  static const GLfloat light_pos[4];
  static const GLfloat light_amb[4];
  static const GLfloat black[4];

  GLfloat scale;
  GLfloat light_diff[4];
  GLfloat light_spec[4];
  GLfloat light_rot;		///< angle sun position
  GLfloat radius;			///< sun radius
  GLfloat ox, oy, oz;		///< original position

  class Light *light;		///< light pointer
  class Flare *flare;		///< flares

public:
  static const OClass oclass;	///< class variable

  virtual const OClass* getOClass() {return &oclass;}

  static void funcs();	///< init funclist

  Sun(char *l);	///< Constructor

  static WObject * (creator)(char *l);
  /**< Creates from file line. */

  virtual void changePermanent(float lasting);
  /**< Permanent movement. */

  virtual void lighting();
  /**< Renders light. */

  virtual void quit();
  /**< Quits. */

 private:
  virtual void parser(char *l);
  /**< Parses file line.*/

  virtual void defaults();
  /**< Sets defaults. */

  virtual void behavior();
  /**< Sets behaviors. */

  virtual void inits();
  /**< Inits specific */

  virtual void makeSolid();
  /**< Builds solid geometry. */

  virtual void render();
  /**< Draws. */
};

#endif
