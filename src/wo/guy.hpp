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
#ifndef GUY_HPP
#define GUY_HPP

#include "wobject.hpp"

class Http;

#define GUY_TYPE 34
#define GUY_NAME "Guy"


#define CYCLE		50
#define MAX_JOINTS	5
#define MAX_CPOINTS	34	// 2 end point ones and 10 in the middle
#define HEAD_R		0.08	// d=16
#define NECK_H		0.05	//
#define NECK_R		0.04	//
#define BUST_H		0.60	//
#define BUST_W		0.22	//
#define BUST_L		0.52	//
#define ULEG_H		0.37	//
#define LLEG_H		0.37	//
#define UARM_H		0.33	//
#define LARM_H		0.33	//
#define ANKLE_R		0.03	//
#define FOOT_H		0.11	//
#define HIP_R		0.09	// d=18
#define SHOULDER_R	0.04	// d=8
#define KNEE_R		0.05	// d=10
#define ELBOW_R		0.03	// d=6
#define WRIST_R		0.03	// d=6
#define BREATH_R	0.06	// d


typedef struct {
  int numpoints;
  float coords[MAX_CPOINTS];
  float angles[MAX_CPOINTS];
} tGuyCtrlPts;


/**
 * Guy class
 */
class Guy: public WObject {

private:
  enum {
    BUST,
    NECK,
    HEAD,
    ULEG,
    LLEG,
    FOOT,
    UARM,
    LARM,
    BREATH
  };

  static uint16_t RATE;
  static uint8_t BODY_PARTS;
  static uint8_t OVERSAMPLE;
  static const char DEF_URL[];
  static const float BUST_COLOR[];
  static const float LEGS_COLOR[];
  static const float SKIN_COLOR[];
  static const float FEET_COLOR[];

  uint8_t step;		///< position in cycle, start in middle
  float incstep;	///< step increment
  GLint dlist;		///< body displaylist
  uint8_t sex;		///< sex toggle 0=male 1=female
  uint8_t walking;	///< walk toggle
  uint8_t animing;	///< anim toggle
  bool showing;		///< showing flag
  bool flying;		///< flying flag
  bool control;		///< flag controlled or not by user
  uint8_t numjoints;	///< joinpoint number
  tGuyCtrlPts *curve;	///< series of ctrl points for a joint
  float skin_color[4];  ///< skin color
  float bust_color[4];  ///< bust color
  float legs_color[4];  ///< legs color
  float feet_color[4];  ///< feet color
  float cycles[2][MAX_JOINTS][CYCLE]; ///< array of angles

public:
  static const OClass oclass;	///< class variable.

  virtual const OClass* getOClass() {return &oclass;}

  static void funcs();	///< init funclist.

  Guy(char *l);		///< Constructor from file.
  Guy();		///< Constructor from user.

  static WObject * (creator)(char *l);

  virtual void changePermanent(float lasting);

  virtual void draw();
  /**< Draws the body. */

  virtual void render();
  /**< Specific rendering. */

  virtual void quit();
  /**< Quits properly. */

  virtual void pose();

  virtual void anim(bool flag);
  /**< Set animing flag. */

  virtual void fly(bool flag);
  /**< Set flying flag. */

  virtual void show(bool flag);
  /**< Set showing flag. */

private:
  virtual void parser(char *l);
  /**< Parses file line. */

  virtual void defaults();
  /**< Sets default values. */

  virtual void makeSolid();
  /**< Builds geometry. */

  virtual void behavior();
  /**< Sets behavior. */

  virtual void inits();
  /**< Do specific initializations. */

  static void httpReader(void *oa, Http *http);
  /**< Reads cset files. */

  virtual void computeCurve(int joint);
  /**< Computes cset curves. */

  virtual const char * getUrl() const;

  virtual void draw_bust();
  virtual void draw_neck();
  virtual void draw_breath();
  virtual void draw_head();
  virtual void draw_uleg();
  virtual void draw_lleg();
  virtual void draw_foot();
  virtual void draw_uarm();
  virtual void draw_larm();

  virtual void display_body();
  /**< Displays the body. */

  virtual void display_bust();
  virtual void display_neck();
  virtual void display_breath(int which);
  virtual void display_head();
  virtual void display_leg(int which);
  virtual void display_arm(int which);

  // GUI callbacks
  static void animate_cb(Guy *o, void *d, time_t s, time_t u);
  static void walking_cb(Guy *o, void *d, time_t s, time_t u);
};

#endif
