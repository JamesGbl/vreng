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
 *  widgets.hpp : Ubit Widgets for the VREng GUI
 *  VREng Project
 *  Author: Eric Lecolinet - ENST Paris
 *  Date: 2002/2008
 *
 *  http://vreng.enst.fr/  http://www.enst.fr/~elc/ubit
 */
#ifndef WIDGETS_HPP
#define WIDGETS_HPP  1

#include <vector>
#include <ubit/ubit.hpp>
#include "gui.hpp"
using namespace ubit;

#if (UBIT_VERSION_MAJOR < 6 || !defined(UBIT_WITH_GL))
#   error "Vreng requires Ubit Version 6 compiled in OpenGL mode"
# endif

class Gui;
class GuiWidgets;
class Scene;
class Navig;
class Mvt;
class WObject;
class User;
class World;
class Vnc;


/**
 * GuiItem Class
 */
struct GuiItem : public UButton {
  GuiItem(UArgs args = UArgs::none);
};

/** struct for updating the ObjectBar and the ObjectMenu in the GUI */
struct ObjInfo {
  char *name;			///< class, instance or action name
  void (*fun)(int);		///< function to call
  int  farg;			///< arg of the function
};

/** KR structure for postponing Key Releases when AutoRepeat is ON */
struct KRKey {
  static const int KRBUF_MAX = 10; 	// max number of postponed Key Release(s)
  int vrkey;			///< code of the corresponding VREng change key
  struct timeval time;		///< time when this key was released
};


/**
 * GuiWidgets class
 */
class GuiWidgets : public ubit::UFrame {
public:
  static const int MESSAGES_BOX_WIDTH = 320;
  static const int MESSAGES_BOX_HEIGHT = 150;
  static const int GW_DEFAULT_SCROLL = 50;
  static const int GW_ZOOM_SCROLL = 35;

  GuiWidgets(Gui*);
  ///< constructor.

  Navig* getNavig() {return &navig;}

  void alertDialog(const char* message);
  ///< opens alert box if arg is not null, closes it if arg is null.

  void setInfobar(UBox* content);

  static void showInfoDialog(const char* title, const char* message);

  // Users - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  GuiItem* addUser(User*);
  ///< Adds an avatar name.

  void updateUser(GuiItem*, User*);
  ///< Updates an avatar.

  void removeUser(GuiItem*);
  ///< Removes an avatar name.

  // Worlds - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  GuiItem* addWorld(World*, bool isCurrentWorld);
  ///< Adds a world name.

  void updateWorld(World*, bool isCurrentWorld);
  ///< Updates a world name.

  void removeWorld(World*);
  ///< Removes a world name.

  // Callback functions
  class WObject* getPointedObject(int x, int y, ObjInfo* obji, int depthsel);
  /**< returns info about the pointed object but do NOT select it */
  
  static void callAction(int numaction);
  static void setKey(int key, int is_pressed);  
  void processKey(long keysym, int keychar, bool is_pressed);
  void flushPostponedKRs();
  bool pendingPostponedKRs() {return (postponedKRmask || postponedKRcount);}

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
private:
  friend class Gui;
  friend class Scene;
  friend class Navig;
  friend class Panels;
  
  // ! BEWARE: order matters !
  Gui& gui;            ///< reference to the GUI object
  class PutInfo& putinfo;
  class Capture& capture;
  UBox infos;
  UElem worlds, carts, avatars;
  class Scene& scene;        ///< OpenGL Drawing Zone
  class Navig& navig;		       ///< navigation
  UOptionDialog &source_dialog, &worlds_dialog;
  UDialog &prefs_dialog, &settings_dialog, &grid_dialog, &tool_dialog, &addobj_dialog;
  class Messages& messages;
  class Panels& panels;
  UBox &infobar, &menubar;
  long postponedKRmask;	       ///< mask of all postponed Key Release events
  long postponedKRcount;	     ///< count in the KRbuf
  KRKey postponedKRbuf[KRKey::KRBUF_MAX]; ///< kbd bufs

  // private methods - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Dialog
  void openSourceDialog();
  void destinationsDialog();
  void openWorldsDialog();
  UDialog& createPrefsDialog();
  UDialog& createSettingsDialog();
  UDialog& createGridDialog();
  UDialog& createToolDialog();
  UDialog& createAddobjDialog();
  UMenu& createFileMenu();
  UMenu& createMarkMenu();
  void addDynamicMenus(UMenubar&, const char* filename);
  UBox& createInfobar();
  UBox& createMenubar();

  // Message
  void openMessage(UMessageEvent&);
  void putMessage(UMessageEvent&);
  void getMessage(UMessageEvent&);
  void moveMessage(UMessageEvent&);

  // GuiWidgets internal methods
  void backCB();
  void forwardCB();
  void homeCB();
  void saveCB();
  void helpCB();
  void setPrefCB(int tool);
  void setAudioCB(bool on);
  void setVideoCB(bool on);
  void setWhiteboardCB(bool on);
  void setModelerCB(bool on);
  void addMarkCB();
  void addNewObjectCB();
  void setRayDirection(int x, int y);
};

#endif
