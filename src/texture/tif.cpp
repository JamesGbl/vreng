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
#include "reader.hpp"	// Reader
#include "cache.hpp"	// openCache
#include "texture.hpp"	// Texture

#if HAVE_TIFFIO_H
#include <tiffio.h>
#endif


/** Load a TIFF image */
Img * Img::loadTIF(void *tex, ImageReader read_func)
{
#if HAVE_LIBTIFF
  // we download the tiff file and put it into the cache
  Reader *ir = new Reader(tex, read_func);

  if (ir->downloadInCache(tex, Reader::KEEP_CLOSE) == NULL) {	// not opened
    delete ir;
    return NULL;
  }
  delete ir;

  // we open the tiff file
  TIFF *fp;
  if (! (fp = TIFFOpen(ir->getFilename(tex), "r"))) return NULL;

  /* we read the header */
  uint16_t width, height;
  uint8_t channel;

  TIFFGetField(fp, TIFFTAG_IMAGEWIDTH, &width);
  TIFFGetField(fp, TIFFTAG_IMAGELENGTH, &height);
  TIFFGetField(fp, TIFFTAG_SAMPLESPERPIXEL, &channel);

  if (channel <= Img::RGB) channel = Img::RGB;
  else channel = Img::RGBA;

  trace(DBG_IMG, "loadTIF: width=%d height=%d channel=%d", width, height, channel);

  // always 4 bytes per pixel for this
  uint32 * tmpImage = (uint32 *)_TIFFmalloc((tsize_t)(width * height * sizeof(uint32_t)));

  // we read the data with the library
  if (! TIFFReadRGBAImage(fp, width, height, tmpImage, 0)) {
    error("loadTIF: error reading file %s", ir->getFilename(tex));
    return NULL;
  }

  // we alloc img and the pixmap
  Img *img = new Img(width, height, channel);

  // convert component format
  uint8_t *pixptr = img->pixmap;

  for (int i=0; i < height ; i++) {
    for (int j=0; j < width ; j++) {
      uint32_t pixel = tmpImage[(i*width) + j];

      *pixptr++ = (uint8)TIFFGetR(pixel);
      *pixptr++ = (uint8)TIFFGetG(pixel);
      *pixptr++ = (uint8)TIFFGetB(pixel);
      if (channel == Img::RGBA)
        *pixptr++ = (uint8)TIFFGetA(pixel);
    }
  }
  _TIFFfree(tmpImage);
  TIFFClose(fp);

  return img;
#else
  return NULL;
#endif
}
