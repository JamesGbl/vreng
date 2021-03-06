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
/*
 * Authors: Fabrice Bellard, Philippe Dax
 */
#include "vreng.hpp"
#include "solid.hpp"
#include "draw.hpp"	// STYLE
#include "render.hpp"	// sharedRender
#include "texture.hpp"	// getFromCache
#include "wobject.hpp"	// WObject
#include "netobj.hpp"	// declareObjDelta
#include "color.hpp"	// Color
#include "user.hpp"	// localuser
#include "md2.hpp"	// Md2
#include "obj.hpp"	// Obj
#include "man.hpp"	// draw
#include "car.hpp"	// draw
#include "teapot.hpp"	// draw
#include "format.hpp"	// getModelByUrl
#include "parse.hpp"	// printNumline
#include "prof.hpp"	// new_solid
#include "pref.hpp"	// ::g.pref
#include "scene.hpp"	// getScene


#define DEF_ALPHA		1.
#define DEF_FOG			0
#define DEF_SCALE		1.
#define DEF_SHININESS		20
#define DEF_SPHERE_SLICES	16
#define DEF_SPHERE_STACKS	16
#define DEF_CONE_SLICES		16
#define DEF_CONE_STACKS		8
#define DEF_TORUS_CYLINDERS	16
#define DEF_TORUS_CIRCLES	16
#define DEF_DISK_SLICES		16
#define DEF_WHEEL_SPOKES	12
#define DEF_DISK_LOOPS		8
#define FRAME_MAX		256

/* Solid tokens. */
enum {
  STOK_ERR = 0,
  /* shapes */
  STOK_SHAPE,
  STOK_BOX,
  STOK_MAN,
  STOK_GUY,
  STOK_ANDROID,
  STOK_CAR,
  STOK_SPHERE,
  STOK_CONE,
  STOK_TORUS,
  STOK_RECT,
  STOK_DISK,
  STOK_LINE,
  STOK_PYRAMID,
  STOK_CIRCLE,
  STOK_TRIANGLE,
  STOK_ELLIPSE,
  STOK_POINT,
  STOK_STATUE,
  STOK_BBOX,
  STOK_BSPHERE,
  STOK_CROSS,
  STOK_SPHERE_TORUS,
  STOK_SPHERE_DISK,
  STOK_CONE_DISK,
  STOK_WHEEL,
  STOK_HELIX,
  STOK_TEAPOT,
  /* dimensions */
  STOK_URL,
  STOK_SIZE,
  STOK_RADIUS,
  STOK_RADIUS2,
  STOK_RADIUS3,
  STOK_PTSIZE,
  STOK_WIDTH,
  STOK_DEPTH,
  STOK_HEIGHT,
  STOK_LENGTH,
  STOK_THICK,
  STOK_SIDE,
  /* position */
  STOK_REL,
  /* textures */
  STOK_TEXTURE,
  STOK_TEX_XP,
  STOK_TEX_XN,
  STOK_TEX_YP,
  STOK_TEX_YN,
  STOK_TEX_ZP,
  STOK_TEX_ZN,
  /* textures Repeat */
  STOK_TEXTURE_R,
  STOK_TEX_XP_R,
  STOK_TEX_XN_R,
  STOK_TEX_YP_R,
  STOK_TEX_YN_R,
  STOK_TEX_ZP_R,
  STOK_TEX_ZN_R,
  STOK_TEXTURE_RS,
  STOK_TEX_XP_RS,
  STOK_TEX_XN_RS,
  STOK_TEX_YP_RS,
  STOK_TEX_YN_RS,
  STOK_TEX_ZP_RS,
  STOK_TEX_ZN_RS,
  STOK_TEXTURE_RT,
  STOK_TEX_XP_RT,
  STOK_TEX_XN_RT,
  STOK_TEX_YP_RT,
  STOK_TEX_YN_RT,
  STOK_TEX_ZP_RT,
  STOK_TEX_ZN_RT,
  /* materials */
  STOK_DIFFUSE,
  STOK_AMBIENT,
  STOK_SPECULAR,
  STOK_EMISSION,
  STOK_SHININESS,
  STOK_ALPHA,
  STOK_FOG,
  /* drawing */
  STOK_STYLE,
  STOK_FACE,
  STOK_SLICES,
  STOK_STACKS,
  STOK_CYLINDERS,
  STOK_CIRCLES,
  STOK_SPOKES,
  STOK_BLINK,
  /* frames */
  STOK_FRAMES,
  STOK_BEGINFRAME,
  STOK_ENDFRAME,
  STOK_MODEL,
  STOK_SCALE,
  STOK_SCALEX,
  STOK_SCALEY,
  STOK_SCALEZ,
  STOK_SOLID,
  /* lightings */
  STOK_SPOT_DIRECTION,
  STOK_SPOT_CUTOFF,
  STOK_CONSTANT_ATTENUAT,
  STOK_LINEAR_ATTENUAT,
  STOK_QUADRATIC_ATTENUAT
};

// local
struct sStokens {
  const char *tokstr;
  const char *tokalias;
  int tokid;
};

static const struct sStokens stokens[] = {
  { "shape", "", STOK_SHAPE },
  { "box", "", STOK_BOX },
  { "man", "", STOK_MAN},
  { "guy", "", STOK_GUY},
  { "android", "", STOK_ANDROID},
  { "car","", STOK_CAR},
  { "sphere", "", STOK_SPHERE },
  { "cone", "cylinder", STOK_CONE },
  { "torus", "", STOK_TORUS },
  { "rect", "", STOK_RECT },
  { "disk", "", STOK_DISK },
  { "line", "", STOK_LINE },
  { "pyramid", "", STOK_PYRAMID },
  { "triangle", "", STOK_TRIANGLE },
  { "circle", "", STOK_CIRCLE },
  { "ellipse", "", STOK_ELLIPSE },
  { "pt", "point", STOK_POINT },
  { "statue", "", STOK_STATUE },
  { "bb", "bbox", STOK_BBOX },
  { "bs", "bsphere", STOK_BSPHERE },
  { "cross", "", STOK_CROSS },
  { "sphere+torus", "dsphere", STOK_SPHERE_TORUS },
  { "sphere+disk", "saucer", STOK_SPHERE_DISK },
  { "cone+disk", "hat", STOK_CONE_DISK },
  { "wheel", "", STOK_WHEEL },
  { "helix","", STOK_HELIX},
  { "teapot","", STOK_TEAPOT},
  { "url", "solid", STOK_URL },
  { "dim", "size", STOK_SIZE },
  { "r", "radius", STOK_RADIUS },
  { "rb", "ri", STOK_RADIUS },
  { "radius2", "rc", STOK_RADIUS2 },
  { "rt", "re", STOK_RADIUS2 },
  { "radius3", "", STOK_RADIUS3 },
  { "ptsize", "pointsize", STOK_PTSIZE },
  { "h", "height", STOK_HEIGHT },
  { "l", "length", STOK_LENGTH },
  { "w", "width", STOK_WIDTH },
  { "d", "depth", STOK_DEPTH },
  { "t", "thick", STOK_THICK },
  { "s", "side", STOK_SIDE },
  { "rel", "pos", STOK_REL },
  { "tx", "texture", STOK_TEXTURE },
  { "xp", "tx_right", STOK_TEX_XP },
  { "xn", "tx_front", STOK_TEX_XN },
  { "yp", "tx_left", STOK_TEX_YP },
  { "yn", "tx_back", STOK_TEX_YN },
  { "zp", "tx_top", STOK_TEX_ZP },
  { "zn", "tx_bottom", STOK_TEX_ZN },
  { "txr", "texture_r", STOK_TEXTURE_R },
  { "xpr", "tex_xpr", STOK_TEX_XP_R },
  { "xnr", "tex_xnr", STOK_TEX_XN_R },
  { "ypr", "tex_ypr", STOK_TEX_YP_R },
  { "ynr", "tex_ynr", STOK_TEX_YN_R },
  { "zpr", "tex_zpr", STOK_TEX_ZP_R },
  { "znr", "tex_znr", STOK_TEX_ZN_R },
  { "txrs", "texture_rs", STOK_TEXTURE_RS },
  { "xprs", "tex_xprs", STOK_TEX_XP_RS },
  { "xnrs", "tex_xnrs", STOK_TEX_XN_RS },
  { "yprs", "tex_yprs", STOK_TEX_YP_RS },
  { "ynrs", "tex_ynrs", STOK_TEX_YN_RS },
  { "zprs", "tex_zprs", STOK_TEX_ZP_RS },
  { "znrs", "tex_znrs", STOK_TEX_ZN_RS },
  { "txrt", "texture_rt", STOK_TEXTURE_RT },
  { "xprt", "tex_xprt", STOK_TEX_XP_RT },
  { "xnrt", "tex_xnrt", STOK_TEX_XN_RT },
  { "yprt", "tex_yprt", STOK_TEX_YP_RT },
  { "ynrt", "tex_ynrt", STOK_TEX_YN_RT },
  { "zprt", "tex_zprt", STOK_TEX_ZP_RT },
  { "znrt", "tex_znrt", STOK_TEX_ZN_RT },
  { "dif", "diffuse", STOK_DIFFUSE },
  { "amb", "ambient", STOK_AMBIENT },
  { "spe", "specular", STOK_SPECULAR },
  { "emi", "emission", STOK_EMISSION },
  { "shi", "shininess", STOK_SHININESS },
  { "a", "alpha", STOK_ALPHA },
  { "fog", "", STOK_FOG },
  { "st", "style", STOK_STYLE },
  { "fa", "face", STOK_FACE },
  { "sl", "slices", STOK_SLICES },
  { "sk", "stacks", STOK_STACKS },
  { "cy", "cylinders", STOK_CYLINDERS },
  { "ci", "circles", STOK_CIRCLES },
  { "sp", "spokes", STOK_SPOKES },
  { "bl", "blink", STOK_BLINK },
  { "nf", "frames", STOK_FRAMES },
  { "bf", "beginframe", STOK_BEGINFRAME },
  { "ef", "endframe", STOK_ENDFRAME },
  { "solid", "", STOK_SOLID },
  { "m", "model", STOK_MODEL },
  { "sc", "scale", STOK_SCALE },
  { "sx", "scalex", STOK_SCALEX },
  { "sy", "scaley", STOK_SCALEY },
  { "sz", "scalez", STOK_SCALEZ },
  { "spotd", "spot_direction", STOK_SPOT_DIRECTION },
  { "spotc", "spot_cutoff", STOK_SPOT_CUTOFF },
  { "ca", "constant_attenuation", STOK_CONSTANT_ATTENUAT },
  { "la", "linear_attenuation", STOK_LINEAR_ATTENUAT },
  { "qa", "quadratic_attenuation", STOK_QUADRATIC_ATTENUAT },
  { NULL, NULL, 0 }
};


/* New Solid. */
Solid::Solid()
{
  new_solid++;
  dlists = NULL;	// solid display list
  wobject = NULL;
  shape = STOK_BOX;	// box shape by default
  numrel = 0;
  rel_bbcent = newV3(0, 0, 0);
  rel_bbsize = newV3(0, 0, 0);
  abs_bbcent = newV3(0, 0, 0);
  abs_bbsize = newV3(0, 0, 0);
  frame = 0;		// frame index in displaylist
  curframe = 0;		// frame to render
  nbframes = 1;		// 1 frame by default
  framed = false;	// mono framed by default
  is_visible = true;	// visible by default
  is_opaque = true;	// opaque by default
  isflashy = false;
  isflashable = false;
  isreflexive = false;
  isblinking = false;
  isflary = false;
  blink = false;
  ray_dlist = 0;
  for (int i=0; i<5; i++) rel[i] = 0;
  for (int i=0; i<3; i++) flashcolor[i] = 1;  // white
}

/* Deletes solid from display-list. */
Solid::~Solid()
{
  ::g.render.removeSolidFromList(this);

  delete[] dlists;
  del_solid++;
}

char * Solid::skipEqual(char *p)
{
  if (p && (p = strchr(p, '='))) p++;
  return p;
}

char * Solid::getTok(char *l, uint16_t *tok)
{
  char *t = l;
  const struct sStokens *ptab;

  *tok = STOK_ERR;
  //error("l=%s",l);
  l = skipEqual(l);
  if (l) {
    *(l-1) = '\0';	// end of token '=',  replaced by null terminated
    for (ptab = stokens; ptab->tokstr ; ptab++) {
      if ((!strcmp(ptab->tokstr, t)) || (!strcmp(ptab->tokalias, t))) {
        *tok = ptab->tokid;
        return l;
      }
    }
    error("getTok: unknown \"%s\" in %s", t, l);
    return l;
  }
  else { error("getTok: in %s", t); return t; }
}

char * Solid::getFramesNumber(char *l)
{
  if (!stringcmp(l, "frames=")) l = wobject->parse()->parseUInt16(l, &nbframes, "frames");
  return l;
}

/* Parses <frame , return next token after frame. */
char * Solid::parseFrame(char *l)
{
  if (!strcmp(l, "frame")) {
    framed = true;
    char *p = wobject->parse()->nextToken();
    return p;
  }
  while (l && framed) {
    if (!stringcmp(l, "frame")) return wobject->parse()->nextToken();
    l = wobject->parse()->nextToken();
  }
  return l;
}

/* Sets shape class member from shape="...", return next token. */
char * Solid::parseShape(char *l)
{
  const struct sStokens *ptab;
  char s[16];

  if (!stringcmp(l, "shape=")) {
    l = wobject->parse()->parseString(l, s, "shape");
    for (ptab = stokens; ptab->tokstr ; ptab++) {
      if ((!strcmp(ptab->tokstr, s)) || (!strcmp(ptab->tokalias, s))) {
        shape = ptab->tokid;
        return l;
      }
    }
    error("unknown shape \"%s\" in %s'", s, l);
    shape = 0;
  }
  return l;
}

/* solid parser. */
char * Solid::parser(char *l)
{
  if (!l) {
    error("no solid content");
    wobject->parse()->printNumline();
    return NULL;
  }
  char ll[BUFSIZ];
  strcpy(ll, l);
  if (*l == '<') l++;	// skip open-tag

  l = getFramesNumber(l);

  dlists = new GLint[nbframes];

  ::g.render.addSolidInList(this);
  IdM4(&position);

  if (wobject->getInstance() && wobject->haveAction()) setFlashable(true);

  // axis aligned bounding boxes (AABB) are here
  V3 bbmax = newV3(0, 0, 0);
  V3 bbmin = newV3(0, 0, 0);

  // for each frame
  for (frame = 0; frame < nbframes; ) {
    int r = 0;

    l = parseFrame(l);
    l = parseShape(l);
    switch (shape) {
      case STOK_BBOX:
      case STOK_BOX:
      case STOK_SPHERE:
      case STOK_CONE:
      case STOK_TORUS:
      case STOK_RECT:
      case STOK_DISK:
      case STOK_LINE:
      case STOK_POINT:
      case STOK_PYRAMID:
      case STOK_TRIANGLE:
      case STOK_BSPHERE:
      case STOK_CIRCLE:
      case STOK_ELLIPSE:
      case STOK_SPHERE_TORUS:
      case STOK_CROSS:
      case STOK_SPHERE_DISK:
      case STOK_CONE_DISK:
      case STOK_WHEEL:
      case STOK_HELIX:
      case STOK_TEAPOT:
      case STOK_MAN:
      case STOK_GUY:
      case STOK_ANDROID:
      case STOK_CAR:
        r = solidParser(l, bbmax, bbmin); break;
      case STOK_STATUE:
      case STOK_MODEL:
        r = statueParser(l, bbmax, bbmin); break;
      default:
        delete[] dlists;
        dlists = NULL;
        return NULL;
    }

    if (r == -1) { error("parser error: shape=%hu ll=%s", shape, ll); delete this; return NULL; }
    frame += r;
  }

  /* computes relative AABB of this solid: bbcent and bbsize */
  for (int i=0; i<3; i++) {
    rel_bbcent.v[i] = (bbmax.v[i] + bbmin.v[i]) / 2;
    rel_bbsize.v[i] = (bbmax.v[i] - bbmin.v[i]) / 2;
  }

  /* next Token */
  l = wobject->parse()->nextToken();
  if (l && !strcmp(l, "/solid")) l = wobject->parse()->nextToken(); // skip </solid>
  return l;
}

/* Solid Parser. */
int Solid::solidParser(char *l, V3 &bbmax, V3 &bbmin)
{
  if (!l) { error("no solid description"); return -1; }

  // default dimensions
  GLfloat radius = 0, radius2 = 0, radius3 = 0;
  GLfloat length = 0, width = 0, height = 0, thick = 0, side = 0;

  // default materials
  for (int i=0; i<4; i++) {
    mat_diffuse[i] = mat_ambient[i] = mat_specular[i] = 1;
    mat_emission[i] = 0;
  }
  mat_shininess[0] = DEF_SHININESS;
  mat_alpha = DEF_ALPHA;	// opaque

  // default lights params
  GLfloat light_spot_direction[] = {1,1,1,1};
  GLfloat light_spot_cutoff[] = {180};
  GLfloat light_constant_attenuation[] = {1};
  GLfloat light_linear_attenuation[] = {0};
  GLfloat light_quadratic_attenuation[] = {0};
  GLfloat fog[] = {DEF_FOG,1,1,1};	// density + white

  // default draws params
  scale = scalex = scaley = scalez = DEF_SCALE;
  uint8_t style = Draw::STYLE_FILL;	// default style
  uint8_t slices = DEF_SPHERE_SLICES;
  uint8_t stacks = DEF_SPHERE_STACKS;
  uint8_t cylinders = DEF_TORUS_CYLINDERS;
  uint8_t circles = DEF_TORUS_CIRCLES;
  uint8_t spokes = DEF_WHEEL_SPOKES;
  uint8_t face = 0;	// default face

  // default textures
  int texid = -1;	// for quadrics (sphere, cylinder, disc, torus, ...)
  int box_tex[6] = {-1,-1,-1,-1,-1,-1};	// for parallepipedic shapes
  GLfloat box_texrep[6][2] = { {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1} };
  GLfloat tex_r_s = 1, tex_r_t = 1;

  Teapot *teapot = NULL;

  V3 dim = newV3(.1, .1, .1);	// default dimension : box 10x10x10 cm

  ::g.render.first_bbox = true;

  switch (shape) {
    case STOK_SPHERE:
      slices    = DEF_SPHERE_SLICES;
      stacks    = DEF_SPHERE_STACKS;
      break;
    case STOK_CONE:
      slices    = DEF_CONE_SLICES;
      stacks    = DEF_CONE_STACKS;
      break;
    case STOK_TORUS:
      cylinders = DEF_TORUS_CYLINDERS;
      circles   = DEF_TORUS_CIRCLES;
      break;
    case STOK_DISK:
    case STOK_SPHERE_DISK:
    case STOK_CONE_DISK:
      slices    = DEF_DISK_SLICES;
      stacks    = DEF_DISK_LOOPS;
      break;
    case STOK_SPHERE_TORUS:
      slices    = DEF_SPHERE_SLICES;
      stacks    = DEF_SPHERE_STACKS;
      cylinders = DEF_TORUS_CYLINDERS;
      circles   = DEF_TORUS_CIRCLES;
    case STOK_WHEEL:
      spokes    = DEF_WHEEL_SPOKES;
      break;
  }

  // parse after shape
  while (l) {
    uint16_t tok = 0; uint8_t flgblk = 0;

    if ((*l == '\0') || (*l == '/')) { *l = '\0'; break; } // end of solid

    l = getTok(l, &tok);
    switch (tok) {
      case STOK_SOLID:	//not used
        error("token solid"); break;
      case STOK_URL:
        break; //TODO
      case STOK_SIZE:
        l = wobject->parse()->parseVector3fv(l, &dim); break;
      case STOK_DIFFUSE:
        l = wobject->parse()->parseVector3f(l, &mat_diffuse[0]);
        for (int i=0; i<3; i++) mat_ambient[i] = mat_diffuse[i];
        break;
      case STOK_AMBIENT:
        l = wobject->parse()->parseVector3f(l, &mat_ambient[0]); break;
      case STOK_SPECULAR:
        l = wobject->parse()->parseVector3f(l, &mat_specular[0]); break;
      case STOK_EMISSION:
        l = wobject->parse()->parseVector3f(l, &mat_emission[0]);
        for (int i=0; i<3; i++) mat_ambient[i] = mat_emission[i];
        break;
      case STOK_SHININESS:
        l = wobject->parse()->parseInt(l, &mat_shininess[0]); break;
      case STOK_ALPHA:
        l = wobject->parse()->parseFloat(l, &mat_alpha);
        mat_diffuse[3] = mat_ambient[3] = mat_alpha; break;
      case STOK_SCALE:
        l = wobject->parse()->parseFloat(l, &scale); break;
      case STOK_SCALEX:
        l = wobject->parse()->parseFloat(l, &scalex); break;
      case STOK_SCALEY:
        l = wobject->parse()->parseFloat(l, &scaley); break;
      case STOK_SCALEZ:
        l = wobject->parse()->parseFloat(l, &scalez); break;
      case STOK_RADIUS3:
        l = wobject->parse()->parseFloat(l, &radius3); break;
      case STOK_RADIUS2:
        l = wobject->parse()->parseFloat(l, &radius2); break;
      case STOK_RADIUS:
        l = wobject->parse()->parseFloat(l, &radius); break;
      case STOK_HEIGHT:
        l = wobject->parse()->parseFloat(l, &height); break;
      case STOK_LENGTH:
        l = wobject->parse()->parseFloat(l, &length); break;
      case STOK_WIDTH:
        l = wobject->parse()->parseFloat(l, &width); break;
      case STOK_THICK:
        l = wobject->parse()->parseFloat(l, &thick); break;
      case STOK_SIDE:
        l = wobject->parse()->parseFloat(l, &side); break;
      case STOK_PTSIZE:
        l = wobject->parse()->parseFloat(l, &radius); break;
      case STOK_FOG:
        l = wobject->parse()->parseFloat(l, &fog[0]);
        for (int i=0; i<3; i++) fog[i+1] = mat_diffuse[i]; break;
      case STOK_STYLE:
        l = wobject->parse()->parseUInt8(l, &style); break;
      case STOK_FACE:
        l = wobject->parse()->parseUInt8(l, &face); break;
      case STOK_SLICES:
        l = wobject->parse()->parseUInt8(l, &slices); break;
      case STOK_STACKS:
        l = wobject->parse()->parseUInt8(l, &stacks); break;
      case STOK_CYLINDERS:
        l = wobject->parse()->parseUInt8(l, &cylinders); break;
      case STOK_CIRCLES:
        l = wobject->parse()->parseUInt8(l, &circles); break;
      case STOK_SPOKES:
        l = wobject->parse()->parseUInt8(l, &spokes); break;
      case STOK_SPOT_CUTOFF:
        l = wobject->parse()->parseFloat(l, &light_spot_cutoff[0]); break;
      case STOK_SPOT_DIRECTION:
        l = wobject->parse()->parseVector3f(l, &light_spot_direction[0]); break;
      case STOK_CONSTANT_ATTENUAT:
        l = wobject->parse()->parseFloat(l, &light_constant_attenuation[0]); break;
      case STOK_LINEAR_ATTENUAT:
        l = wobject->parse()->parseFloat(l, &light_linear_attenuation[0]); break;
      case STOK_QUADRATIC_ATTENUAT:
        l = wobject->parse()->parseFloat(l, &light_quadratic_attenuation[0]); break;
      case STOK_BLINK:
        l = wobject->parse()->parseUInt8(l, &flgblk);
        if (flgblk) { blink = true; setBlinking(true); } break;
      case STOK_REL:
        l = wobject->parse()->parseVector5f(l, rel); ++numrel; break;
      case STOK_TEXTURE:
        { char *url = new char[URL_LEN];
          l = wobject->parse()->parseString(l, url);
#if 0
          if (*url) texid = Texture::getFromCache(url);
#else
          if (*url) {
            texture = new Texture(url);
            texid = texture->id;
            texture->object = wobject;
            texture->solid = this;
          }
#endif
          delete[] url;
        }
        break;
      case STOK_TEX_XP:
      case STOK_TEX_XN:
      case STOK_TEX_YP:
      case STOK_TEX_YN:
      case STOK_TEX_ZP:
      case STOK_TEX_ZN:
        { char *url = new char[URL_LEN];
          l = wobject->parse()->parseString(l, url);
#if 0
          if (*url) box_tex[tok-STOK_TEX_XP] = Texture::getFromCache(url);
#else
          if (*url) {
            texture = new Texture(url);
            box_tex[tok-STOK_TEX_XP] = texture->id;
            texture->object = wobject;
            texture->solid = this;
          }
#endif
          delete[] url;
        }
        break;
      case STOK_TEXTURE_R:
        l = wobject->parse()->parseFloat(l, &tex_r_s); tex_r_t = tex_r_s; break;
      case STOK_TEXTURE_RS:
        l = wobject->parse()->parseFloat(l, &tex_r_s); break;
      case STOK_TEXTURE_RT:
        l = wobject->parse()->parseFloat(l, &tex_r_t); break;
      case STOK_TEX_XP_R:
      case STOK_TEX_XN_R:
      case STOK_TEX_YP_R:
      case STOK_TEX_YN_R:
      case STOK_TEX_ZP_R:
      case STOK_TEX_ZN_R:
        l = wobject->parse()->parseFloat(l, &box_texrep[tok-STOK_TEX_XP_R][0]);
        box_texrep[tok-STOK_TEX_XP_R][1] = box_texrep[tok-STOK_TEX_XP_R][0];
        break;
      case STOK_TEX_XP_RS:
      case STOK_TEX_XN_RS:
      case STOK_TEX_YP_RS:
      case STOK_TEX_YN_RS:
      case STOK_TEX_ZP_RS:
      case STOK_TEX_ZN_RS:
        l = wobject->parse()->parseFloat(l, &box_texrep[tok-STOK_TEX_XP_RS][0]); break;
      case STOK_TEX_XP_RT:
      case STOK_TEX_XN_RT:
      case STOK_TEX_YP_RT:
      case STOK_TEX_YN_RT:
      case STOK_TEX_ZP_RT:
      case STOK_TEX_ZN_RT:
        l = wobject->parse()->parseFloat(l, &box_texrep[tok-STOK_TEX_XP_RT][1]); break;

      default: error("solidParser: bad token=%hu", tok); return -1;
    }
  }

  /**
   * draw solids
   */

  /* display list generation */
  int dlist = glGenLists(1);
  glNewList(dlist, GL_COMPILE);

  glCullFace(GL_BACK);
  glShadeModel(GL_SMOOTH);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glMaterialiv(GL_FRONT, GL_SHININESS, mat_shininess);

  switch (shape) {

    case STOK_BBOX:	// invisible box
      setBB(dim.v[0], dim.v[1], dim.v[2]);
      if (::g.pref.bbox) Draw::bbox(dim.v[0], dim.v[1], dim.v[2]);
      break;

    case STOK_BSPHERE:	// invisible sphere
      if (! radius) radius = (dim.v[0] + dim.v[1] + dim.v[2]) / 3;
      dim.v[0] = dim.v[1] = dim.v[2] = 2*radius;
      setBB(2*radius, 2*radius, 2*radius);
      if (::g.pref.bbox) Draw::bbox(2*radius, 2*radius, 2*radius);
      break;

    case STOK_BOX:
      preDraw(0, mat_alpha, fog);
      Draw::box(dim.v[0], dim.v[1], dim.v[2], box_tex, box_texrep, style);
      if (::g.pref.bbox) Draw::bbox(dim.v[0], dim.v[1], dim.v[2]);
      postDraw(0, mat_alpha, fog);
      break;

    case STOK_MAN:
      if (localuser->man) localuser->man->draw();
      else {
        Man *man = new Man(dim.v[0], dim.v[1], dim.v[2]);
        man->draw();
      }
      setBB(dim.v[0]/2, dim.v[1]/2, dim.v[2]/2);
      if (::g.pref.bbox) Draw::bbox(dim.v[0], dim.v[1], dim.v[2]);
      break;

    case STOK_GUY:
    case STOK_ANDROID:
      setBB(dim.v[0]/2, dim.v[1]/2, dim.v[2]/2);
      if (::g.pref.bbox) Draw::bbox(dim.v[0], dim.v[1], dim.v[2]);
      break;

    case STOK_SPHERE:
      preDraw(texid, mat_alpha, fog, true);
      Draw::sphere(radius, slices, stacks, style);
      setBB(radius * M_SQRT2, radius * M_SQRT2, radius * M_SQRT2);
      if (::g.pref.bbox) Draw::bbox(radius * M_SQRT2, radius * M_SQRT2, radius * M_SQRT2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_CONE:
      if (radius == radius2) stacks = 1; // cylinder
      preDraw(texid, mat_alpha, fog, true);
      if (thick) {	// double surface
        Draw::cylinder(radius - thick/2, radius2 - thick/2, height, slices, stacks, style);
        glEnable(GL_CULL_FACE);
        Draw::cylinder(radius + thick/2, radius2 + thick/2, height, slices, stacks, style);
      }
      else {		// single surface
        Draw::cylinder(radius, radius2, height, slices, stacks, style);
      }
      //setBB(radius, radius, height);
      if (::g.pref.bbox) Draw::bbox(radius, radius, height);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_TORUS:
      preDraw(texid, mat_alpha, fog);
      Draw::torus(radius2, cylinders, radius, circles, style);
      if (::g.pref.bbox) Draw::bbox(radius * M_SQRT2, radius * M_SQRT2, radius2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_DISK:
      preDraw(texid, mat_alpha, fog, true);
      Draw::disk(radius, radius2, slices, stacks, style);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_PYRAMID:
      preDraw(texid, mat_alpha, fog, true);
      Draw::pyramid(side, height, style);
      if (::g.pref.bbox) Draw::bbox(side, side, height/2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_SPHERE_TORUS:
      preDraw(texid, mat_alpha, fog);
      Draw::sphere(radius, slices, stacks, style);
      Draw::torus(0.05, cylinders, radius2, circles, style);
      setBB(radius2 * M_SQRT1_2/2, radius2 * M_SQRT1_2/2, radius * M_SQRT1_2/2);
      if (::g.pref.bbox) Draw::bbox(radius2 * M_SQRT2, radius2 * M_SQRT2, radius * M_SQRT2/2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_SPHERE_DISK:
      preDraw(texid, mat_alpha, fog);
      Draw::sphere(radius, slices, stacks, style);
      Draw::disk(radius, radius2, slices, stacks, style);
      setBB(radius2 * M_SQRT1_2, radius2 * M_SQRT1_2, radius * M_SQRT1_2);
      if (::g.pref.bbox) Draw::bbox(radius * M_SQRT2, radius * M_SQRT2, radius * M_SQRT2/2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_CONE_DISK:
      if (radius == radius3) stacks = 1; // cylinder
      preDraw(texid, mat_alpha, fog);
      Draw::cylinder(radius, radius3, height, slices, stacks, style);
      Draw::disk(radius, radius2, slices, stacks, style);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_CROSS:
      preDraw(0, mat_alpha, fog);
      Draw::box(dim.v[0], dim.v[1], dim.v[2], box_tex, box_texrep, style);
      Draw::box(dim.v[2], dim.v[1], dim.v[0], box_tex, box_texrep, style);
      postDraw(0, mat_alpha, fog);
      break;

    case STOK_RECT:
      preDraw(texid, mat_alpha, fog, face);
      Draw::rect(dim.v[0], dim.v[1], style, tex_r_s, tex_r_t);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_LINE:
      preDraw(texid, mat_alpha, fog, true);
      Draw::line(length, thick);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_CIRCLE:
      preDraw(texid, mat_alpha, fog, true);
      Draw::ellipse(radius, radius, style);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_TRIANGLE:
      break;

    case STOK_ELLIPSE:
      preDraw(texid, mat_alpha, fog, true);
      Draw::ellipse(radius, radius2, style);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_POINT:
      glPointSize((radius) ? radius : 1);
      Draw::point(dim.v[0], dim.v[1], dim.v[2]);
      glPointSize(1);
      break;

    case STOK_HELIX:
      preDraw(texid, mat_alpha, fog, true);
      Draw::helix(radius, length, height, slices, thick, mat_diffuse);
      setBB(radius, radius, length/2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_CAR:
      preDraw(texid, mat_alpha, fog, true);
      Car::draw(dim.v[0], dim.v[1], dim.v[2], box_tex, box_texrep, slices, style);
      setBB(dim.v[0], dim.v[1], dim.v[2] / 2);
      if (::g.pref.bbox) Draw::bbox(dim.v[0], dim.v[1], dim.v[2]/2);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_TEAPOT:
      preDraw(texid, mat_alpha, fog, true);
      teapot = new Teapot();
      teapot->draw(dim.v[0], dim.v[1], dim.v[2], box_tex, box_texrep, slices, style);
      setBB(dim.v[0], dim.v[1], dim.v[2]);
      if (::g.pref.bbox) Draw::bbox(dim.v[0], dim.v[1], dim.v[2]);
      postDraw(texid, mat_alpha, fog);
      break;

    case STOK_WHEEL:
#if 0
      preDraw(texid, mat_alpha, fog);
      Wheel *wheel = new Wheel(spokes, radius, mat_diffuse);
      postDraw(texid, mat_alpha, fog);
#endif
      break;
  }
  glEndList();

  /* sets dlists number for this frame */
  dlists[frame] = dlist;

  /*
   * sets bounding boxes max and min
   */
  switch (shape) {
    // without bounding boxes
    case STOK_POINT:
    case STOK_LINE:
    case STOK_TRIANGLE:
    case STOK_RECT:
    case STOK_CIRCLE:
    case STOK_WHEEL:
    case STOK_ELLIPSE: // 2D shapes without BBox
      break;
    default: // with bounding boxes
      getBB(bbmax, bbmin, frame != 0);
  }
  return 1;	// only one frame
}

/* Parses statue and returns f (number of frames). */
int Solid::statueParser(char *l, V3 &bbmax, V3 &bbmin)
{
  int texid = -1;
  GLfloat scale = DEF_SCALE;
  uint16_t firstframe = 1;
  uint16_t lastframe = nbframes;
  uint16_t tabframes[FRAME_MAX] = { 0 };
  char *url_model = NULL;

  mat_alpha = DEF_ALPHA;

  ::g.render.first_bbox = true;

  while (l) {
    uint16_t tok;

    if ( (*l == '\0') || (*l == '/') ) break; // end of solid

    l = getTok(l, &tok);
    if (tok == 0) break;

    switch (tok) {
      case STOK_SOLID: break;
      case STOK_MODEL:
      case STOK_URL:
        url_model = new char[URL_LEN];
        l = wobject->parse()->parseString(l, url_model); break;
      case STOK_SCALE:
        l = wobject->parse()->parseFloat(l, &scale); break;
      case STOK_BEGINFRAME:
        l = wobject->parse()->parseUInt16(l, &firstframe); break;
      case STOK_ENDFRAME:
        l = wobject->parse()->parseUInt16(l, &lastframe); break;
      case STOK_DIFFUSE:
        l = wobject->parse()->parseVector3f(l, &mat_diffuse[0]);
        for (int i=0; i<3; i++) mat_ambient[i] = mat_diffuse[i]; break;
      case STOK_AMBIENT:
        l = wobject->parse()->parseVector3f(l, &mat_ambient[0]); break;
      case STOK_SPECULAR:
        l = wobject->parse()->parseVector3f(l, &mat_specular[0]); break;
      case STOK_ALPHA:
        l = wobject->parse()->parseFloat(l, &mat_alpha);
        mat_diffuse[3] = mat_ambient[3] = mat_alpha; break;
      case STOK_TEXTURE:
        { char *url_tex = new char[URL_LEN];
          l = wobject->parse()->parseString(l, url_tex);
#if 0
          if (*url_tex) texid = Texture::getFromCache(url_tex);
#else
          if (*url_tex) {
            texture = new Texture(url_tex);
            texid = texture->id;
            texture->object = wobject;
          }
#endif
          delete[] url_tex;
        }
        break;
      default: error("statueParser: bad tok=%d", tok); return -1;
    }
  }
  firstframe = (firstframe == 0) ? 1 : firstframe;
  if (lastframe < firstframe) lastframe = firstframe;
  int f;
  for (f=0; firstframe <= lastframe; f++) tabframes[f] = firstframe++;
  tabframes[f] = 0;

  if (url_model) {	// model url exists
    int model_t = Format::getModelByUrl(url_model);
    switch (model_t) {
      case MODEL_MD2: {
          Md2 *md2 = new Md2(url_model);

          for (f=0; tabframes[f] && f < FRAME_MAX; f++) {
            md2->setScale(scale);
            if ((dlists[f] = md2->displaylist(tabframes[f], texid)) < 0) {
              f = -1;
              break;
            }
            getBB(bbmax, bbmin, framed); // get bounding box
          }
          delete md2;
        }
        break;
      case MODEL_OBJ: {
          Obj *obj = new Obj(url_model, 0);
          obj->setScale(scale);
          obj->setColor(GL_DIFFUSE, mat_diffuse);
          obj->setColor(GL_AMBIENT, mat_diffuse);
          obj->setColor(GL_SPECULAR, mat_specular);
          dlists[0] = obj->displaylist();
          delete obj;
          f = 1;
        }
        break;
    }
  }
  return f;	// number f frames
}

// accessor
void Solid::getBB(V3 &max, V3 &min, bool framed) const
{
  ::g.render.getBB(max, min, framed);
}

// accessor
void Solid::setBB(GLfloat w, GLfloat d, GLfloat h)
{
  ::g.render.setBB(w*1, d*1, h*1);
}

void Solid::testRelative(bool flag)
{
  if (numrel) {
    switch ((int)flag) {
    case true:  // pre
      glPushMatrix();
      glRotatef(RAD2DEG(rel[3]), 0, 0, 1);	// az
      glRotatef(RAD2DEG(rel[4]), 1, 0, 0);	// ax
      glTranslatef(rel[0], rel[1], rel[2]);	// x y z
      break;
    case false: // post
      glPopMatrix();
      break;
    }
  }
}

void Solid::testScale(bool flag)
{
  switch ((int)flag) {
  case true:  // pre
    glPushMatrix();
    if (scale != 1) glScalef(scale, scale, scale);
    if (scalex != 1 || scaley != 1 || scalez != 1) glScalef(scalex, scaley, scalez);
    break;
  case false: // post
    glPopMatrix();
    break;
  }
}

void Solid::testBlend(bool flag, GLfloat alpha)
{
  if (alpha < 1) {
    is_opaque = false;
    switch ((int)flag) {
    case true:  // pre
      glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      break;
    case false: // post
      glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
      break;
    }
  }
}

void Solid::testFog(bool flag, GLfloat *fog)
{
  if (*fog > 0) {
    switch ((int)flag) {
    case true:  // pre
      glEnable(GL_FOG);
      glFogi(GL_FOG_MODE, GL_EXP);
      glFogf(GL_FOG_DENSITY, *fog);
      glFogfv(GL_FOG_COLOR, fog+1);
      break;
    case false: // post
      glDisable(GL_FOG);
      break;
    }
  }
}

void Solid::testTexture(bool flag, int texid)
{
  if (texid > 0) {
    switch ((int)flag) {
    case true:  // pre
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texid);
      break;
    case false: // post
      glDisable(GL_TEXTURE_2D);
      break;
    }
  }
}

void Solid::preDraw(int texid, GLfloat alpha, GLfloat *fog, bool cull)
{
  testFog(true, fog);
  testBlend(true, alpha);
  testTexture(true, texid);
  testScale(true);
  testRelative(true);
  if (cull) glDisable(GL_CULL_FACE);
}

void Solid::postDraw(int texid, GLfloat alpha, GLfloat *fog)
{
  glEnable(GL_CULL_FACE);
  testRelative(false);
  testScale(false);
  testTexture(false, texid);
  testBlend(false, alpha);
  testFog(false, fog);
}

/* returns relative center and size of BB. */
void Solid::getRelativeBB(V3 &center, V3 &size) const
{
  center = rel_bbcent;
  size = rel_bbsize;
}

/* returns size of BB. */
void Solid::getDim(V3 &dim) const
{
  dim = rel_bbsize;
}

/* returns relative center of BB. */
void Solid::getCenter(V3 &center) const
{
  center = rel_bbcent;
}

/* returns materials. */
void Solid::getMaterials(GLfloat *dif, GLfloat *amb, GLfloat *spe, GLfloat *emi, GLint *shi, GLfloat *alpha)
{
  for (int i=0; i<4; i++) {
    dif[i] = mat_diffuse[i];
    amb[i] = mat_ambient[i];
    spe[i] = mat_specular[i];
    emi[i] = mat_emission[i];
  }
  shi[0] = mat_shininess[0];
  *alpha = mat_alpha;
}

/*
 * Computes BB and returns absolute center and size of AABB.
 */
void Solid::getAbsoluteBB(V3 &center, V3 &size)
{
  V3 vtmp[2], vrel, vabs, vmin, vmax;

  for (int i=0; i<3; i++) {
    vtmp[0].v[i] = rel_bbcent.v[i] - rel_bbsize.v[i]; // min
    vtmp[1].v[i] = rel_bbcent.v[i] + rel_bbsize.v[i]; // max
  }

  for (int n=0; n < 8; n++) {	// 8 points of AABB parallelepidic
    vrel.v[0] = vtmp[n     % 2].v[0];
    vrel.v[1] = vtmp[(n/2) % 2].v[1];
    vrel.v[2] = vtmp[(n/4) % 2].v[2];

    // add object position
    MulM4V3(&vabs, &position, &vrel);	// vabs = posmat * vrel
    if (n == 0)  vmin = vmax = vabs;
    else {
      for (int i=0; i<3; i++) {
	vmin.v[i] = MIN(vabs.v[i], vmin.v[i]);
	vmax.v[i] = MAX(vabs.v[i], vmax.v[i]);
      }
    }
  }

  for (int i=0; i<3; i++) {
    center.v[i] = abs_bbcent.v[i] = (vmax.v[i] + vmin.v[i]) / 2;
    size.v[i]   = abs_bbsize.v[i] = (vmax.v[i] - vmin.v[i]) / 2;
  }
}

void Solid::updateBB(GLfloat az)
{
  ::g.render.updateBB(az);
}

// accessor - get WObject from Solid
WObject* Solid::object()
{
#if 0 //dax segfaukt in getDim
  if (wobject->isValid())
    return wobject;
  else
    return NULL;
#else
    return wobject;
#endif
}

void Solid::setPosition(const M4& mpos)
{
  position = mpos;
}

void Solid::getPosition(M4& mpos)
{
  mpos = position;
}

void Solid::setVisible(bool _isvisible)
{
  is_visible = _isvisible;
}

bool Solid::isVisible()
{
  return is_visible;
}

bool Solid::isOpaque()
{
  return is_opaque;
}

/** Draws a ray between user'eyes and the object's impact
 * window: +--> x	viewport: y
 *         |			  ^
 *         v			  |
 *         y			  +--> x
 */
void Solid::setRay(GLint wx, GLint wy)
{
  if (! localuser) return;

  // user's eye
  GLfloat ex = localuser->pos.x + User::NEAR; //eye + near
  GLfloat ey = localuser->pos.y;
  GLfloat ez = localuser->pos.z + localuser->height/2 - 0.10; //eye's height
  // center of selectionned object
  GLfloat ox = wobject->pos.x;
  GLfloat oy = wobject->pos.y;
  GLfloat oz = wobject->pos.z;
  // ray color
  const GLfloat *color = Color::red;  // red

  Draw::ray(&ray_dlist, ex, ey, ez, ox, oy, oz, color, 0);  // alternative

  localuser->ray = newV3(ox, oy, oz);

  localuser->noh->declareObjDelta(User::PROPRAY);  // publish ray property to network

#if 0 //dax not used
  GLdouble mview[16], mproj[16];
  GLdouble tx, ty, tz;	// computed target
  GLint vp[4];
  
  ::g.gui.getScene()->getCoords(vp);
  glGetDoublev(GL_MODELVIEW_MATRIX, mview);
  glGetDoublev(GL_PROJECTION_MATRIX, mproj);
  gluUnProject(wx, vp[3]-wy, 0, mview, mproj, vp, &tx, &ty, &tz);
  //error("e: %.1f %.1f %.1f t: %.1f %.1f %.1f o: %.1f %.1f %.1f v: %d %d %d %d w: %d %d", ex,ey,ez, tx,ty,tz, ox,oy,oz, vp[0],vp[1],vp[2],vp[3], wx,wy);
#endif
}

void Solid::resetRay()
{
  if (ray_dlist) {
    ray_dlist = 0;
    if (! localuser)  return;
    localuser->ray = newV3(0, 0, 0);
    localuser->noh->declareObjDelta(User::PROPRAY);
  }
}

void Solid::setFlashable(bool _isflashable)
{
   isflashable = _isflashable;
}

void Solid::setFlashyEdges(bool _isflashy)
{
  isflashy = _isflashy;
}

void Solid::setFlashyEdges(const GLfloat *_flashcolor)
{
  isflashy = true;
  for (int i=0; i<3; i++)  flashcolor[i] = _flashcolor[i];
}

void Solid::resetFlashyEdges()
{
  isflashy = false;
}

bool Solid::toggleBlinking()
{
  if (blink) {
    blink = false;
    return true;
  }
  else {
    blink = true;
    return false;
  }
}

void Solid::setBlinking(bool _isblinking)
{
  isblinking = _isblinking;
}

bool Solid::isBlinking() const
{
  return isblinking;
}

void Solid::setReflexive(bool _isreflexive)
{
  isreflexive = _isreflexive;
}

bool Solid::isReflexive() const
{
  return isreflexive;
}

void Solid::setFlary(bool _isflary)
{
  isflary = _isflary;
}

bool Solid::isFlary() const
{
  return isflary;
}

uint8_t Solid::getFrames() const
{
  return nbframes;
}

uint8_t Solid::getFrame() const
{
  return curframe;
}

void Solid::setFrame(uint16_t _frame)
{
  curframe = _frame % nbframes;
}
