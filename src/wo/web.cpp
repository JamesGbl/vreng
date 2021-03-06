//---------------------------------------------------------------------------
// VREng (Virtual Reality Engine)	http://vreng.enst.fr/
//
// Copyright (C) 1997-2011 Philippe Dax
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
#include "web.hpp"
#include "move.hpp"	// gotoFront
#include "browser.hpp"	// start
#include "user.hpp"	// USER_TYPE
#include "text.hpp"	// Text


const OClass Web::oclass(WEB_TYPE, "Web", Web::creator);
const float Web::TTL = 4.;       // 4 sec max
const float Web::ASPEED = M_PI;  // 180deg/sec
const uint16_t Web::MAXLEN = 128;// 128
const float Web::GLYPHSIZ = 0.05;// 5 cm

// local
static uint16_t oid = 0;


/* creation from a file */
WObject * Web::creator(char *l)
{
  return new Web(l);
}

void Web::defaults()
{
  state = 0;	// normal face
  aspeed = ASPEED;
  atemp = 0;
  text = NULL;
  legend = NULL;
}

void Web::parselegend(char *l)
{
  char buf[BUFSIZ];

  strcpy(buf, l);
  char *p = strstr(buf, "legend=");
  if (p) {
    p += 8;
    char *q = strchr(p, '"');
    if (q) *q = '\0';
    legend = new char[MAXLEN];
    strcpy(legend, p);
  }
}

void Web::parser(char *l)
{
  parselegend(l);
  defaults();
  l = tokenize(l);
  begin_while_parse(l) {
    l = parse()->parseAttributes(l, this);
    if (!l) break;
    if      (!stringcmp(l, "url")) l = parse()->parseUrl(l, names.url);
    else if (!stringcmp(l, "legend")) {
      l += 7; // skip legend=
      l = parse()->skipAttribute(l);
    }
  }
  end_while_parse(l);
}

Web::Web(char *l)
{
  parser(l);

  afront = pos.az;
  acurr = afront;
  aback = afront + M_PI;

  enableBehavior(PERSISTENT);
  setRenderPrior(RENDER_NORMAL);

  initializeMobileObject(TTL);
  createPermanentNetObject(PROPS, ++oid);
}

void Web::updateTime(time_t sec, time_t usec, float *lasting)
{
  updateLasting(sec, usec, lasting);
}

void Web::changePosition(float lasting)
{ 
  if (atemp < M_PI) {
    pos.az += lasting * move.aspeed.v[0];
    atemp += lasting * move.aspeed.v[0];
  }
  else {
    pos.az = acurr + M_PI;
    stopImposedMovement();
  }
  //error("az=%.2f", pos.az);
}

/* object intersects: projection */
bool Web::whenIntersect(WObject *pcur, WObject *pold)
{
  switch (pcur->type) {
  case USER_TYPE:
    projectPosition(pcur, pold);
    return true;
    break;
  default:
    return false;
    break;
  }
}

void Web::pivot()
{
  float nexta;

  acurr = pos.az;
  atemp = 0;
  switch (state) {
  case 0: nexta = aback;  break;
  case 1: nexta = afront; break;
  }
  pos.moved = false;
  clearV3(move.aspeed);
  move.aspeed.v[0] = aspeed;
  initImposedMovement(TTL);
  if (text) {	// get rid of previous text
    text->delFromList();
  }

  if (nexta == aback && legend) {
    WObject *pleg = new WObject();
    V3 dim;
    float fgcolor[4] = {0,1,0,1}; // green
    copyPositionAndBB(pleg);
    getDim(dim);	// get dim
    pleg->pos.z += (dim.v[2] - 0.15);	// 15cm under the top
    pleg->pos.ax = pos.ax;
    pleg->pos.az = afront;
    pos.az = afront;
    if (dim.v[0] > dim.v[1]) {
      pleg->pos.x += (dim.v[0] + 0.001) * sin(afront);	// 1mm near front face
      pleg->pos.y -= (dim.v[1] - 0.05) * cos(afront);	// 5cm from the left margin
    }
    else {
      pleg->pos.y += (dim.v[0] + 0.001) * sin(afront);	// 1mm near front face
      pleg->pos.x -= (dim.v[1] - 0.05) * cos(afront);	// 5cm from the left margin
    }
    error("legend: %.2f [%.3f %.3f %.3f] web: %.2f [%.2f %.2f %.2f %.2f - %.2f %.2f %.2f]", strlen(legend)*GLYPHSIZ, pleg->pos.x, pleg->pos.y, pleg->pos.z, dim.v[0]*2, pos.x, pos.y, pos.z, afront, dim.v[0], dim.v[1], dim.v[2]);
    text = new Text(legend, pleg->pos, 0.25, fgcolor);
    text->setShifts(pleg->pos.x, pleg->pos.y, pleg->pos.z, pleg->pos.az + M_PI, pleg->pos.ax + M_PI_2);
    delete pleg;
  }
  state ^= 1;
  pos.moved = true;     // has moved
}

/* Opens browser */
void Web::open_cb(Web *web, void *d, time_t s, time_t u)
{
  Browser::start(web->names.url);
#if 0 //obsoleted
  if (!stringcmp(purl, "wrl") || !stringcmp(purl, "vrm")) {
    Browser::startvrml(web->names.url);
    return;
  }
#endif
}

/* Pivot */
void Web::pivot_cb(Web *web, void *d, time_t s, time_t u)
{
  web->pivot();
}

void Web::quit()
{
  oid = 0;
  flushMySqlPosition();
  if (text) delete text;
  if (legend) delete[] legend;
}

void Web::funcs()
{
  getPropertyFunc(WEB_TYPE, PROPXY, WO_PAYLOAD get_xy);
  getPropertyFunc(WEB_TYPE, PROPZ, WO_PAYLOAD get_z);
  getPropertyFunc(WEB_TYPE, PROPAZ, WO_PAYLOAD get_az);
  getPropertyFunc(WEB_TYPE, PROPAX, WO_PAYLOAD get_ax);
  getPropertyFunc(WEB_TYPE, PROPAY, WO_PAYLOAD get_ay);
  getPropertyFunc(WEB_TYPE, PROPHNAME, WO_PAYLOAD get_hname);

  putPropertyFunc(WEB_TYPE, PROPXY, WO_PAYLOAD put_xy);
  putPropertyFunc(WEB_TYPE, PROPZ, WO_PAYLOAD put_z);
  putPropertyFunc(WEB_TYPE, PROPAZ, WO_PAYLOAD put_az);
  putPropertyFunc(WEB_TYPE, PROPAX, WO_PAYLOAD put_ax);
  putPropertyFunc(WEB_TYPE, PROPAY, WO_PAYLOAD put_ay);
  putPropertyFunc(WEB_TYPE, PROPHNAME, WO_PAYLOAD put_hname);

  setActionFunc(WEB_TYPE, 0, WO_ACTION open_cb, "Open");
  setActionFunc(WEB_TYPE, 1, WO_ACTION pivot_cb, "Pivot");
  setActionFunc(WEB_TYPE, 2, WO_ACTION gotoFront, "Approach");
  setActionFunc(WEB_TYPE, 3, WO_ACTION moveObject, "Move");
}
