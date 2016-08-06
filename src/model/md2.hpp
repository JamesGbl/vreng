//---------------------------------------------------------------------------
// VREng (Virtual Reality Engine)	http://vreng.enst.fr/
//
// Copyright (C) 1997-2008 Philippe dax
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
/* GiMd2Viewer - Quake2 model viewer
 * Copyright (C) 1998  Lionel ULMER <bbrox@mygale.org>
 *
 * Based on code Copyright (C) 1997 Trey Harrison <trey@crack.com>
 */

#ifndef MD2_HPP
#define MD2_HPP

/** Md2 vertex */
typedef struct {
  float x, y, z;	///< vertex coords
  float nx, ny, xz;	///< vertex normals
} tMd2Vertex;

/** Md2 texture coord */
typedef struct {
  float s, t;		///< texture coords
} tMd2TexInfo;

/** Md2 frame */
typedef struct {
  char name[16];	///< frame name
  tMd2Vertex *vert_table;	///< vertexes table
} tMd2Frame;

/** Vector */
typedef struct {
  float x, y, z;	///< vector 3D
} tMd2Vec3;

/** Md2 Trivertex */
typedef struct {
  uint8_t x;	///< x coord
  uint8_t y;	///< y coord
  uint8_t z;	///< z coord
  uint8_t normal; ///< index of the vertex normal
} Trivertex;

/** Md2 Bounding Box */
typedef struct sBoundingBox {
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  float zmin;
  float zmax;
} tBoundingBox;

#if 0 //not used
typedef struct {
  tMd2Vec3 scale;	///< multiply byte verts by this
  tMd2Vec3 origin;	///< then add this
  char name[16];	///< frame name from grabbing
  Trivertex verts[1];	///< variable sized
} tMd2FrameInfo;

anim_t animlist[21] =
{
  // first, last, fps
  {   0,  39,  9 },   // STAND
  {  40,  45, 10 },   // RUN
  {  46,  53, 10 },   // ATTACK
  {  54,  57,  7 },   // PAIN_A
  {  58,  61,  7 },   // PAIN_B
  {  62,  65,  7 },   // PAIN_C
  {  66,  71,  7 },   // JUMP
  {  72,  83,  7 },   // FLIP
  {  84,  94,  7 },   // SALUTE
  {  95, 111, 10 },   // FALLBACK
  { 112, 122,  7 },   // WAVE
  { 123, 134,  6 },   // POINT
  { 135, 153, 10 },   // CROUCH_STAND
  { 154, 159,  7 },   // CROUCH_WALK
  { 160, 168, 10 },   // CROUCH_ATTACK
  { 196, 172,  7 },   // CROUCH_PAIN
  { 173, 177,  5 },   // CROUCH_DEATH
  { 178, 183,  7 },   // DEATH_FALLBACK
  { 184, 189,  7 },   // DEATH_FALLFORWARD
  { 190, 197,  7 },   // DEATH_FALLBACKSLOW
  { 198, 198,  5 },   // BOOM
};
#endif

/** Md2 header */
typedef struct {
  char ident[4];	///< magic number
  int32_t version;	///< version
  int32_t skinwidth;	///< width
  int32_t skinheight;	///< height
  int32_t framesize;    ///< byte size of each frame
  int32_t num_skins;	///< number of skins
  int32_t num_xyz;	///< number of vertices ?
  int32_t num_st;       ///< greater than num_xyz for seams
  int32_t num_tris;	///< number of triangles
  int32_t num_glcmds;   ///< dwords in strip/fan command list
  int32_t num_frames;	///< number of frames
  int32_t ofs_skins;    ///< each skin is a MAX_SKINNAME string
  int32_t ofs_st;       ///< byte offset from start for stverts
  int32_t ofs_tris;     ///< offset for dtriangles
  int32_t ofs_frames;   ///< offset for first frame
  int32_t ofs_glcmds;	///< offset for gl cmds
  int32_t ofs_end;      ///< end of file
} tMd2Header;

/**
 * Md2 class
 */
class Md2 {

private:
  int32_t *glcmds;	///< GL commands
  tMd2TexInfo *texinfo;	///< texture infos
  tMd2Frame *frames;	///< frames
  tBoundingBox bbox;	///< bounding box
  bool loaded;		///< flag loaded or not
  GLint *dlists;	///< diplay list for frames
  float desiredScale;	///< scale
  char *url;		///< md2 url

public:
  int32_t numframes;	///< number of frames
  int32_t skinwidth;	///< skin width
  int32_t skinheight;	///< skin height

  Md2(const char *url);	///< Constructor
  virtual ~Md2();	///< Destructor

  virtual int32_t displaylist(int frame, int texture);
  /**< Get display-lists from Md2 model */

  virtual void setScale(float scale);
  /**< Sets scale of model */

  virtual float getRadius();
  /**< Gets radius of model */

  virtual void render(struct Pos &pos);
  /**< Renders the model */

  virtual void render(struct Pos &pos, uint16_t frame);
  /**< Renders one frame of the model */

  static void httpReader(void *_md2, class Http *http);
  /**< Md2 http reader */

private:
  virtual void defaults();
  /**< Sets default values */

  virtual bool loadFromHttp(Http *http);
  /**< Loads from http */

  virtual bool loadFromFile(FILE *f);
  /**< Loads from file */

  virtual const char * getUrl() const;
  /**< get an Url */

  virtual int32_t getFrames(tMd2Header *md2_hdr, FILE *f);
  virtual int32_t getFrames(tMd2Header *md2_hdr, class Http *http);
  /**< Get frames from Md2 model */

  virtual int32_t getGLCmds(tMd2Header *md2_hdr, FILE *f);
  virtual int32_t getGLCmds(tMd2Header *md2_hdr, class Http *http);
  /**< Get GL commands from Md2 model */

  virtual void updBbox(float x, float y, float z);
  /**< Updates BB */

  virtual void draw(int32_t frame, int32_t nextfrm, float ratio, float scale);
  /**< Draw frames of Md2 Model */

  virtual int32_t displaylist(int frame, int nextfrm, float inter, float scale, int texture);
  /**< Get display-lists from Md2 model */
};

#endif
