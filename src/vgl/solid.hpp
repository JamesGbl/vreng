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
/*
 * Les fonctions suivantes sont utilisees pour gerer des solides
 * disposes dans le monde.
 * On n'a pas specifie ici:
 * - la gestion des sources lumineuses et des modeles lumineux
 * - la gestion des hierarchies d'objets
 * - les fonctions d'entree/sortie pour les geometries et les scenes
 * - comment gerer plusieurs mondes ou affichages
 */
#ifndef SOLID_HPP
#define SOLID_HPP


/**
 * Solid class
 */
class Solid {
  friend class WObject; //DB FIXME, suppress direct access from the WObject class
  friend class Texture;

protected:
  class WObject	*wobject;	///< WObject parent.
  class Texture *texture;
  GLint*	dlists;		///< cached display list.
  M4		position;	///< position matrix.
  V3		rel_bbcent;	///< relative center of BB.
  V3		rel_bbsize;	///< relative half sizes of BB.
  V3		abs_bbcent;	///< absolute center of BB.
  V3		abs_bbsize;	///< absolute half sizes of BB.
  bool		is_visible;	///< should this solid be drawn ?.
  bool		is_opaque;	///< set if the solid is totaly opaque.
  GLfloat	mat_diffuse[4];
  GLfloat	mat_ambient[4];
  GLfloat	mat_specular[4];
  GLfloat	mat_emission[4];
  GLint		mat_shininess[1];
  GLfloat	mat_alpha;
  GLfloat	scale, scalex, scaley, scalez;

public:
  enum rendering_mode {
    PLAIN,		///< render surfaces with plain colors.
    TEXTURED,		///< render surfaces with their textures.
    WIRED,		///< don't render surfaces, only render edges.
    ZBUFSELECT		///< only fill the Z-buffer (for selection).
  };

  /* display modes */
  enum display_mode {
    NORMAL,
    VIRTUAL,
    FLASHY,
    REFLEXIVE,
    PROGRESS
  };

  uint8_t	shape;		///< basic shape.
  uint8_t	numrel;		///< relative solid number.
  uint16_t	nbframes;	///< number of frames of this solid.
  uint16_t	frame;		///< frame number.
  uint16_t	curframe;	///< current frame.
  bool		framed;		///< flag framed.
  bool		isflashy;	///< flag flashy.
  bool		isflashable;	///< flag flashable.
  bool		isreflexive;	///< flag reflexive.
  bool		isflary;	///< flag flary.
  bool		isblinking;	///< flag blinking.
  bool		blink;		///< flag blink.
  GLint		ray_dlist;	///< ray display list.
  GLfloat 	flashcolor[3];	///< flash color.
  GLfloat 	rel[5];		///< relative position/orientation.
  char		name[HNAME_LEN];///< solid name.

  Solid();		///< constructor.
  virtual ~Solid();	///< destructor.

  // Accessors
  virtual WObject* object();
  /**< Returns the associated WObject. */

  virtual void getAbsoluteBB(V3& bbcent, V3& bbsize);
  /**< Returns a bounding box for this solid.
   * The bounding box is aligned with the world reference. */

  virtual void getRelativeBB(V3& bbcent, V3& bbsize) const;
  virtual void getDim(V3& bbsize) const;
  virtual void getCenter(V3& bbcent) const;
  /**< Returns relative bounding-box. */

  virtual void updateBB(GLfloat az);
  /**< Updates BB according to its orientation. */

  virtual void getMaterials(GLfloat *diff, GLfloat *amb, GLfloat *spe, GLfloat *emi, GLint *shi, GLfloat *alpha);
  /* Returns materials. */

  virtual void setPosition(const M4& mpos);
  /**< Updates the solid position.
   * The position is defined by the matrix 4x4 'mpos'
   * which gives the transformation todo on local coords towards world coords.
   */

  virtual void getPosition(M4& mpos);
  /**< Gives solid's position. */

  virtual void setVisible(bool v);
  /**< Sets the solid visible (true) or invisible (false). */

  virtual bool isVisible();
  /**< Return if the solid should be drawn or not. */

  virtual bool isOpaque();
  /**< Return if the solid is opaque or not. */

  // Drawing
  virtual void render3D(rendering_mode mode, uint8_t layer);
  /**< Issue the OpenGL commands to draw the solid in the given mode.
       It is called several times with "layer" increasing from 0 to ? in
       order to allow drawing at different layers. */

  // File parsing
  virtual char* parser(char *l);	///< Parser commun.

  virtual char* parseFrame(char* l);
  virtual char* parseShape(char* l);
  virtual int statueParser(char* l, V3& bbmax, V3& bbmin);
  virtual int solidParser(char* l, V3& bbmax, V3& bbmin);

  virtual uint8_t getFrames() const;
  /**< Gets the number of frames. */

  virtual uint8_t getFrame() const;
  /**< Gets the index of current frames. */

  virtual void setFrame(uint16_t frame);
  /**< Changes the "frame" of the solid (ie its geometry). */

  virtual bool isBlinking() const;
  /**< Checks if blinking. */

  virtual bool toggleBlinking();
  /**< Checks if rendering of a blinking solid must be done. */

  virtual void setRay(GLint x, GLint y);
  /**< Makes a ray between user'eyes and the center of the object. */

  virtual void resetRay();
  /**< Resets ray. */

  virtual void setFlashyEdges(const GLfloat *_flashcolor);
  /**< Sets the solid edges flashy with this color. */

  virtual void resetFlashyEdges();
  /**< Resets the solid edges flashy. */

  virtual void setReflexive(bool flag);
  /**< Sets the solid reflexive. */

  virtual bool isReflexive() const;
  /**< Checks whether the solid is reflexive. */

  virtual void setFlary(bool flag);
  /**< Sets the solid flary. */

  virtual bool isFlary() const;
  /**< Checks whether the solid is flary. */

  virtual void setFlashyEdges(bool flag);
  /**< Sets the solid edges flashy. */

  virtual char * getFramesNumber(char *l);
  /**< Parses frames number. */

  virtual int displayList(int rendertype);
  /**< Renders a solid in display-list. */

  virtual int displayNormal();
  /**< Renders a normal solid. */

  virtual int displayReflexive();
  /**< Renders a reflexive solid. */

  virtual int displayVirtual();
  /**< Renders a reflexive solid. */

  virtual void displayFlary();
  /**< Renders attached flare to a solid. */

  virtual int displayFlashy();
  /**< Renders a solid flashy. */

  virtual void displayRay();
  /**< Displays ray. */

  virtual char * skipEqual(char *p);
  /** Skips '=' character. */

  virtual void vr2gl();
  /**< Transposes vreng coordinates in opengl coordinates. */

#if 0
  static void update3D(Pos &pos);
  /**< Updates object in the 3D. */

  static void updateAll3D(Pos &pos);
  /**< Updates object in the 3D. */

  static void updateCamera(Pos &pos);
  /**< Updates camera in the 3D. */

  static void getSurfVecs(Pos &pos, V3 *v, V3 *w, V3 *norm);
  /**< Returns two vectors that describe the object's surface
   * and a normal vector to that surface
   */
#endif

private:

  virtual void setFlashable(bool flag);
  /**< Sets the solid flashable. */

  virtual void setBlinking(bool flag);
  /**< Sets the solid blinking. */

  virtual void preDraw(int texid, GLfloat alpha, GLfloat *fog, bool cull = false);
  /**< Begins transforms before drawing. */

  virtual void postDraw(int texid, GLfloat alpha, GLfloat *fog);
  /**< Ends transforms after drawing. */

  virtual void getBB(V3 &max, V3 &min, bool framed) const;
  /**< Gets BB. */

  virtual void setBB(GLfloat w, GLfloat d, GLfloat h);
  /**< Sets BB. */

  virtual void testRelative(bool flag);
  /**< Makes transforms if relative postion. */

  virtual void testScale(bool flag);
  /**< Makes scaling operations. */

  virtual void testBlend(bool flag, GLfloat alpha);
  /**< Makes blending operations if alpha. */

  virtual void testFog(bool flag, GLfloat *fog);
  /**< Makes fog operations if fog. */

  virtual void testTexture(bool flag, int texid);
  /**< Makes texture binding */

  virtual char* getTok(char* l, uint16_t* tok);
  /** Gets current token. */

  virtual void displayMirroredScene();
  /**< Displays the mirrored scene */

#if 0 //not used
  virtual void displayObject();
  /**< Displays a reflexive object. */

  virtual int solidIntersect(Solid *s2);
  /**< Returns True if both solids 's1' et 's2' intersect themself
   * not implemented for the moment: return 'true'. */

  static void setFrameBuffer(char *buf, int x0, int y0, int xsize, int ysize);
  /**< parameters given the position of the display buffer in the display window
   * (at address 'buf').
   * note: 'xsize' and 'x0' must be even. */
#endif //not used

};

#endif
