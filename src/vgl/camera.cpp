//---------------------------------------------------------------------------
// VREng (Virtual Reality Engine)	http://vreng.enst.fr/
//
// Copyright (C) 1997-2012 Philippe Dax
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
#include "render.hpp"
#include "scene.hpp"	// getScene
#include "solid.hpp"	// Solid
#include "wobject.hpp"	// WObject
#include "world.hpp"	// current
#include "user.hpp"	// USER_TYPE
#include "glu.hpp"	// glu alternative
#include "img.hpp"	// saveJPG
#include "ogl.hpp"	// copyPixels
#include "pref.hpp"	// width3D
#include "timer.hpp"	// getRate


// global
struct Render::sCamera cam_user;


void Render::camera()
{
  cameraProjection(cam_user.fovy, cam_user.near, cam_user.far);
}

/* Observer view, called by updateCamera: vr2gl.cpp. */
void Render::setCameraPosition(M4 *vr_mat)
{
  camera_pos = *vr_mat;
}

/*
 * Observer view, called by updateCameraFromObject: world.cpp user.cpp.
 * static
 */
void Render::cameraProjection(GLfloat fovy, GLfloat near, GLfloat far)
{
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);

  GLint width = vp[2];
  GLint height = vp[3];
  GLfloat ratio = (GLfloat) width / (GLfloat) height;
  GLfloat top = near * tan(fovy * M_PI_180);
  GLfloat bottom = -top;
  GLfloat right = top * ratio;
  GLfloat left = -right;
  cam_user.fovy = fovy;
  cam_user.near = near;
  cam_user.far = far;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(left, right, bottom, top, near, far);
  glTranslatef(0, 0, -near);	// orig -0.4
  glMatrixMode(GL_MODELVIEW);
}

void Render::setViewMode(uint8_t mode)
{
  view = mode;
  if (view != VIEW_THIRD_PERSON)
    thirdPerson_xRot = thirdPerson_yRot = thirdPerson_Near = 0;
}

uint8_t Render::getViewMode() const
{
  return view;
}

void Render::switchViewMap()
{
  viewMap = !viewMap;
}

void Render::setPitch(GLfloat angle)
{
  pitch = angle;
}

void Render::cameraPosition()
{
  M4 vr_mat;

  glMatrixMode(GL_MODELVIEW);
  glDisable(GL_SCISSOR_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//default

  switch (view) {

    case VIEW_FIRST_PERSON:
      vr_mat = MulM4(TranslateM4(0, 0, 0.15),
                     MulM4(RotateM4(pitch, UX), camera_pos));
      break;

    case VIEW_THIRD_PERSON:
      vr_mat = MulM4(TranslateM4(0, localuser->height/6, thirdPerson_Near-.8),
                     MulM4(RotateM4(M_PI_2/6 + thirdPerson_xRot + pitch, UX),
                           MulM4(RotateM4(thirdPerson_yRot, UY),
                                 camera_pos)
                          )
                    );
      break;

    case VIEW_THIRD_PERSON_FAR:
      vr_mat = MulM4(TranslateM4(0, localuser->height/6, thirdPerson_Near-2.4),
                     MulM4(RotateM4(M_PI_2/6 + thirdPerson_xRot + pitch, UX),
                           MulM4(RotateM4(thirdPerson_yRot, UY),
                                 camera_pos)
                          )
                    );
      break;

    case VIEW_TURN_AROUND:
      turnAround += (M_PI/18) / MAX(::g.times.getRate() / 5, 1);
      vr_mat = MulM4(TranslateM4(0, localuser->height/4, -2),
                     MulM4(RotateM4(M_PI_2/4, UX),
                           MulM4(RotateM4(thirdPerson_yRot + turnAround, UY),
                                 camera_pos)
                          )
                    );
      break;

    case VIEW_VERTICAL:
      vr_mat = MulM4(RotateM4(M_PI_2, UX),
                     MulM4(TranslateM4(0, -0.5, 0),	// 50cm top
                           camera_pos)
                    );
      break;

    case VIEW_VERTICAL_FAR:
      vr_mat = MulM4(RotateM4(M_PI_2, UX),
                     MulM4(TranslateM4(0, -3, 0),	// 3m top
                           camera_pos)
                    );
      break;

    case VIEW_GROUND_LEVEL:
      vr_mat = MulM4(TranslateM4(0, localuser->height - 0.10, 0), camera_pos);
      break;

    case VIEW_WIRED:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      vr_mat = MulM4(RotateM4(pitch, UX), camera_pos);
      break;

    case VIEW_SCISSOR:
      vr_mat = camera_pos;
      break;
  }

  // transpose Vreng to OpenGl coordinates
  GLfloat gl_mat[16];
  M4toV16(&vr_mat, gl_mat);
  glLoadMatrixf(gl_mat);
}


void Render::map()
{
  if (viewMap) {
    int edgesize = 1;
    GLint x, y, w, h;
    ::g.gui.getScene()->getCoords(x, y, w, h);
    
    //glScissor(x + w-(w/4), y, w/4, (GLsizei) ((h-y)/4));	// bottom-right corner
    glScissor(x + w-(w/3), y +h -h/3, w/3, (GLsizei) ((h-y)/3));  // top-right corner
    glEnable(GL_SCISSOR_TEST);
    
    ::g.gui.getScene()->setViewport(w-(w/3)+edgesize, y+h-h/3-edgesize,
                                    (w/3)-2*edgesize, (GLsizei) ((h-y)/3));
    glMatrixMode(GL_MODELVIEW);

    // place the mini-map at a position depending on the world's dimensions
    //TODO: move the mini-map when the avatar is on a edge
    World *world = World::current();
    GLfloat d = floor(MAX(world->bbsize.v[0], world->bbsize.v[1]) / tan(DEG2RAD(User::FOVY)) - 5);
    M4 vr_mat = MulM4(RotateM4(M_PI_2, UZ), TranslateM4(0, 0, -d)); // dm top

    // transpose vreng to opengl
    GLfloat gl_mat[16];
    M4toV16(&vr_mat, gl_mat);
    glLoadMatrixf(gl_mat);

    // redraw the scene inside the scissor
    clearGLBuffer();
    lighting();
    solids(false);

    if (localuser) mapUserPos = getVisiblePosition(localuser);
    mapUserPos.V_Z = 1;

    // reset initial state
    glDisable(GL_SCISSOR_TEST);
    ::g.gui.getScene()->setViewport(x, y, w, h);
  }
}

void Render::satellite()
{
  if (view == VIEW_SCISSOR) {
    int edgesize = 1;
    GLint x, y, w, h;
    ::g.gui.getScene()->getCoords(x, y, w, h);

    glScissor(x, y, w/5, (GLsizei)((h-y)/5));   // bottom-left corner
    glEnable(GL_SCISSOR_TEST);
    ::g.gui.getScene()->setViewport(edgesize, edgesize, (w/5)-2*edgesize, (GLsizei) ((h-y)/5)-2*edgesize);
    glMatrixMode(GL_MODELVIEW);

    // scene position
    glLoadIdentity();
    glRotatef(-90,1,0,0);
    glRotatef(90,0,0,1);

    // camera position
    glRotatef(-RAD2DEG(satelliteRot.V_Z), 0, 0, 1);
    glTranslatef(-satellitePos.v[0], -satellitePos.v[1], -satellitePos.v[2]);

    // draw the scene inside the scissor
    glClear(GL_COLOR_BUFFER_BIT);
    clearGLBuffer();
    lighting();
    solids(false);

    // reset initial state
    glDisable(GL_SCISSOR_TEST);
    ::g.gui.getScene()->setViewport(x, y, w, h);
    mapUserPos.V_Z = 0; //retire l'affichage de la position ds la map
  }
}

void Render::setCameraScissor(GLfloat posx, GLfloat posy, GLfloat posz, GLfloat rotz)
{
  if (view != VIEW_SCISSOR) {
    view = VIEW_SCISSOR;
    satellitePos.v[0] = posx;
    satellitePos.v[1] = posy;
    satellitePos.v[2] = posz;
    satelliteRot.v[2] = rotz;
  } else view = VIEW_FIRST_PERSON;
}

V3 Render::getVisiblePosition(WObject *po)
{
  bool seen = false;
  GLint vp[4];
  GLdouble mview[16], mproj[16];

  ::g.gui.getScene()->getCoords(vp[0], vp[1], vp[2], vp[3]);
  GLint w = vp[2];
  GLint h = vp[3];

  GLfloat xa  = po->pos.x;
  GLfloat ya  = po->pos.y;
  GLfloat za  = po->pos.z;
  GLfloat dxa = po->pos.bbsize.v[0];
  GLfloat dya = po->pos.bbsize.v[1];
  GLfloat dza = po->pos.bbsize.v[2];

  glGetDoublev(GL_MODELVIEW_MATRIX, mview);
  glGetDoublev(GL_PROJECTION_MATRIX, mproj);

  GLdouble x[5], y[5], z[5];
  gluProject(xa    , ya    , za    , mview, mproj, vp, &x[0],&y[0],&z[0]);
  gluProject(xa+dxa, ya+dya, za+dza, mview, mproj, vp, &x[1],&y[1],&z[1]);
  gluProject(xa-dxa, ya+dya, za+dza, mview, mproj, vp, &x[2],&y[2],&z[2]);
  gluProject(xa+dxa, ya-dya, za-dza, mview, mproj, vp, &x[3],&y[3],&z[3]);
  gluProject(xa-dxa, ya-dya, za-dza, mview, mproj, vp, &x[4],&y[4],&z[4]);

  for (int i=0; i<5; i++)
    y[i] = vp[3] - y[i];

  for (int i=0; i<5; i++) {
    if ((x[i] > w) || (x[i] < 0) || (y[i] > h) || (y[i] < 0)) continue;
    uint16_t n = getBufferSelection((GLint) x[i], (GLint) y[i], 0);
    WObject *o = WObject::byNum(n);
    if (o && !strcasecmp(po->getInstance(), o->getInstance())) {
      seen = true;
      break;
    }
  }
  return newV3(x[0], y[0], seen);
}

void Render::calculateFov(GLfloat posx, GLfloat posy, GLfloat posz, GLfloat rotz, char* filename)
{
  GLint vp[4];
  GLdouble mview[16], mproj[16];

  glGetIntegerv(GL_VIEWPORT, vp);
  glGetDoublev(GL_MODELVIEW_MATRIX, mview);
  glGetDoublev(GL_PROJECTION_MATRIX, mproj);

  GLint w = vp[2]; if (w & 1) ++w;	//even values
  GLint h = vp[3]; if (h & 1) ++h;

  // crash on some machines, use GL_BACK to render (test: va vers @dax@10,6,-5,1.0@ !)
  glDrawBuffer(GL_BACK);
  glPushMatrix();
   // transformations to have the good position
   glRotatef(-90, 1,0,0);
   glRotatef(90, 0,0,1);
   glRotatef(-RAD2DEG(rotz), 0,0,1);
   glTranslatef(-posx, -posy, -posz);

   // redraw the scene (solids only)
   clearGLBuffer();
   solids(false);
  glPopMatrix();

  // we use the back, then we read the back
  uint8_t *pixjpg = Ogl::copyPixels(::g.pref.width3D, ::g.pref.height3D, GL_BACK);

  // saving in a jpeg file
  int jpegquality = 1;
  Img::saveJPG(filename, ::g.pref.width3D, ::g.pref.height3D, jpegquality, pixjpg);
  delete[] pixjpg;

  // rendering reinitializes buffers then we draw in the front and the back
  render();
}

void Render::computeCameraProjection()
{
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  GLint w = viewport[2];
  GLint h = viewport[3];
  GLfloat fovy = cam_user.fovy;
  GLfloat near = cam_user.near;
  GLfloat far = cam_user.far;

  trace(DBG_FORCE, "User=(%.2f %.2f %.2f %.2f) fovy=%.2f near=%.2f far=%.2f w=%.2f h=%.2f", localuser->pos.x, localuser->pos.y, localuser->pos.z, localuser->pos.az, fovy, near, far, w, h);
}
