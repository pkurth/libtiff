/*
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef _TIFFIO_
#define	_TIFFIO_

/**
 * @file tiffio.h
 * @brief TIFF I/O Library Definitions.
 */
#include "tiff.h"
#include "tiffvers.h"

/**
 * @brief A TIFF image file.
 * @details The internal details of this structure are private.
 */
typedef struct tiff TIFF;

/*
 * The following typedefs define the intrinsic size of
 * data types used in the *exported* interfaces.  These
 * definitions depend on the proper definition of types
 * in tiff.h.  Note also that the varargs interface used
 * to pass tag types and values uses the types defined in
 * tiff.h directly.
 */

/**
 * @brief Signed machine addressing size type.
 * @details This type int32_t on 32bit machines, int64_t on 64bit machines.
 */
typedef TIFF_SSIZE_T tmsize_t;

/**
 * @brief Maximum size of tmsize_t.
 */
#define TIFF_TMSIZE_T_MAX (tmsize_t)(SIZE_MAX >> 1)

/**
 * @brief File offset
 * @note toff_t is not off_t for many reasons; TIFFs max out at
 * 32-bit file offsets, and BigTIFF maxes out at 64-bit
 * offsets being the most important, and to ensure use of
 * a consistently unsigned type across architectures.
 * Prior to libtiff 4.0, this was an unsigned 32-bit type.
 */
typedef uint64_t toff_t;

/* the following are deprecated and should be replaced by their defining
   counterparts */

/**
 * @brief Directory tag.
 * @note ttag_t is unsigned int and not unsigned short because
 * ANSI C requires that the type before the ellipsis be a
 * promoted type (i.e. one of int, unsigned int, pointer,
 * or double) and because we defined pseudo-tags that are
 * outside the range of legal Aldus-assigned tags.
 */
typedef uint32_t ttag_t;

/** Directory index */
typedef uint16_t tdir_t;

/** Sample number */
typedef uint16_t tsample_t;

/** Strip or tile number */
typedef uint32_t tstrile_t;

/** Strip number */
typedef tstrile_t tstrip_t;

/** Tile number */
typedef tstrile_t ttile_t;

/** I/O size in bytes
 * @note tsize_t is signed and not unsigned because some functions
 * return -1.
 */
typedef tmsize_t tsize_t;

/** Image data reference */
typedef void* tdata_t;

#if !defined(__WIN32__) && (defined(_WIN32) || defined(WIN32))
#define __WIN32__
#endif

/*
 * On windows you should define USE_WIN32_FILEIO if you are using tif_win32.c
 * or AVOID_WIN32_FILEIO if you are using something else (like tif_unix.c).
 *
 * By default tif_unix.c is assumed.
 */

#if defined(_WINDOWS) || defined(__WIN32__) || defined(_Windows)
#  if !defined(__CYGWIN) && !defined(AVOID_WIN32_FILEIO) && !defined(USE_WIN32_FILEIO)
#    define AVOID_WIN32_FILEIO
#  endif
#endif

#if defined(USE_WIN32_FILEIO)
# define VC_EXTRALEAN
# include <windows.h>
# ifdef __WIN32__
/** Client data handle */
DECLARE_HANDLE(thandle_t);
# else
/** Client data handle */
typedef HFILE thandle_t;
# endif /* __WIN32__ */
#else
/** Client data handle */
typedef void* thandle_t;
#endif /* USE_WIN32_FILEIO */

/*
 * Flags to pass to TIFFPrintDirectory to control
 * printing of data structures that are potentially
 * very large.   Bit-or these flags to enable printing
 * multiple items.
 */

/** Print no extra information */
#define TIFFPRINT_NONE	       0x0
/** Print strips or tiles information */
#define TIFFPRINT_STRIPS       0x1
/** Print color or gray response curves */
#define TIFFPRINT_CURVES       0x2
/** Print colormap */
#define TIFFPRINT_COLORMAP     0x4

/** Print JPEG Q matrices */
#define TIFFPRINT_JPEGQTABLES  0x100
/** Print JPEG AC tables */
#define TIFFPRINT_JPEGACTABLES 0x200
/** Print JPEG DC tables */
#define TIFFPRINT_JPEGDCTABLES 0x200

/* 
 * Colour conversion macros.
 */

/** Reference white (D65 X) */
#define D65_X0 (95.0470F)
/** Reference white (D65 Y) */
#define D65_Y0 (100.0F)
/** Reference white (D65 Z) */
#define D65_Z0 (108.8827F)

/** Reference white (D50 X) */
#define D50_X0 (96.4250F)
/** Reference white (D50 Y) */
#define D50_Y0 (100.0F)
/** Reference white (D50 Z) */
#define D50_Z0 (82.4680F)


/** 8-bit R, G or B sample */
typedef unsigned char TIFFRGBValue;

/** Display device description. */
typedef struct {
	float d_mat[3][3]; /**< XYZ -> luminance matrix */
	float d_YCR;       /**< Light o/p for reference white (R) */
	float d_YCG;       /**< Light o/p for reference white (G) */
	float d_YCB;       /**< Light o/p for reference white (B) */
	uint32_t d_Vrwr;   /**< Pixel values for reference white (R) */
	uint32_t d_Vrwg;   /**< Pixel values for reference white (G) */
	uint32_t d_Vrwb;   /**< Pixel values for reference white (B) */
	float d_Y0R;       /**< Residual light for black pixel (R) */
	float d_Y0G;       /**< Residual light for black pixel (G) */
	float d_Y0B;       /**< Residual light for black pixel (B) */
	float d_gammaR;    /**< Gamma values for the three guns (R) */
	float d_gammaG;    /**< Gamma values for the three guns (G) */
	float d_gammaB;    /**< Gamma values for the three guns (B) */
} TIFFDisplay;

/** YCbCr conversion to RGB */
typedef struct {
	TIFFRGBValue* clamptab; /** Range clamping table */
	int* Cr_r_tab;
	int* Cb_b_tab;
	int32_t* Cr_g_tab;
	int32_t* Cb_g_tab;
	int32_t* Y_tab;
} TIFFYCbCrToRGB;

/** CIE Lab 1976 conversion to RGB */
typedef struct {                                  
	int range;                                /**< Size of conversion table */
#define CIELABTORGB_TABLE_RANGE 1500
	float rstep, gstep, bstep;
	float X0, Y0, Z0;                         /**< Reference white point */
	TIFFDisplay display;
	float Yr2r[CIELABTORGB_TABLE_RANGE + 1];  /**< Conversion of Yr to r */
	float Yg2g[CIELABTORGB_TABLE_RANGE + 1];  /**< Conversion of Yg to g */
	float Yb2b[CIELABTORGB_TABLE_RANGE + 1];  /**< Conversion of Yb to b */
} TIFFCIELabToRGB;

/**
 * RGBA-style image.
 */
typedef struct _TIFFRGBAImage TIFFRGBAImage;

/*
 * The image reading and conversion routines invoke
 * "put routines" to copy/image/whatever tiles of
 * raw image data.  A default set of routines are 
 * provided to convert/copy raw image data to 8-bit
 * packed ABGR format rasters.  Applications can supply
 * alternate routines that unpack the data into a
 * different format or, for example, unpack the data
 * and draw the unpacked raster on the display.
 */
typedef void (*tileContigRoutine)
    (TIFFRGBAImage*, uint32_t*, uint32_t, uint32_t, uint32_t, uint32_t, int32_t, int32_t,
     unsigned char*);
typedef void (*tileSeparateRoutine)
    (TIFFRGBAImage*, uint32_t*, uint32_t, uint32_t, uint32_t, uint32_t, int32_t, int32_t,
     unsigned char*, unsigned char*, unsigned char*, unsigned char*);

/*
 * RGBA-reader state.
 */
struct _TIFFRGBAImage {
	TIFF* tif;                              /**< image handle */
	int stoponerr;                          /**< stop on read error */
	int isContig;                           /**< data is packed/separate */
	int alpha;                              /**< type of alpha data present */
	uint32_t width;                           /**< image width */
	uint32_t height;                          /**< image height */
	uint16_t bitspersample;                   /**< image bits/sample */
	uint16_t samplesperpixel;                 /**< image samples/pixel */
	uint16_t orientation;                     /**< image orientation */
	uint16_t req_orientation;                 /**< requested orientation */
	uint16_t photometric;                     /**< image photometric interp */
	uint16_t* redcmap;                        /**< colormap palette */
	uint16_t* greencmap;
	uint16_t* bluecmap;
	/** get image data routine */
	int (*get)(TIFFRGBAImage*, uint32_t*, uint32_t, uint32_t);
	/** put decoded strip/tile */
	union {
	    void (*any)(TIFFRGBAImage*);
	    tileContigRoutine contig;
	    tileSeparateRoutine separate;
	} put;
	TIFFRGBValue* Map;                      /**< sample mapping array */
	uint32_t** BWmap;                         /**< black&white map */
	uint32_t** PALmap;                        /**< palette image map */
	TIFFYCbCrToRGB* ycbcr;                  /**< YCbCr conversion state */
	TIFFCIELabToRGB* cielab;                /**< CIE L*a*b conversion state */

	uint8_t* UaToAa;                          /**< Unassociated alpha to associated alpha conversion LUT */
	uint8_t* Bitdepth16To8;                   /**< LUT for conversion from 16bit to 8bit values */

	int row_offset;
	int col_offset;
};

/*
 * Macros for extracting components from the
 * packed ABGR form returned by TIFFReadRGBAImage.
 */
#define TIFFGetR(abgr) ((abgr) & 0xff)
#define TIFFGetG(abgr) (((abgr) >> 8) & 0xff)
#define TIFFGetB(abgr) (((abgr) >> 16) & 0xff)
#define TIFFGetA(abgr) (((abgr) >> 24) & 0xff)

/*
 * A CODEC is a software package that implements decoding,
 * encoding, or decoding+encoding of a compression algorithm.
 * The library provides a collection of builtin codecs.
 * More codecs may be registered through calls to the library
 * and/or the builtin implementations may be overridden.
 */

/** Codec initialisation method. */
typedef int (*TIFFInitMethod)(TIFF*, int);

/** Codec definition */
typedef struct {
	char* name;
	uint16_t scheme;
	TIFFInitMethod init;
} TIFFCodec;

#include <stdio.h>
#include <stdarg.h>

/* share internal LogLuv conversion routines? */
#ifndef LOGLUV_PUBLIC
#define LOGLUV_PUBLIC 1
#endif

#if defined(__GNUC__) || defined(__attribute__)
#  define TIFF_ATTRIBUTE(x)    __attribute__(x)
#else
#  define TIFF_ATTRIBUTE(x) /*nothing*/
#endif

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Pointer to error handling function.
 * @param module Module name
 * @param fmt Message format string
 * @param ap Message format arguments
 */
typedef void (*TIFFErrorHandler)(const char* module, const char* fmt, va_list ap);

/**
 * @brief Pointer to extended error handling function.
 * @param handle Client handle
 * @param module Module name
 * @param fmt Message format string
 * @param ap Message format arguments
 */
typedef void (*TIFFErrorHandlerExt)(thandle_t handle, const char* module, const char* fmt, va_list ap);

/**
 * @brief Pointer to read or write function.
 * @param handle Client handle
 * @param buf Pointer to data buffer for reading into or writing from
 * @param size Size of data buffer
 * @returns Number of bytes read or written
 */
typedef tmsize_t (*TIFFReadWriteProc)(thandle_t handle, void* buf, tmsize_t size);

/**
 * @brief Pointer to seek function.
 * @param handle Client handle
 * @param offset Offset value
 * @param whence Seek directive
 * @returns New file offset
 */
typedef toff_t (*TIFFSeekProc)(thandle_t handle, toff_t offset, int whence);

/**
 * @brief Pointer to close function.
 * @param handle Client handle
 * @returns Status value
 */
typedef int (*TIFFCloseProc)(thandle_t handle);

/**
 * @brief Pointer to size function.
 * @param handle Client handle
 * @returns Client handle filesize in bytes
 */
typedef toff_t (*TIFFSizeProc)(thandle_t handle);

/**
 * @brief Pointer to memory map function.
 * @param handle Client handle
 * @param[out] base Pointer to the address of the mapped region
 * @param[out] size Pointer to the size of the mapped region
 * @returns Status value
 */
typedef int (*TIFFMapFileProc)(thandle_t handle, void** base, toff_t* size);

/**
 * @brief Pointer to memory unmap function.
 * @param handle Client handle
 * @param[out] base Address of the mapped region
 * @param[out] size Size of the mapped region
 * @returns Status value
 */
typedef void (*TIFFUnmapFileProc)(thandle_t handle, void* base, toff_t size);

/**
 * @brief Pointer to tag extender function.
 * @param tif TIFF file
 */
typedef void (*TIFFExtendProc)(TIFF* tif);

/**
 * @brief Get LibTIFF release version number as a string.
 * @return Version string
 */
extern const char* TIFFGetVersion(void);

/**
 * @brief Find a compression codec by number.
 * @details Search registered codecs, then built-in codecs.
 * @param scheme Compression codec scheme number
 * @return Pointer to compression codec, or NULL if the codec was not found
 */
extern const TIFFCodec* TIFFFindCODEC(uint16_t scheme);

/**
 * @brief Register a compression codec.
 * @param scheme Compression codec scheme number
 * @param name Compression codec name
 * @param init Initialisation function
 * @return Pointer to compression codec, or NULL if the codec could not be registered
 */
extern TIFFCodec* TIFFRegisterCODEC(uint16_t scheme, const char* name, TIFFInitMethod init);

/**
 * @brief Unregister a compression codec.
 * @param codec Codec to unregister
 */
extern void TIFFUnRegisterCODEC(TIFFCodec* codec);

/**
 * @brief Check if codec is functional.
 * @param scheme Compression codec scheme number
 * @return 1 if the codec is configured and working, otherwise 0.
 */
extern int TIFFIsCODECConfigured(uint16_t scheme);

/**
 * @brief Get list of configured codecs
 * @details The list includes both built-in codecs and codecs registered by the user.
 * @note The caller is responsible for freeing the returned structure, which
 * is a contiguous allocation containing all of the TIFFCodec records.  Free
 * with _TIFFfree.
 *
 * @return An array of TIFFCodec records (the last record is NULL)
 * or NULL if function failed.
 */
extern TIFFCodec* TIFFGetConfiguredCODECs(void);

/*
 * Memory functions.
 */

/**
 * Allocate memory.
 * @param s Size to allocate
 * @return Pointer to allocated memory, or NULL if allocation failed or s was 0.
 */
extern void* _TIFFmalloc(tmsize_t s);

/**
 * Allocate cleared memory.
 * @param nmemb Number of members
 * @param siz Size of each member
 * @return Pointer to allocated memory, or NULL if allocation failed or s was 0.
 */
extern void* _TIFFcalloc(tmsize_t nmemb, tmsize_t siz);

/**
 * Resize allocated memory.
 * @param p Pointer to existing allocation
 * @param s Size to reallocate; must be nonzero
 * @return Pointer to reallocated memory, or NULL if allocation failed.
 */
extern void* _TIFFrealloc(void* p, tmsize_t s);

/**
 * Set memory to value
 * @param p Pointer to object to fill
 * @param v Value to set
 * @param c Object size
 */
extern void _TIFFmemset(void* p, int v, tmsize_t c);

/**
 * Copy memory
 * @param d Destination object
 * @param s Source object
 * @param c Object size
 */
extern void _TIFFmemcpy(void* d, const void* s, tmsize_t c);

/**
 * @brief Compare memory
 * @details Lexicographical comparison of memory values
 * @param p1 First object
 * @param p2 Second object
 * @param c  Object size
 * @return <0 if p1 sorts before p2, >0 if p1 sorts after p2, 0 if p1 and p2 are identical
 */
extern int _TIFFmemcmp(const void* p1, const void* p2, tmsize_t c);

/**
 * Free allocated memory
 * @param p Pointer to allocated memory
 */
extern void _TIFFfree(void* p);

/**
 * @brief Get number of "custom" tags in the current directory.
 * @param tif TIFF file
 * @return Number of tags
 */
extern int TIFFGetTagListCount( TIFF * tif);

/**
 * @brief Get the TIFF tag number for a "custom" tag by index
 * @param tif TIFF file
 * @param tag_index "custom" tag index number
 * @return TIFF tag number, or -1 if the index was invalid
 */
extern uint32_t TIFFGetTagListEntry(TIFF * tif, int tag_index );

/** TIFF tag length is determined by field descriptor searching */
#define TIFF_ANY       TIFF_NOTYPE
/* TIFF tag length is variable length, stored as uint16_t */
#define TIFF_VARIABLE  -1
/* TIFF tag length is variable length, defined by SamplesPerPixel tag */
#define TIFF_SPP       -2
/* TIFF tag length is variable length, stored as uint32_t */
#define TIFF_VARIABLE2 -3

/** TIFFField custom bit */
#define FIELD_CUSTOM    65

/**
 * @brief TIFF Field structure.
 * @details This private structure defines the content of a TIFF field,
 * including the tag number, tag name, field type, read and write counts.
 */
typedef struct _TIFFField TIFFField;

/**
 * @brief Array of TIFF Field structures.
 * @details This private structure defines a collection of TIFF fields.
 */
typedef struct _TIFFFieldArray TIFFFieldArray;

/**
 * @brief Find field by tag number and datatype
 * @param tif TIFF file
 * @param tag Field tag number
 * @param dt Field data type
 * @return Field, or NULL if not found
 */
extern const TIFFField* TIFFFindField(TIFF *tif, uint32_t tag, TIFFDataType dt);

/**
 * @brief Find field by tag number
 * @details Will find any datatype and is equivalent to
 * TIFFFindField with TAG_ANY as the datatype.
 * @param tif TIFF file
 * @return Field, or NULL if not found
 */
extern const TIFFField* TIFFFieldWithTag(TIFF* tif, uint32_t tag);

/**
 * @brief Find field by tag name
 * @details Will find any datatype and is equivalent to
 * _TIFFFindFieldByName with TAG_ANY as the datatype.
 * @param tif TIFF file
 * @param field_name Field name to find
 * @return Field, or NULL if not found
 */
extern const TIFFField* TIFFFieldWithName(TIFF* tif, const char * field_name);

/**
 * @brief Get field tag number
 * @param fip Field information pointer
 * @return Field tag number
 */
extern uint32_t TIFFFieldTag(const TIFFField* fip);

/**
 * @brief Get field tag name
 * @param fip Field information pointer
 * @return Field tag name
 */
extern const char* TIFFFieldName(const TIFFField* fip);

/**
 * @brief Get field data type
 * @param fip Field information pointer
 * @return Field data type
 */
extern TIFFDataType TIFFFieldDataType(const TIFFField* fip);

/**
 * @brief Get field pass count
 * @param fip Field information pointer
 * @return Field pass count
 */
extern int TIFFFieldPassCount(const TIFFField* fip);

/**
 * @brief Get field read count
 * @param fip Field information pointer
 * @return Field read count
 */
extern int TIFFFieldReadCount(const TIFFField* fip);

/**
 * @brief Get field write count
 * @param fip Field information pointer
 * @return Field write count
 */
extern int TIFFFieldWriteCount(const TIFFField* fip);

/**
 * @brief Get field data type size
 * @details Internal storage size of field data type in bytes.
 * @param fip Field information pointer
 * @return Field data type size
 */

extern int TIFFFieldSetGetSize(const TIFFField* fip);

/**
 * @brief Get field data type count size
 * @details Size of count parameter 0=none, 2=uint16_t, 4=uint32_t
 * @param fip Field information pointer
 * @return Field data type count size
 */
extern int TIFFFieldSetGetCountSize(const TIFFField* fip);

/**
 * @brief Get field anonymous status
 * @param fip Field information pointer
 * @return Field anonymous status
 */
extern int TIFFFieldIsAnonymous(const TIFFField * fip);

/**
 * @brief Pointer to value setting function.
 * @param tif TIFF file
 * @param tag Field tag number
 * @param ap Value-setting arguments
 */
typedef int (*TIFFVSetMethod)(TIFF* tif, uint32_t tag, va_list ap);

/**
 * @brief Pointer to value getting function.
 * @param tif TIFF file
 * @param tag Field tag number
 * @param ap Value-getting arguments
 */
typedef int (*TIFFVGetMethod)(TIFF* tif, uint32_t tag, va_list ap);

/**
 * @brief Pointer to directory printing function.
 * @param tif TIFF file
 * @param file File handle to send formatted output to
 * @param flags Printing flags; @see TIFFPrintDirectory for details
 */
typedef void (*TIFFPrintMethod)(TIFF* tif, FILE* fd, long flags);

/**
 * @brief TIFF tag functions.
 */
typedef struct {
    TIFFVSetMethod vsetfield; /**< Tag set routine */
    TIFFVGetMethod vgetfield; /**< Tag get routine */
    TIFFPrintMethod printdir; /**< Directory print routine */
} TIFFTagMethods;

/**
 * @brief Get tag methods for TIFF file
 * @note The tag methods are not overridable by the user,
 * so there is no corresponding function to modify the
 * methods.
 * @param tif TIFF file
 * @return Pointer to the tag methods
 */
extern  TIFFTagMethods *TIFFAccessTagMethods(TIFF *tif);

/**
 * @brief Get client information
 * @details Retrieve a previously-stored item by name.
 * @param tif TIFF file
 * @param name Client information name
 * @return Pointer to client data, or NULL if name not found
 */
extern  void *TIFFGetClientInfo(TIFF *tif, const char *name);

/**
 * @brief Set client information
 * @details The name must be unique; if data has already been
 * stored with this name, it will be updated to use the new
 * data value.
 * @param tif TIFF file
 * @param name Client information name
 * @param data Client data
 */
extern  void TIFFSetClientInfo(TIFF *tif, void *name, const char *data);

/**
 * @brief Free the TIFF structure
 * @details The given structure will be completely freed, so ensure
 * the opened file handle and pointer to the close procedure are
 * saved in external variables before callingTIFFCleanup(), if you
 * will need this information to properly close the file.
 *
 * @param tif TIFF file
 */
extern void TIFFCleanup(TIFF* tif);

/**
 * @brief Close a previously opened TIFF file.
 * @details Close a file that was previously opened with TIFFOpen().
 * Any buffered data are flushed to the file, including the contents of
 * the current directory (if modified), and all resources are reclaimed.
 *
 * @param tif TIFF file
 */
extern void TIFFClose(TIFF* tif);

/**
 * @brief Flush pending changes to TIFF file.
 * @details This function will flush buffered data, update the strip
 * or tile arrays and rewrite the current directory.
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFFlush(TIFF* tif);

/**
 * @brief Flush pending image data writes to TIFF file.
 * @details Buffered data will be flushed to the TIFF file.
 * @note Frank Warmerdam'2000: I modified this to return 1 if
 * TIFF_BEENWRITING is not set, so that TIFFFlush() will proceed to
 * write out the directory.  The documentation says returning 1 is an
 * error indicator, but not having been writing isn't exactly a an
 * error.  Hopefully this doesn't cause problems for other people.
 *
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFFlushData(TIFF* tif);

/**
 * @brief Get field value
 * @details Get the value of a field in the internal directory structure.
 * The arguments required are tag-specific and may also depend upon
 * other field values, such as SamplesPerPixel.
 * @param tif TIFF file
 * @param tag Field tag number
 * @param ... Get arguments
 * @return 0 on error, 1 on success
 */
extern int TIFFGetField(TIFF* tif, uint32_t tag, ...);

/**
 * @brief Get field value (variable arguments)
 * @details Get the value of a field in the internal directory structure.
 * The arguments required are tag-specific and may also depend upon
 * other field values, such as SamplesPerPixel.
 * Like TIFFGetField, but taking a varargs
 * parameter list.  This routine is useful
 * for building higher-level interfaces on
 * top of the library.
 * @param tif TIFF file
 * @param tag Field tag number
 * @param va_list Get variable arguments
 * @return 0 on error, 1 on success
 */
extern int TIFFVGetField(TIFF* tif, uint32_t tag, va_list ap);

/**
 * @brief Get field value with default if unset
 * @details Get the value of a field in the internal directory structure.
 * The arguments required are tag-specific and may also depend upon
 * other field values, such as SamplesPerPixel.  If unset, the default
 * value for the field will be returned.
 * @param tif TIFF file
 * @param tag Field tag number
 * @param ... Get arguments
 * @return 0 on error, 1 on success
 */
extern int TIFFGetFieldDefaulted(TIFF* tif, uint32_t tag, ...);

/**
 * @brief Get field value with default if unset (variable arguments)
 * @details Get the value of a field in the internal directory structure.
 * The arguments required are tag-specific and may also depend upon
 * other field values, such as SamplesPerPixel.  If unset, the default
 * value for the field will be returned.
 * Like TIFFGetField, but taking a varargs
 * parameter list.  This routine is useful
 * for building higher-level interfaces on
 * top of the library.
 * @param tif TIFF file
 * @param tag Field tag number
 * @param va_list Get variable arguments
 * @return 0 on error, 1 on success
 */
extern int TIFFVGetFieldDefaulted(TIFF* tif, uint32_t tag, va_list ap);

/**
 * @brief Read the next TIFF directory
 * @details Read the next TIFF directory from a file and convert it to
 * the internal format. Directories are read sequentially.
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFReadDirectory(TIFF* tif);

/**
 * @brief Read TIFF directory (with custom fields)
 * @details Read custom TIFF directory from an arbitrary offset
 * and convert it into the internal format using custom fields.
 * Similar to TIFFReadDirectory().
 * @param tif TIFF file
 * @param diroff Offset into TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFReadCustomDirectory(TIFF* tif, toff_t diroff, const TIFFFieldArray* infoarray);

/**
 * @brief Read EXIF directory
 * @details Read EXIF directory from an arbitrary offset
 * and convert it into the internal format.
 * @note EXIF is an important special case of a custom directory.
 * @param tif TIFF file
 * @param diroff Offset into TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFReadEXIFDirectory(TIFF* tif, toff_t diroff);

/**
 * @brief Read EXIF-GPS directory
 * @details Read EXIF-GPS directory from an arbitrary offset
 * and convert it into the internal format.
 * @note EXIF-GPS is an important special case of a custom directory.
 * @param tif TIFF file
 * @param diroff Offset into TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFReadGPSDirectory(TIFF* tif, toff_t diroff);

/**
 * @brief Get size of scanline (unsigned 64-bit)
 * @details Get the number of bytes to read/write in a call to
 * one of the scanline-oriented I/O routines.  Note that
 * this number may be 1/SamplesPerPixel if the data is
 * stored as separate planes.
 * The ScanlineSize in case of YCbCrSubsampling is defined as the
 * strip size divided by the strip height, i.e. the size of a pack
 * of vertical subsampling lines divided by vertical subsampling.
 * It should thus make sense when multiplied by a multiple of
 * vertical subsampling.
 * @param tif TIFF file
 * @return Scanline size in bytes, or 0 on error
 */
extern uint64_t TIFFScanlineSize64(TIFF* tif);

/**
 * @brief Get size of scanline (signed integer)
 * @details Get the number of bytes to read/write in a call to
 * one of the scanline-oriented I/O routines.  Note that
 * this number may be 1/SamplesPerPixel if the data is
 * stored as separate planes.
 * The ScanlineSize in case of YCbCrSubsampling is defined as the
 * strip size divided by the strip height, i.e. the size of a pack
 * of vertical subsampling lines divided by vertical subsampling.
 * It should thus make sense when multiplied by a multiple of
 * vertical subsampling.
 * @param tif TIFF file
 * @return Scanline size in bytes, or 0 on error
 */
extern tmsize_t TIFFScanlineSize(TIFF* tif);

/**
 * @brief Get size of raster scanline (unsigned 64-bit)
 * @details Return the number of bytes required to store a complete
 * decoded and packed raster scanline (as opposed to the
 * I/O size returned by TIFFScanlineSize which may be less
 * if data is store as separate planes).
 * @param tif TIFF file
 * @return Raster scanline size in bytes, or 0 on error
 */
extern uint64_t TIFFRasterScanlineSize64(TIFF* tif);

/**
 * @brief Get size of raster scanline (signed integer)
 * @details Return the number of bytes required to store a complete
 * decoded and packed raster scanline (as opposed to the
 * I/O size returned by TIFFScanlineSize which may be less
 * if data is store as separate planes).
 * @param tif TIFF file
 * @return Raster scanline size in bytes, or 0 on error
 */
extern tmsize_t TIFFRasterScanlineSize(TIFF* tif);


/**
 * @brief Get size of a strip (unsigned 64-bit)
 * @details Get the number of bytes in a row-aligned strip.
 * @note If RowsPerStrip is larger than the
 * recorded ImageLength, then the strip size is
 * truncated to reflect the actual space required
 * to hold the strip.
 * @param tif TIFF file
 * @return Strip size in bytes, or 0 on error
 */
extern uint64_t TIFFStripSize64(TIFF* tif);

/**
 * @brief Get size of a strip (signed integer)
 * @details Get the number of bytes in a row-aligned strip.
 * @note If RowsPerStrip is larger than the
 * recorded ImageLength, then the strip size is
 * truncated to reflect the actual space required
 * to hold the strip.
 * @param tif TIFF file
 * @return Strip size in bytes, or 0 on error
 */
extern tmsize_t TIFFStripSize(TIFF* tif);

/**
 * @brief Get "raw" size of a strip (unsigned 64-bit)
 * @details Get the number of bytes in a row-aligned strip.
 * @note "Raw" means the size of a strip which has not been
 * decoded.
 * @param tif TIFF file
 * @return Strip size in bytes, or 0 on error
 */
extern uint64_t TIFFRawStripSize64(TIFF* tif, uint32_t strip);

/**
 * @brief Get "raw" size of a strip (signed integer)
 * @details Get the number of bytes in a row-aligned strip.
 * @note "Raw" means the size of a strip which has not been
 * decoded.
 * @param tif TIFF file
 * @return Strip size in bytes, or 0 on error
 */
extern tmsize_t TIFFRawStripSize(TIFF* tif, uint32_t strip);

/**
 * @brief Get size of a strip with variable row count (unsigned 64-bit)
 * @details Get the number of bytes in a row-aligned strip with the
 * specified row count.
 * @note If RowsPerStrip is larger than the
 * recorded ImageLength, then the strip size is
 * truncated to reflect the actual space required
 * to hold the strip.
 * @param tif TIFF file
 * @param nrows Row count
 * @return Strip size in bytes, or 0 on error
 */
extern uint64_t TIFFVStripSize64(TIFF* tif, uint32_t nrows);

/**
 * @brief Get size of a strip with variable row count (signed integer)
 * @details Get the number of bytes in a row-aligned strip with the
 * specified row count.
 * @note If RowsPerStrip is larger than the
 * recorded ImageLength, then the strip size is
 * truncated to reflect the actual space required
 * to hold the strip.
 * @param tif TIFF file
 * @param nrows Row count
 * @return Strip size in bytes, or 0 on error
 */
extern tmsize_t TIFFVStripSize(TIFF* tif, uint32_t nrows);

/**
 * @brief Get size of each row of a tile (unsigned 64-bit)
 * @details Get the number of bytes in each row of a tile.
 * @param tif TIFF file
 * @return Row size in bytes, or 0 on error
 */
extern uint64_t TIFFTileRowSize64(TIFF* tif);

/**
 * @brief Get size of each row of a tile (signed integer)
 * @details Get the number of bytes in each row of a tile.
 * @param tif TIFF file
 * @return Row size in bytes, or 0 on error
 */
extern tmsize_t TIFFTileRowSize(TIFF* tif);

/**
 * @brief Get size of a tile (unsigned 64-bit)
 * @details Get the number of bytes in a row-aligned tile.
 * @param tif TIFF file
 * @return Row size in bytes, or 0 on error
 */
extern uint64_t TIFFTileSize64(TIFF* tif);

/**
 * @brief Get size of a tile (signed integer)
 * @details Get the number of bytes in a row-aligned tile.
 * @param tif TIFF file
 * @return Row size in bytes, or 0 on error
 */
extern tmsize_t TIFFTileSize(TIFF* tif);

/**
 * @brief Get size of a tile with variable row count (unsigned 64-bit)
 * @details Get the number of bytes in a row-aligned tile
 * with the specified row count.
 * @param tif TIFF file
 * @param nrows Row count
 * @return Row size in bytes, or 0 on error
 */
extern uint64_t TIFFVTileSize64(TIFF* tif, uint32_t nrows);

/**
 * @brief Get size of a tile with variable row count (signed integer)
 * @details Get the number of bytes in a row-aligned tile
 * with the specified row count.
 * @param tif TIFF file
 * @param nrows Row count
 * @return Row size in bytes, or 0 on error
 */
extern tmsize_t TIFFVTileSize(TIFF* tif, uint32_t nrows);

/**
 * @brief Get default strip size for current directory
 * @details Get the default strip size based upon the image
 * characteristics and a requested value.  If the
 * request is <1, choose a strip size according
 * to certain heuristics.
 * @param tif TIFF file
 * @param request Requested size.  Set to <1 to compute default size.
 * @return Computed strip size if request value was <1, or else request value.
 */
extern uint32_t TIFFDefaultStripSize(TIFF* tif, uint32_t request);

/**
 * @brief Get default tile size for current directory
 * @details Get the default tile size based on the image
 * characteristics.  If the tw or th requests are <1,
 * choose a size according to certain heuristics.
 * @param tif TIFF file
 * @param[inout] tw Tile width; must be desired width or <1 to compute
 * @param[inout] th Tile height; must be desired width or <1 to compute
 */
extern void TIFFDefaultTileSize(TIFF* tif, uint32_t* tw, uint32_t* th);

/**
 * @brief Get file descriptor for open TIFF file.
 * @param tif TIFF file
 * @return file descriptor number
 */
extern int TIFFFileno(TIFF* tif);

/**
 * @brief Change file descriptor for open TIFF file.
 * @param tif TIFF file
 * @param fd File descriptor number
 * @return Previous file descriptor value
 */
extern int TIFFSetFileno(TIFF* tif, int fd);

/**
 * @brief Get client data for open TIFF file.
 * @param tif TIFF file
 * @return Client data
 */
extern thandle_t TIFFClientdata(TIFF* tif);

/**
 * @brief Set client data for open TIFF file.
 * @param tif TIFF file
 * @param newvalue New client data value
 * @return Old client data
 */
extern thandle_t TIFFSetClientdata(TIFF* tif, thandle_t newvalue);

/**
 * @brief Get read/write mode for open TIFF file.
 * @param tif TIFF file
 * @return Read/write mode
 */
extern int TIFFGetMode(TIFF* tif);

/**
 * @brief Set read/write mode for open TIFF file.
 * @param tif TIFF file
 * @param mode New read/write mode
 * @return Old read/write mode
 */
extern int TIFFSetMode(TIFF* tif, int mode);

/**
 * @brief Check if current TIFF directory is tiled.
 * @param tif TIFF file.
 * @return 0 if strips; nonzero if tiles
 */
extern int TIFFIsTiled(TIFF* tif);

/**
 * @brief Check if current TIFF file is byte-swapped.
 * @param tif TIFF file.
 * @return 0 not byte-swapped; nonzero if byte-swapped
 */
extern int TIFFIsByteSwapped(TIFF* tif);

/**
 * @brief Check if current TIFF directory is up-sampled.
 * @param tif TIFF file.
 * @return 0 if not upsampled; nonzero if up-sampled.
 */
extern int TIFFIsUpSampled(TIFF* tif);

/**
 * @brief Check if current TIFF directory is MSB-to-LSB bit order.
 * @param tif TIFF file.
 * @return 0 if LSB-to-MSB; nonzero if MSB-to-LSB.
 */
extern int TIFFIsMSB2LSB(TIFF* tif);

/**
 * @brief Check if current TIFF file is big-endian.
 * @param tif TIFF file.
 * @return 0 if little-endian; nonzero if big-endian.
 */
extern int TIFFIsBigEndian(TIFF* tif);

/**
 * @brief Check if current TIFF file is a BigTIFF format TIFF.
 * @param tif TIFF file.
 * @return 0 if standard TIFF; nonzero if BigTIFF..
 */
extern int TIFFIsBigTIFF(TIFF* tif);

/**
 * Get file read method for TIFF file.
 * @param tif TIFF file.
 * @return File read method
 */
extern TIFFReadWriteProc TIFFGetReadProc(TIFF* tif);

/**
 * Get file write method for TIFF file.
 * @param tif TIFF file.
 * @return File write method
 */
extern TIFFReadWriteProc TIFFGetWriteProc(TIFF* tif);

/**
 * Get file seek method for TIFF file.
 * @param tif TIFF file.
 * @return File seek method
 */
extern TIFFSeekProc TIFFGetSeekProc(TIFF* tif);

/**
 * Get file close method for TIFF file.
 * @param tif TIFF file.
 * @return File close method
 */
extern TIFFCloseProc TIFFGetCloseProc(TIFF* tif);

/**
 * Get file size method for TIFF file.
 * @param tif TIFF file.
 * @return File size method
 */
extern TIFFSizeProc TIFFGetSizeProc(TIFF* tif);

/**
 * Get file memory map method for TIFF file.
 * @param tif TIFF file.
 * @return File memory map method
 */
extern TIFFMapFileProc TIFFGetMapFileProc(TIFF* tif);

/**
 * Get file memory unmap method for TIFF file.
 * @param tif TIFF file.
 * @return File memory unmap method
 */
extern TIFFUnmapFileProc TIFFGetUnmapFileProc(TIFF* tif);

/**
 * Get current row index being written
 * @param tif TIFF file.
 * @return Current row index.
 */
extern uint32_t TIFFCurrentRow(TIFF* tif);

/**
 * Get current directory index
 * @param tif TIFF file.
 * @return Current directory index
 */
extern uint16_t TIFFCurrentDirectory(TIFF* tif);

/**
 * Get the total number of directories in a file
 * @param tif TIFF file.
 * @return Directory count
 */
extern uint16_t TIFFNumberOfDirectories(TIFF* tif);

/**
 * Get file offset of the current directory.
 * @param tif TIFF file.
 * @return File offset
 */
extern uint64_t TIFFCurrentDirOffset(TIFF* tif);

/**
 * Get current strip index.
 * @param tif
 * @return Strip index
 */
extern uint32_t TIFFCurrentStrip(TIFF* tif);

/**
 * Get current tile index.
 * @param tif
 * @return tile index
 */
extern uint32_t TIFFCurrentTile(TIFF* tif);

/**
 * @brief Set up raw read buffer.
 * @details Set up the raw data buffer in preparation for
 * reading a strip of raw data.  If the buffer
 * is specified as NULL, then a buffer of appropriate
 * size is allocated by the library.  Otherwise,
 * the client must guarantee that the buffer is
 * large enough to hold any individual strip of
 * raw data.
 * @param tif TIFF file
 * @param bp Pointer to buffer; NULL to allocate automatically
 * @param size Size of buffer; only used if bp is not NULL
 * @return 0 on error, 1 on success
 */
extern int TIFFReadBufferSetup(TIFF* tif, void* bp, tmsize_t size);

/**
 * @brief Set up raw write buffer.
 * @details Set up the raw data buffer in preparation for
 * writing a strip of raw data.  If the size is specified as -1,
 * then a buffer of appropriate size is allocated by the library
 * (bp is ignored).
 * If bp is NULL, a buffer of the specified size will be allocated.
 * Otherwise, bp and size will be used as specified;
 * the client must guarantee that the buffer is
 * large enough to hold any individual strip of
 * raw data.
 * @param tif TIFF file
 * @param bp Pointer to buffer; NULL to allocate automatically
 * @param size Size of buffer; only used if bp is not -1 and not NULL
 * @return 0 on error, 1 on success
 */
extern int TIFFWriteBufferSetup(TIFF* tif, void* bp, tmsize_t size);

/**
 * @brief Set up directory for strip or tile reading and writing
 * @details Compute number of strips or tiles, and allocate space
 * for storing the per-strip or per-tile offsets and byte counts.
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFSetupStrips(TIFF* tif);

/**
 * @brief Check if set up properly for writing
 * @details Verify file is writable and that the directory
 * information is setup properly.  In doing the latter
 * we also "freeze" the state of the directory so
 * that important information is not changed.
 * @param tif TIFF file
 * @param tiles 1 to check if writing tiles, 0 to check if writing strips
 * @param module Module name (for error reporting)
 * @return 0 on error, 1 on success
 */
extern int TIFFWriteCheck(TIFF* tif, int tiles, const char * module);

/**
 * @brief Release storage associated with a directory.
 * @param tif TIFF file
 */
extern void TIFFFreeDirectory(TIFF* tif);

/**
 * @brief Create new directory
 * @details Set up for a new directory.
 * The newly created directory will not exist in the file until
 * one of TIFFWriteDirectory(), TIFFFlush() or TIFFClose() is called.
 *
 * @todo Should we automatically call
 * TIFFWriteDirectory() if the current one is dirty?  Or fail?
 *
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFCreateDirectory(TIFF* tif);

/**
 * @brief Create new custom directory
 * @details In addition to the default setup performed by
 * TIFFCreateDirectory, additionally set up the custom fields
 * specified in the provided field array.
 * @param tif TIFF file
 * @param infoarray Field array
 * @return 0 on error, 1 on success
 */
extern int TIFFCreateCustomDirectory(TIFF* tif,const TIFFFieldArray* infoarray);

/**
 * Create a new EXIF directory
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFCreateEXIFDirectory(TIFF* tif);

/**
 * Create a new EXIF-GPS directory
 * @param tif TIFF file
 * @return 0 on error, 1 on success
 */
extern int TIFFCreateGPSDirectory(TIFF* tif);

/**
 * @brief Check if current directory is the last directory
 * @param tif TIFF file
 * @return 1 if the last directory, otherwise 0
 */
extern int TIFFLastDirectory(TIFF* tif);

/**
 * @brief Set current directory by directory index
 * @details Set current directory to be the n-th directory
 * in the file.
 * @note Directories are numbered starting at 0.
 * @param tif TIFF file
 * @param dirn Directory index
 * @return 0 on error, 1 on success
 */
extern int TIFFSetDirectory(TIFF* tif, uint16_t dirn);

/**
 * @brief Set current directory by directory offset in file
 * @details Set the current directory to be the directory
 * located at the specified file offset.  This interface
 * is used mainly to access directories linked with
 * the SubIFD tag (e.g. thumbnail images).
 * @param tif TIFF file
 * @param diroff Directory offset
 * @return 0 on error, 1 on success
 */
extern int TIFFSetSubDirectory(TIFF* tif, uint64_t diroff);

extern int TIFFUnlinkDirectory(TIFF* tif, uint16_t);
extern int TIFFSetField(TIFF* tif, uint32_t, ...);
extern int TIFFVSetField(TIFF* tif, uint32_t, va_list);
extern int TIFFUnsetField(TIFF* tif, uint32_t);
extern int TIFFWriteDirectory(TIFF * tif);
extern int TIFFWriteCustomDirectory(TIFF * tif, uint64_t *);
extern int TIFFCheckpointDirectory(TIFF * tif);
extern int TIFFRewriteDirectory(TIFF * tif);
extern int TIFFDeferStrileArrayWriting(TIFF* tif);
extern int TIFFForceStrileArrayWriting(TIFF* tif);

#if defined(c_plusplus) || defined(__cplusplus)
extern void TIFFPrintDirectory(TIFF*, FILE*, long = 0);
extern int TIFFReadScanline(TIFF* tif, void* buf, uint32_t row, uint16_t sample = 0);
extern int TIFFWriteScanline(TIFF* tif, void* buf, uint32_t row, uint16_t sample = 0);
extern int TIFFReadRGBAImage(TIFF*, uint32_t, uint32_t, uint32_t*, int = 0);
extern int TIFFReadRGBAImageOriented(TIFF*, uint32_t, uint32_t, uint32_t*,
    int = ORIENTATION_BOTLEFT, int = 0);
#else
extern void TIFFPrintDirectory(TIFF*, FILE*, long);
extern int TIFFReadScanline(TIFF* tif, void* buf, uint32_t row, uint16_t sample);
extern int TIFFWriteScanline(TIFF* tif, void* buf, uint32_t row, uint16_t sample);
extern int TIFFReadRGBAImage(TIFF*, uint32_t, uint32_t, uint32_t*, int);
extern int TIFFReadRGBAImageOriented(TIFF*, uint32_t, uint32_t, uint32_t*, int, int);
#endif

extern int TIFFReadRGBAStrip(TIFF*, uint32_t, uint32_t * );
extern int TIFFReadRGBATile(TIFF*, uint32_t, uint32_t, uint32_t * );
extern int TIFFReadRGBAStripExt(TIFF*, uint32_t, uint32_t *, int stop_on_error );
extern int TIFFReadRGBATileExt(TIFF*, uint32_t, uint32_t, uint32_t *, int stop_on_error );
extern int TIFFRGBAImageOK(TIFF*, char [1024]);
extern int TIFFRGBAImageBegin(TIFFRGBAImage*, TIFF*, int, char [1024]);
extern int TIFFRGBAImageGet(TIFFRGBAImage*, uint32_t*, uint32_t, uint32_t);
extern void TIFFRGBAImageEnd(TIFFRGBAImage*);

/**
 * @brief Open a TIFF file for reading or writing.
 * @param name The filename of the file to open
 * @param mode THe open mode of the file
 * @return The opened TIFF file, or NULL if opening failed
 */
extern TIFF* TIFFOpen(const char* name, const char* mode);

# ifdef __WIN32__
extern TIFF* TIFFOpenW(const wchar_t*, const char*);
# endif /* __WIN32__ */
extern TIFF* TIFFFdOpen(int, const char*, const char*);
extern TIFF* TIFFClientOpen(const char*, const char*,
	    thandle_t,
	    TIFFReadWriteProc, TIFFReadWriteProc,
	    TIFFSeekProc, TIFFCloseProc,
	    TIFFSizeProc,
	    TIFFMapFileProc, TIFFUnmapFileProc);
extern const char* TIFFFileName(TIFF*);
extern const char* TIFFSetFileName(TIFF*, const char *);
extern void TIFFError(const char*, const char*, ...) TIFF_ATTRIBUTE((__format__ (__printf__,2,3)));
extern void TIFFErrorExt(thandle_t, const char*, const char*, ...) TIFF_ATTRIBUTE((__format__ (__printf__,3,4)));
extern void TIFFWarning(const char*, const char*, ...) TIFF_ATTRIBUTE((__format__ (__printf__,2,3)));
extern void TIFFWarningExt(thandle_t, const char*, const char*, ...) TIFF_ATTRIBUTE((__format__ (__printf__,3,4)));
extern TIFFErrorHandler TIFFSetErrorHandler(TIFFErrorHandler);
extern TIFFErrorHandlerExt TIFFSetErrorHandlerExt(TIFFErrorHandlerExt);
extern TIFFErrorHandler TIFFSetWarningHandler(TIFFErrorHandler);
extern TIFFErrorHandlerExt TIFFSetWarningHandlerExt(TIFFErrorHandlerExt);
extern TIFFExtendProc TIFFSetTagExtender(TIFFExtendProc);
extern uint32_t TIFFComputeTile(TIFF* tif, uint32_t x, uint32_t y, uint32_t z, uint16_t s);
extern int TIFFCheckTile(TIFF* tif, uint32_t x, uint32_t y, uint32_t z, uint16_t s);
extern uint32_t TIFFNumberOfTiles(TIFF*);
extern tmsize_t TIFFReadTile(TIFF* tif, void* buf, uint32_t x, uint32_t y, uint32_t z, uint16_t s);
extern tmsize_t TIFFWriteTile(TIFF* tif, void* buf, uint32_t x, uint32_t y, uint32_t z, uint16_t s);
extern uint32_t TIFFComputeStrip(TIFF*, uint32_t, uint16_t);
extern uint32_t TIFFNumberOfStrips(TIFF*);
extern tmsize_t TIFFReadEncodedStrip(TIFF* tif, uint32_t strip, void* buf, tmsize_t size);
extern tmsize_t TIFFReadRawStrip(TIFF* tif, uint32_t strip, void* buf, tmsize_t size);
extern tmsize_t TIFFReadEncodedTile(TIFF* tif, uint32_t tile, void* buf, tmsize_t size);
extern tmsize_t TIFFReadRawTile(TIFF* tif, uint32_t tile, void* buf, tmsize_t size);
extern int      TIFFReadFromUserBuffer(TIFF* tif, uint32_t strile,
                                       void* inbuf, tmsize_t insize,
                                       void* outbuf, tmsize_t outsize);
extern tmsize_t TIFFWriteEncodedStrip(TIFF* tif, uint32_t strip, void* data, tmsize_t cc);
extern tmsize_t TIFFWriteRawStrip(TIFF* tif, uint32_t strip, void* data, tmsize_t cc);
extern tmsize_t TIFFWriteEncodedTile(TIFF* tif, uint32_t tile, void* data, tmsize_t cc);
extern tmsize_t TIFFWriteRawTile(TIFF* tif, uint32_t tile, void* data, tmsize_t cc);
extern int TIFFDataWidth(TIFFDataType);    /* table of tag datatype widths within TIFF file. */
extern void TIFFSetWriteOffset(TIFF* tif, toff_t off);
extern void TIFFSwabShort(uint16_t*);
extern void TIFFSwabLong(uint32_t*);
extern void TIFFSwabLong8(uint64_t*);
extern void TIFFSwabFloat(float*);
extern void TIFFSwabDouble(double*);
extern void TIFFSwabArrayOfShort(uint16_t* wp, tmsize_t n);
extern void TIFFSwabArrayOfTriples(uint8_t* tp, tmsize_t n);
extern void TIFFSwabArrayOfLong(uint32_t* lp, tmsize_t n);
extern void TIFFSwabArrayOfLong8(uint64_t* lp, tmsize_t n);
extern void TIFFSwabArrayOfFloat(float* fp, tmsize_t n);
extern void TIFFSwabArrayOfDouble(double* dp, tmsize_t n);
extern void TIFFReverseBits(uint8_t* cp, tmsize_t n);
extern const unsigned char* TIFFGetBitRevTable(int);

extern uint64_t TIFFGetStrileOffset(TIFF *tif, uint32_t strile);
extern uint64_t TIFFGetStrileByteCount(TIFF *tif, uint32_t strile);
extern uint64_t TIFFGetStrileOffsetWithErr(TIFF *tif, uint32_t strile, int *pbErr);
extern uint64_t TIFFGetStrileByteCountWithErr(TIFF *tif, uint32_t strile, int *pbErr);

#ifdef LOGLUV_PUBLIC
#define U_NEU		0.210526316
#define V_NEU		0.473684211
#define UVSCALE		410.
extern double LogL16toY(int);
extern double LogL10toY(int);
extern void XYZtoRGB24(float*, uint8_t*);
extern int uv_decode(double*, double*, int);
extern void LogLuv24toXYZ(uint32_t, float*);
extern void LogLuv32toXYZ(uint32_t, float*);
#if defined(c_plusplus) || defined(__cplusplus)
extern int LogL16fromY(double, int = SGILOGENCODE_NODITHER);
extern int LogL10fromY(double, int = SGILOGENCODE_NODITHER);
extern int uv_encode(double, double, int = SGILOGENCODE_NODITHER);
extern uint32_t LogLuv24fromXYZ(float*, int = SGILOGENCODE_NODITHER);
extern uint32_t LogLuv32fromXYZ(float*, int = SGILOGENCODE_NODITHER);
#else
extern int LogL16fromY(double, int);
extern int LogL10fromY(double, int);
extern int uv_encode(double, double, int);
extern uint32_t LogLuv24fromXYZ(float*, int);
extern uint32_t LogLuv32fromXYZ(float*, int);
#endif
#endif /* LOGLUV_PUBLIC */

extern int TIFFCIELabToRGBInit(TIFFCIELabToRGB*, const TIFFDisplay *, float*);
extern void TIFFCIELabToXYZ(TIFFCIELabToRGB *, uint32_t, int32_t, int32_t,
                            float *, float *, float *);
extern void TIFFXYZToRGB(TIFFCIELabToRGB *, float, float, float,
                         uint32_t *, uint32_t *, uint32_t *);

extern int TIFFYCbCrToRGBInit(TIFFYCbCrToRGB*, float*, float*);
extern void TIFFYCbCrtoRGB(TIFFYCbCrToRGB *, uint32_t, int32_t, int32_t,
                           uint32_t *, uint32_t *, uint32_t *);

/****************************************************************************
 *               O B S O L E T E D    I N T E R F A C E S
 *
 * Don't use this stuff in your applications, it may be removed in the future
 * libtiff versions.
 ****************************************************************************/

/**
 * @brief TIFF field description (obsolete)
 * @see TIFField
 * @deprecated Use TIFFField and associated functions instead.
 */
typedef	struct {
	ttag_t	field_tag;		/**< field's tag */
	short	field_readcount;	/**< read count/TIFF_VARIABLE/TIFF_SPP */
	short	field_writecount;	/**< write count/TIFF_VARIABLE */
	TIFFDataType field_type;	/**< type of associated data */
        unsigned short field_bit;	/**< bit in field's set bit vector */
	unsigned char field_oktochange;	/**< if true, can change while writing */
	unsigned char field_passcount;	/**< if true, pass dir count on set */
	char	*field_name;		/**< ASCII name */
} TIFFFieldInfo;

/**
 * Merge custom TIFF field definitions for use with current TIFF file
 * @see TIFField
 * @deprecated Use TIFFField and associated functions instead.
 * @todo Add example and references for replacement functionality.
 * @param tif TIFF file
 * @param info Array of field definitions
 * @param n Number of field definitions in array
 * @return 0 on success, -1 on failure
 */
extern int TIFFMergeFieldInfo(TIFF* tif, const TIFFFieldInfo info[], uint32_t n);
        
#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

#endif /* _TIFFIO_ */

/* vim: set ts=8 sts=8 sw=8 noet: */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */
