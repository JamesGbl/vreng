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
#ifndef DOOR_HPP
#define DOOR_HPP

#include "wobject.hpp"

#define DOOR_TYPE	3
#define DOOR_NAME	"Door"


/**
 * Door class
 */
class Door: public WObject {

private:
  float aopen;		///< open angle
  float aclose;		///< close angle
  float aspeed;		///< angular speed (radian)
  V3 center;		///< center position
  V3 size;		///< dimension

public:
  /* properties */
  enum {
    PROPHNAME,
    PROPXY,
    PROPZ,
    PROPAZ,
    PROPS
  };

  /* states */
  enum {
    NONE,
    OPENED,	///< opened
    CLOSED,	///< closed
    LOCKED,	///< locked
    UNLOCKED	///< unlocked
  };

  static const OClass oclass;	///< class variable

  virtual const OClass* getOClass() {return &oclass;}

  Door(char *l);	///< Constructor

  static void funcs();	///< init funclist

  static WObject * (creator)(char *l);
  /**< Create from fileline */

  virtual void changePosition(float lasting);
  /**< Makes changes on position */

  virtual void updateTime(time_t, time_t, float *lasting);
  /**< Updates time */

  virtual bool updateToNetwork(const Pos &oldpos);
  /**< Publishes position */

  virtual bool whenIntersect(WObject *pcur, WObject *pold);
  /**< When an collision occurs */

  virtual void quit();
  /**< Quits properly */

private:
  virtual void parser(char *l);
  /**< Parses file line */

  virtual void open();
  virtual void close();
  virtual void lock();
  virtual void unlock();

  // GUI callbacks
  static void open_cb(Door *o, void *d, time_t s, time_t u);
  static void close_cb(Door *o, void *d, time_t s, time_t u);
  static void lock_cb(Door *o, void *d, time_t s, time_t u);
  static void unlock_cb(Door *o, void *d, time_t s, time_t u);
};

#endif
