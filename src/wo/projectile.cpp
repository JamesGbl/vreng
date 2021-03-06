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
#include "vreng.hpp"
#include "projectile.hpp"
#include "user.hpp"	// USER_TYPE
#include "netobj.hpp"	// NetObject


void Projectile::updateTime(time_t s, time_t us, float *plasting)
{
  if (! updateLasting(s, us, plasting)) {
    /* the projectile has spent its time to live => destroyed */
#if 0 //FIXME segfault
    toDelete();	// delete Wobject
#endif
  }
}

void Projectile::changePosition(float lasting)
{
  pos.x += lasting * move.lspeed.v[0];
  pos.y += lasting * move.lspeed.v[1];
  pos.z += lasting * move.lspeed.v[2];
}

/* Updates to the network */
bool Projectile::updateToNetwork(const Pos &oldpos)
{
  bool change = false;

  if ((pos.x != oldpos.x) || (pos.y != oldpos.y)) {
    noh->declareObjDelta(PROPXY);
    change = true;
  }
  return change;
}

bool Projectile::whenIntersect(WObject *pcur, WObject *pold)
{
  switch (pcur->type) {
  case USER_TYPE:
    /* projectile intersects an user: hit */
    notice("%s hited by %s", pcur->getInstance(), getInstance());
    pold->copyPositionAndBB(pcur);
    break;
  default:
    pold->copyPositionAndBB(pcur);
  }
#if 0 
  toDelete();	// delete Wobject
#endif
  return true;
}

void Projectile::whenWallsIntersect(WObject *pold, V3 *normal)
{
  enableBehavior(COLLIDE_ONCE);
  bounceTrajectory(pold, normal);
}

void Projectile::funcs()
{}
