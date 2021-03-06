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
#ifndef CAULDRON_HPP
#define CAULDRON_HPP

#include "wobject.hpp"

#define CAULDRON_TYPE	13
#define CAULDRON_NAME	"Cauldron"


/**
 * Cauldron class
 */
class Cauldron: public WObject {

private:
  static const float DELTAZ;

public:
  static const OClass oclass;	///< class variable

  static void funcs();	///< init funclist

  virtual const OClass* getOClass() {return &oclass;} ///< virtual inst. method

  Cauldron(char *l);	///< Constructor

  static WObject * (creator)(char *l);
  /**< Create from fileline */

  virtual bool whenIntersect(WObject *pcur, WObject *pold);
  /**< When an other object intersects */

  virtual void changePermanent(float lasting);
  /**< Change permanent */

private:
  virtual void parser(char *l);
  /**< Parses */

  // Callbacks
  static void create_cb(Cauldron *o, void *d, time_t s, time_t u);
};

#endif
