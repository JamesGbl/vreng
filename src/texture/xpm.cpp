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
#include "img.hpp"
#include "cache.hpp"	// openCache
#include "file.hpp"	// closeFile
#include "texture.hpp"	// Texture

#if HAVE_LIBXPM
#include <X11/xpm.h>
#endif


Img * Img::loadXPM(void *tex, ImageReader read_func)
{
#if HAVE_LIBXPM
  Texture *_tex = (Texture *) tex;
  FILE *f;
  if ((f = Cache::openCache(_tex->url, _tex->http)) == NULL) return NULL;
  File::closeFile(f);

  XpmImage xpmimage;
  int r = XpmReadFileToXpmImage(Cache::getFileName(_tex->url), &xpmimage, NULL);
  if (r != XpmSuccess) {
    if (r == XpmColorFailed) error("XpmReadFileToXpmImage: bad color");
    return NULL;
  }

  int size = xpmimage.width * xpmimage.height;

  Img *img = new Img(xpmimage.width, xpmimage.height, Img::RGB);

  uint8_t *data = new uint8_t[3 * size];
  uint8_t *pxpm = (uint8_t *) xpmimage.data;
  for (int i=0; i < size ; i++, pxpm++) {
    //printf("%d %08x", i, xpmimage.data[i]);
    //dax img->pixmap[i*3 + 0] = *pxpm++;
    data[i*3 + 0] = *pxpm++;
    //printf(" %02x", img->pixmap[i*3 + 0]);
    //dax img->pixmap[i*3 + 1] = *pxpm++;
    data[i*3 + 1] = *pxpm++;
    //printf(" %02x", img->pixmap[i*3 + 1]);
    //dax img->pixmap[i*3 + 2] = *pxpm++;
    data[i*3 + 2] = *pxpm++;
    //printf(" %02x", img->pixmap[i*3 + 2]);
    //printf("\n");
  }

  //dax XpmFreeXpmImage(&xpmimage);	// get rid of the xpmimage
  //dax img->pixmap = (uint8_t *) data;
  img->pixmap = (uint8_t *) xpmimage.data;
  return img;
#else
  return NULL;
#endif
}
