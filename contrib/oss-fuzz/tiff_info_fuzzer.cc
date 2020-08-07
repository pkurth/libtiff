// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>

#include <fcntl.h>
#include <stdarg.h>
#include <stddef.h>

#include "libtiff/tif_config.h"
#include "libtiff/tiff.h"
#include "libtiff/tiffio.h"
#include "libtiff/tiffiop.h"
#include "contrib/stream/tiffstream.h"

constexpr size_t kMaxMalloc = 250000000; // 1/4 GB

void TIFFReadContigStripData(TIFF *tif, unsigned char* buf) {
  const tsize_t scanline = TIFFScanlineSize(tif);

  uint32 h = 0;
  uint32 rowsperstrip = (uint32)-1;

  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);
  for (uint32 row = 0; row < h; row += rowsperstrip) {
    const uint32 nrow = (row + rowsperstrip > h ? h - row : rowsperstrip);
    tstrip_t strip = TIFFComputeStrip(tif, row, 0);
    if (TIFFReadEncodedStrip(tif, strip, buf, nrow * scanline) < 0) {
      break;
    }
  }
  _TIFFfree(buf);
}

void TIFFReadSeparateStripData(TIFF *tif, unsigned char* buf) {
  tsize_t scanline = TIFFScanlineSize(tif);

  uint32 h = 0;
  uint32 rowsperstrip = (uint32)-1;
  tsample_t samplesperpixel = 0;

  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
  for (uint32 row = 0; row < h; row += rowsperstrip) {
    for (tsample_t s = 0; s < samplesperpixel; s++) {
      uint32 nrow = (row + rowsperstrip > h ? h - row : rowsperstrip);
      tstrip_t strip = TIFFComputeStrip(tif, row, s);
      if (TIFFReadEncodedStrip(tif, strip, buf, nrow * scanline) < 0) {
        break;
      }
    }
  }
}

void TIFFReadContigTileData(TIFF *tif, unsigned char* buf) {
  tsize_t rowsize = TIFFTileRowSize(tif);

  uint32 tw = 0, th = 0, w = 0, h = 0;

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetField(tif, TIFFTAG_TILEWIDTH, &tw);
  TIFFGetField(tif, TIFFTAG_TILELENGTH, &th);
  for (uint32 row = 0; row < h; row += th) {
    for (uint32 col = 0; col < w; col += tw) {
      if (TIFFReadTile(tif, buf, col, row, 0, 0) < 0) {
        break;
      }
    }
  }
}

void TIFFReadSeparateTileData(TIFF *tif, unsigned char* buf) {
  const tsize_t rowsize = TIFFTileRowSize(tif);

  uint32 tw = 0, th = 0, w = 0, h = 0;
  tsample_t s, samplesperpixel = 0;

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetField(tif, TIFFTAG_TILEWIDTH, &tw);
  TIFFGetField(tif, TIFFTAG_TILELENGTH, &th);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
  for (uint32 row = 0; row < h; row += th) {
    for (uint32 col = 0; col < w; col += tw) {
      for (s = 0; s < samplesperpixel; s++) {
        if (TIFFReadTile(tif, buf, col, row, 0, s) < 0) {
          break;
        }
      }
    }
  }
}

void TIFFReadData(TIFF *tif) {

  uint16 config;
  unsigned char *buf;

  TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &config);
  if (TIFFIsTiled(tif)) {

    tmsize_t tileSize = TIFFTileSize(tif);
    if (tileSize > kMaxMalloc)
      return;
    buf = (unsigned char *)_TIFFmalloc(tileSize);
    if (buf == nullptr)
      return;

    if (config == PLANARCONFIG_CONTIG)
      TIFFReadContigTileData(tif, buf);
    else
      TIFFReadSeparateTileData(tif, buf);
  } else {

    tmsize_t stripSize = TIFFStripSize(tif);
    if (stripSize > kMaxMalloc)
      return;
    buf = (unsigned char *)_TIFFmalloc(stripSize);
    if (buf == nullptr)
      return;

    if (config == PLANARCONFIG_CONTIG)
      TIFFReadContigStripData(tif, buf);
    else
      TIFFReadSeparateStripData(tif, buf);
  }

  _TIFFfree(buf);
}

void FuzzErrorHandler(const char *, const char *, va_list) {}
void FuzzErrorHandlerExt(thandle_t, const char *, const char *, va_list) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TIFFSetErrorHandler(FuzzErrorHandler);
  TIFFSetErrorHandlerExt(FuzzErrorHandlerExt);
  TIFFSetWarningHandler(FuzzErrorHandler);
  TIFFSetWarningHandlerExt(FuzzErrorHandlerExt);

  const std::string s(reinterpret_cast<const char*>(data), size);
  std::istringstream iss(s);
  std::istream& stream = iss;

  TiffStream ts;
  TIFF *tif = ts.makeFileStream(&stream);
  if (tif == nullptr)
    return 0;

  do {
    toff_t offset = 0;

    TIFFPrintDirectory(tif, stdout, 0); // TODO(rjotwani): replace stdout
    TIFFReadData(tif);
    if (TIFFGetField(tif, TIFFTAG_EXIFIFD, &offset)) {
      if (TIFFReadEXIFDirectory(tif, offset)) {
        TIFFPrintDirectory(tif, stdout, 0); // TODO(rjotwani): replace stdout
      }
    }
  } while (TIFFReadDirectory(tif));

  TIFFClose(tif);
  return 0;
}
