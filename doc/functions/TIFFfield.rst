TIFFfield
=========

Synopsis
--------

.. highlight:: c

::

    #include <tiffio.h>

.. c:struct:: TIFFField

.. c:function:: const TIFFField* TIFFFindField(TIFF* tif, uint32_t tag, TIFFDataType dt)

.. c:function:: const TIFFField* TIFFFindFieldByName(TIFF* tif, const char* field_name, TIFFDataType dt)

.. c:function:: const TIFFField* TIFFFieldWithTag(TIFF* tif, uint32_t tag)

.. c:function:: TIFFField* TIFFFieldWithName(TIFF*tif, const char *field_name)

Description
-----------

The specific information about TIFF tags may be queried using several functions.
:c:func:`TIFFFindField` may be used to find a field using the tag number and a specific data type.  Use
:c:macro:`TIFF_ANY` to find any type.  This is necessary because some tags support use of multiple
datatypes.  :c:func:`TIFFFieldWithTag` is a convenience wrapper function which performs the same
task as :c:func:`TIFFFindField` but sets the datatype to :c:macro:`TIFF_ANY`.

:c:func:`TIFFFindFieldByName` and :c:func:`TIFFFieldWithName` perform the same duties, but
use the field name rather than the tag identifier.

Details of the tags supported by LibTIFF are provided in the following sections.

Baseline TIFF tags
------------------

.. c:macro:: TIFFTAG_SUBFILETYPE

    subfile data descriptor 

The follwing subfile types are supported:

    .. c:macro:: FILETYPE_REDUCEDIMAGE

        reduced resolution version

    .. c:macro:: FILETYPE_PAGE

        one page of many

    .. c:macro:: FILETYPE_MASK

        transparency mask

.. c:macro:: TIFFTAG_OSUBFILETYPE

    +kind of data in subfile 

The following old subfile types are supported:

    .. c:macro:: OFILETYPE_IMAGE

        full resolution image data

    .. c:macro:: OFILETYPE_REDUCEDIMAGE

        reduced size image data

    .. c:macro:: OFILETYPE_PAGE

        one page of many

.. c:macro:: TIFFTAG_IMAGEWIDTH

    image width in pixels 

.. c:macro:: TIFFTAG_IMAGELENGTH

    image height in pixels 

.. c:macro:: TIFFTAG_BITSPERSAMPLE

    bits per channel (sample) 

.. c:macro:: TIFFTAG_COMPRESSION

    data compression technique 

The following compression types are supported:

    .. c:macro:: COMPRESSION_NONE

        dump mode

    .. c:macro:: COMPRESSION_CCITTRLE

        CCITT modified Huffman RLE

    .. c:macro:: COMPRESSION_CCITTFAX3

        CCITT Group 3 fax encoding

    .. c:macro:: COMPRESSION_CCITT_T4

        CCITT T.4 (TIFF 6 name)

    .. c:macro:: COMPRESSION_CCITTFAX4

        CCITT Group 4 fax encoding

    .. c:macro:: COMPRESSION_CCITT_T6

        CCITT T.6 (TIFF 6 name)

    .. c:macro:: COMPRESSION_LZW

        Lempel-Ziv  & Welch

    .. c:macro:: COMPRESSION_OJPEG

        !6.0 JPEG

    .. c:macro:: COMPRESSION_JPEG

        %JPEG DCT compression

    .. c:macro:: COMPRESSION_T85

        !TIFF/FX T.85 JBIG compression

    .. c:macro:: COMPRESSION_T43

        !TIFF/FX T.43 colour by layered JBIG compression

    .. c:macro:: COMPRESSION_NEXT

        NeXT 2-bit RLE

    .. c:macro:: COMPRESSION_CCITTRLEW

        #1 w/ word alignment

    .. c:macro:: COMPRESSION_PACKBITS

        Macintosh RLE

    .. c:macro:: COMPRESSION_THUNDERSCAN

        ThunderScan RLE

    codes 32895-32898 are reserved for ANSI IT8 TIFF/IT <dkelly@apago.com)

    .. c:macro:: COMPRESSION_IT8CTPAD

        IT8 CT w/padding

    .. c:macro:: COMPRESSION_IT8LW

        IT8 Linework RLE

    .. c:macro:: COMPRESSION_IT8MP

        IT8 Monochrome picture

    .. c:macro:: COMPRESSION_IT8BL

        IT8 Binary line art

    compression codes 32908-32911 are reserved for Pixar

    .. c:macro:: COMPRESSION_PIXARFILM

        Pixar companded 10bit LZW

    .. c:macro:: COMPRESSION_PIXARLOG

        Pixar companded 11bit ZIP

    .. c:macro:: COMPRESSION_DEFLATE

        Deflate compression, legacy tag

    .. c:macro:: COMPRESSION_ADOBE_DEFLATE

        Deflate compression, as recognized by Adobe

    compression code 32947 is reserved for Oceana Matrix <dev@oceana.com>

    .. c:macro:: COMPRESSION_DCS

        Kodak DCS encoding

    .. c:macro:: COMPRESSION_JBIG

        ISO JBIG

    .. c:macro:: COMPRESSION_SGILOG

        SGI Log Luminance RLE

    .. c:macro:: COMPRESSION_SGILOG24

        SGI Log 24-bit packed

    .. c:macro:: COMPRESSION_JP2000

        Leadtools JPEG2000

    .. c:macro:: COMPRESSION_LERC

        ESRI Lerc codec: https://github.com/Esri/lerc

    compression codes 34887-34889 are reserved for ESRI

    .. c:macro:: COMPRESSION_LZMA

        LZMA2

    .. c:macro:: COMPRESSION_ZSTD

        ZSTD: WARNING not registered in Adobe-maintained registry

    .. c:macro:: COMPRESSION_WEBP

        WEBP: WARNING not registered in Adobe-maintained registry

    .. c:macro:: COMPRESSION_JXL

        JPEGXL: WARNING not registered in Adobe-maintained registry

.. c:macro:: TIFFTAG_PHOTOMETRIC

    photometric interpretation 

The following photometric interpretations are supported:

    .. c:macro:: PHOTOMETRIC_MINISWHITE

        min value is white

    .. c:macro:: PHOTOMETRIC_MINISBLACK

        min value is black

    .. c:macro:: PHOTOMETRIC_RGB

        RGB color model

    .. c:macro:: PHOTOMETRIC_PALETTE

        color map indexed

    .. c:macro:: PHOTOMETRIC_MASK

        $holdout mask

    .. c:macro:: PHOTOMETRIC_SEPARATED

        !color separations

    .. c:macro:: PHOTOMETRIC_YCBCR

        !CCIR 601

    .. c:macro:: PHOTOMETRIC_CIELAB

        !1976 CIE L*a*b*

    .. c:macro:: PHOTOMETRIC_ICCLAB

        ICC L*a*b* [Adobe TIFF Technote 4]

    .. c:macro:: PHOTOMETRIC_ITULAB

        ITU L*a*b*

    .. c:macro:: PHOTOMETRIC_CFA

        color filter array

    .. c:macro:: PHOTOMETRIC_LOGL

        CIE Log2(L)

    .. c:macro:: PHOTOMETRIC_LOGLUV

        CIE Log2(L) (u',v')

.. c:macro:: TIFFTAG_THRESHHOLDING

    +thresholding used on data 

The following thresholding modes are supported:

    .. c:macro:: THRESHHOLD_BILEVEL

        b&w art scan

    .. c:macro:: THRESHHOLD_HALFTONE

        or dithered scan

    .. c:macro:: THRESHHOLD_ERRORDIFFUSE

        usually floyd-steinberg

.. c:macro:: TIFFTAG_CELLWIDTH

    +dithering matrix width 

.. c:macro:: TIFFTAG_CELLLENGTH

    +dithering matrix height 

.. c:macro:: TIFFTAG_FILLORDER

    data order within a byte 

The following fill orders are supported:

    .. c:macro:: FILLORDER_MSB2LSB

        most significant to least significant

    .. c:macro:: FILLORDER_LSB2MSB

        least significant to most significant

.. c:macro:: TIFFTAG_DOCUMENTNAME

    name of doc. image is from 

.. c:macro:: TIFFTAG_IMAGEDESCRIPTION

    info about image 

.. c:macro:: TIFFTAG_MAKE

    scanner manufacturer name 

.. c:macro:: TIFFTAG_MODEL

    scanner model name/number 

.. c:macro:: TIFFTAG_STRIPOFFSETS

    offsets to data strips 

.. c:macro:: TIFFTAG_ORIENTATION

    Image orientation 

The following orientations are supported:

    .. c:macro:: ORIENTATION_TOPLEFT
    
        row 0 top, col 0 lhs
    
    .. c:macro:: ORIENTATION_TOPRIGHT
    
        row 0 top, col 0 rhs
    
    .. c:macro:: ORIENTATION_BOTRIGHT
    
        row 0 bottom, col 0 rhs
    
    .. c:macro:: ORIENTATION_BOTLEFT
    
        row 0 bottom, col 0 lhs
    
    .. c:macro:: ORIENTATION_LEFTTOP
    
        row 0 lhs, col 0 top
    
    .. c:macro:: ORIENTATION_RIGHTTOP
    
        row 0 rhs, col 0 top
    
    .. c:macro:: ORIENTATION_RIGHTBOT
    
        row 0 rhs, col 0 bottom
    
    .. c:macro:: ORIENTATION_LEFTBOT
    
        row 0 lhs, col 0 bottom
    
.. c:macro:: TIFFTAG_SAMPLESPERPIXEL

    samples per pixel 

.. c:macro:: TIFFTAG_ROWSPERSTRIP

    rows per strip of data 

.. c:macro:: TIFFTAG_STRIPBYTECOUNTS

    bytes counts for strips 

.. c:macro:: TIFFTAG_MINSAMPLEVALUE

    +minimum sample value 

.. c:macro:: TIFFTAG_MAXSAMPLEVALUE

    +maximum sample value 

.. c:macro:: TIFFTAG_XRESOLUTION

    pixels/resolution in x 

.. c:macro:: TIFFTAG_YRESOLUTION

    pixels/resolution in y 

.. c:macro:: TIFFTAG_PLANARCONFIG

    storage organization

The following storage organizations are supported:

    .. c:macro:: PLANARCONFIG_CONTIG

        single image plane

    .. c:macro:: PLANARCONFIG_SEPARATE

        separate planes of data

.. c:macro:: TIFFTAG_PAGENAME

    page name image is from 

.. c:macro:: TIFFTAG_XPOSITION

    x page offset of image lhs 

.. c:macro:: TIFFTAG_YPOSITION

    y page offset of image lhs 

.. c:macro:: TIFFTAG_FREEOFFSETS

    +byte offset to free block 

.. c:macro:: TIFFTAG_FREEBYTECOUNTS

    +sizes of free blocks 

.. c:macro:: TIFFTAG_GRAYRESPONSEUNIT

    $gray scale curve accuracy 

The following gray response units are supported:

    .. c:macro:: GRAYRESPONSEUNIT_10S

        tenths of a unit

    .. c:macro:: GRAYRESPONSEUNIT_100S

        hundredths of a unit

    .. c:macro:: GRAYRESPONSEUNIT_1000S

        thousandths of a unit

    .. c:macro:: GRAYRESPONSEUNIT_10000S

        ten-thousandths of a unit

    .. c:macro:: GRAYRESPONSEUNIT_100000S

        hundred-thousandths

.. c:macro:: TIFFTAG_GRAYRESPONSECURVE

    $gray scale response curve 

.. c:macro:: TIFFTAG_GROUP3OPTIONS

    32 flag bits 

.. c:macro:: TIFFTAG_T4OPTIONS

    TIFF 6.0 proper name alias 

The following T4 options are supported:

    .. c:macro:: GROUP3OPT_2DENCODING

        2-dimensional coding

    .. c:macro:: GROUP3OPT_UNCOMPRESSED

        data not compressed

    .. c:macro:: GROUP3OPT_FILLBITS

        fill to byte boundary

.. c:macro:: TIFFTAG_GROUP4OPTIONS

    32 flag bits 

.. c:macro:: TIFFTAG_T6OPTIONS

    TIFF 6.0 proper name 

The following T6 options are supported:

    .. c:macro:: GROUP4OPT_UNCOMPRESSED

        data not compressed

.. c:macro:: TIFFTAG_RESOLUTIONUNIT

    units of resolutions 

    .. c:macro:: RESUNIT_NONE

        no meaningful units

    .. c:macro:: RESUNIT_INCH

        english

    .. c:macro:: RESUNIT_CENTIMETER

        metric

.. c:macro:: TIFFTAG_PAGENUMBER

    page numbers of multi-page 

.. c:macro:: TIFFTAG_COLORRESPONSEUNIT

    $color curve accuracy

The following color response units are supported:

    .. c:macro:: COLORRESPONSEUNIT_10S

        tenths of a unit

    .. c:macro:: COLORRESPONSEUNIT_100S

        hundredths of a unit

    .. c:macro:: COLORRESPONSEUNIT_1000S

        thousandths of a unit

    .. c:macro:: COLORRESPONSEUNIT_10000S

        ten-thousandths of a unit

    .. c:macro:: COLORRESPONSEUNIT_100000S

        hundred-thousandths

.. c:macro:: TIFFTAG_TRANSFERFUNCTION

    !colorimetry info 

.. c:macro:: TIFFTAG_SOFTWARE

    name & release 

.. c:macro:: TIFFTAG_DATETIME

    creation date and time 

.. c:macro:: TIFFTAG_ARTIST

    creator of image 

.. c:macro:: TIFFTAG_HOSTCOMPUTER

    machine where created 

.. c:macro:: TIFFTAG_PREDICTOR

    prediction scheme w/ LZW 

The following predictors are supported:

    .. c:macro:: PREDICTOR_NONE

        no prediction scheme used

    .. c:macro:: PREDICTOR_HORIZONTAL

        horizontal differencing

    .. c:macro:: PREDICTOR_FLOATINGPOINT

        floating point predictor

.. c:macro:: TIFFTAG_WHITEPOINT

    image white point 

.. c:macro:: TIFFTAG_PRIMARYCHROMATICITIES

    !primary chromaticities 

.. c:macro:: TIFFTAG_COLORMAP

    RGB map for palette image 

.. c:macro:: TIFFTAG_HALFTONEHINTS

    !highlight+shadow info 

.. c:macro:: TIFFTAG_TILEWIDTH

    !tile width in pixels 

.. c:macro:: TIFFTAG_TILELENGTH

    !tile height in pixels 

.. c:macro:: TIFFTAG_TILEOFFSETS

    !offsets to data tiles 

.. c:macro:: TIFFTAG_TILEBYTECOUNTS

    !byte counts for tiles 

.. c:macro:: TIFFTAG_BADFAXLINES

    lines w/ wrong pixel count 

.. c:macro:: TIFFTAG_CLEANFAXDATA

    regenerated line info 

The following clean fax data options are supported:

    .. c:macro:: CLEANFAXDATA_CLEAN

        no errors detected

    .. c:macro:: CLEANFAXDATA_REGENERATED

        receiver regenerated lines

    .. c:macro:: CLEANFAXDATA_UNCLEAN

        uncorrected errors exist

.. c:macro:: TIFFTAG_CONSECUTIVEBADFAXLINES

    max consecutive bad lines 

.. c:macro:: TIFFTAG_SUBIFD

    subimage descriptors 

.. c:macro:: TIFFTAG_INKSET

    !inks in separated image 

The following inksets are supported:

    .. c:macro:: INKSET_CMYK

        !cyan-magenta-yellow-black color

    .. c:macro:: INKSET_MULTIINK

        !multi-ink or hi-fi color

.. c:macro:: TIFFTAG_INKNAMES

    !ascii names of inks 

.. c:macro:: TIFFTAG_NUMBEROFINKS

    !number of inks 

.. c:macro:: TIFFTAG_DOTRANGE

    !0% and 100% dot codes 

.. c:macro:: TIFFTAG_TARGETPRINTER

    !separation target 

.. c:macro:: TIFFTAG_EXTRASAMPLES

    !info about extra samples 

The following extra samples options are supported:

    .. c:macro:: EXTRASAMPLE_UNSPECIFIED

        !unspecified data

    .. c:macro:: EXTRASAMPLE_ASSOCALPHA

        !associated alpha data

    .. c:macro:: EXTRASAMPLE_UNASSALPHA

        !unassociated alpha data

.. c:macro:: TIFFTAG_SAMPLEFORMAT

    !data sample format 

The following sample formats are supported:

    .. c:macro:: SAMPLEFORMAT_UINT

        !unsigned integer data

    .. c:macro:: SAMPLEFORMAT_INT

        !signed integer data

    .. c:macro:: SAMPLEFORMAT_IEEEFP

        !IEEE floating point data

    .. c:macro:: SAMPLEFORMAT_VOID

        !untyped data

    .. c:macro:: SAMPLEFORMAT_COMPLEXINT

        !complex signed int

    .. c:macro:: SAMPLEFORMAT_COMPLEXIEEEFP

        !complex ieee floating

.. c:macro:: TIFFTAG_SMINSAMPLEVALUE

    !variable MinSampleValue 

.. c:macro:: TIFFTAG_SMAXSAMPLEVALUE

    !variable MaxSampleValue 

.. c:macro:: TIFFTAG_CLIPPATH

    %ClipPath [Adobe TIFF technote 2]

.. c:macro:: TIFFTAG_XCLIPPATHUNITS

    %XClipPathUnits [Adobe TIFF technote 2]

.. c:macro:: TIFFTAG_YCLIPPATHUNITS

    %YClipPathUnits [Adobe TIFF technote 2]

.. c:macro:: TIFFTAG_INDEXED

    %Indexed [Adobe TIFF Technote 3]

.. c:macro:: TIFFTAG_JPEGTABLES

    %JPEG table stream 

.. c:macro:: TIFFTAG_OPIPROXY

    %OPI Proxy [Adobe TIFF technote] 

    Tags 400-435 are from the TIFF/FX spec

.. c:macro:: TIFFTAG_GLOBALPARAMETERSIFD

    ! 

.. c:macro:: TIFFTAG_PROFILETYPE

    ! 

The following profile types are supported:

    .. c:macro:: PROFILETYPE_UNSPECIFIED

        !

    .. c:macro:: PROFILETYPE_G3_FAX

        !

.. c:macro:: TIFFTAG_FAXPROFILE

    ! 

The following fax profiles are supported:

    .. c:macro:: FAXPROFILE_S

        !TIFF/FX FAX profile S

    .. c:macro:: FAXPROFILE_F

        !TIFF/FX FAX profile F

    .. c:macro:: FAXPROFILE_J

        !TIFF/FX FAX profile J

    .. c:macro:: FAXPROFILE_C

        !TIFF/FX FAX profile C

    .. c:macro:: FAXPROFILE_L

        !TIFF/FX FAX profile L

    .. c:macro:: FAXPROFILE_M

        !TIFF/FX FAX profile LM

.. c:macro:: TIFFTAG_CODINGMETHODS

    !TIFF/FX coding methods 

The following coding methods are supported:

    .. c:macro:: CODINGMETHODS_T4_1D

        !T.4 1D

    .. c:macro:: CODINGMETHODS_T4_2D

        !T.4 2D

    .. c:macro:: CODINGMETHODS_T6

        !T.6

    .. c:macro:: CODINGMETHODS_T85

        !T.85 JBIG

    .. c:macro:: CODINGMETHODS_T42

        !T.42 JPEG

    .. c:macro:: CODINGMETHODS_T43

        !T.43 colour by layered JBIG

.. c:macro:: TIFFTAG_VERSIONYEAR

    !TIFF/FX version year 

.. c:macro:: TIFFTAG_MODENUMBER

    !TIFF/FX mode number 

.. c:macro:: TIFFTAG_DECODE

    !TIFF/FX decode 

.. c:macro:: TIFFTAG_IMAGEBASECOLOR

    !TIFF/FX image base colour 

.. c:macro:: TIFFTAG_T82OPTIONS

    !TIFF/FX T.82 options 

.. note::

  Tags 512-521 are obsoleted by Technical Note #2 which specifies a revised JPEG-in-TIFF scheme.

.. c:macro:: TIFFTAG_JPEGPROC

    !JPEG processing algorithm 

The following JPEG processing algortithms are supported:

    .. c:macro:: JPEGPROC_BASELINE

        !baseline sequential

    .. c:macro:: JPEGPROC_LOSSLESS

        !Huffman coded lossless

.. c:macro:: TIFFTAG_JPEGIFOFFSET

    !pointer to SOI marker 

.. c:macro:: TIFFTAG_JPEGIFBYTECOUNT

    !JFIF stream length 

.. c:macro:: TIFFTAG_JPEGRESTARTINTERVAL

    !restart interval length 

.. c:macro:: TIFFTAG_JPEGLOSSLESSPREDICTORS

    !lossless proc predictor 

.. c:macro:: TIFFTAG_JPEGPOINTTRANSFORM

    !lossless point transform 

.. c:macro:: TIFFTAG_JPEGQTABLES

    !Q matrix offsets 

.. c:macro:: TIFFTAG_JPEGDCTABLES

    !DCT table offsets 

.. c:macro:: TIFFTAG_JPEGACTABLES

    !AC coefficient offsets 

.. c:macro:: TIFFTAG_YCBCRCOEFFICIENTS

    !RGB -> YCbCr transform 

.. c:macro:: TIFFTAG_YCBCRSUBSAMPLING

    !YCbCr subsampling factors 

.. c:macro:: TIFFTAG_YCBCRPOSITIONING

    !subsample positioning 

The following YCbCr positioning options are supported:

    .. c:macro:: YCBCRPOSITION_CENTERED

        !as in PostScript Level 2

    .. c:macro:: YCBCRPOSITION_COSITED

        !as in CCIR 601-1

.. c:macro:: TIFFTAG_REFERENCEBLACKWHITE

    !colorimetry info 

.. c:macro:: TIFFTAG_STRIPROWCOUNTS

    !TIFF/FX strip row counts 

.. c:macro:: TIFFTAG_XMLPACKET

    %XML packet [Adobe XMP Specification, January 2004

.. c:macro:: TIFFTAG_OPIIMAGEID

    %OPI ImageID Adobe TIFF technote]

.. c:macro:: TIFFTAG_TIFFANNOTATIONDATA

    http://web.archive.org/web/20050309141348/http://www.kofile.com/support%20pro/faqs/annospec.htm 

    tags 32952-32956 are private tags registered to Island Graphics

.. c:macro:: TIFFTAG_REFPTS

    image reference points 

.. c:macro:: TIFFTAG_REGIONTACKPOINT

    region-xform tack point 

.. c:macro:: TIFFTAG_REGIONWARPCORNERS

    warp quadrilateral 

.. c:macro:: TIFFTAG_REGIONAFFINE

    affine transformation mat 

    tags 32995-32999 are private tags registered to SGI

.. c:macro:: TIFFTAG_MATTEING

    $use ExtraSamples 

.. c:macro:: TIFFTAG_DATATYPE

    $use SampleFormat 

.. c:macro:: TIFFTAG_IMAGEDEPTH

    z depth of image 

.. c:macro:: TIFFTAG_TILEDEPTH

    z depth/data tile 

tags 33300-33309 are private tags registered to Pixar

:c:macro:`TIFFTAG_PIXAR_IMAGEFULLWIDTH` and :c:macro:`TIFFTAG_PIXAR_IMAGEFULLLENGTH`
are set when an image has been cropped out of a larger image.
They reflect the size of the original uncropped image.
The :c:macro:`TIFFTAG_XPOSITION` and :c:macro:`TIFFTAG_YPOSITION` can be used
to determine the position of the smaller image in the larger one.

.. c:macro:: TIFFTAG_PIXAR_IMAGEFULLWIDTH

    full image size in x 

.. c:macro:: TIFFTAG_PIXAR_IMAGEFULLLENGTH

    full image size in y 

Tags 33302-33306 are used to identify special image modes and data
used by Pixar's texture formats.

.. c:macro:: TIFFTAG_PIXAR_TEXTUREFORMAT

    texture map format 

.. c:macro:: TIFFTAG_PIXAR_WRAPMODES

    s & t wrap modes 

.. c:macro:: TIFFTAG_PIXAR_FOVCOT

    cotan(fov) for env. maps 

.. c:macro:: TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN
.. c:macro:: TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA

tag 33405 is a private tag registered to Eastman Kodak

.. c:macro:: TIFFTAG_WRITERSERIALNUMBER

    device serial number 

.. c:macro:: TIFFTAG_CFAREPEATPATTERNDIM

    dimensions of CFA pattern 

.. c:macro:: TIFFTAG_CFAPATTERN

    color filter array pattern 

    tag 33432 is listed in the 6.0 spec w/ unknown ownership

.. c:macro:: TIFFTAG_COPYRIGHT

    copyright string 

Tags 33445-33452 are used for GEL fileformat, see
http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf

.. c:macro:: TIFFTAG_MD_FILETAG

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_SCALEPIXEL

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_COLORTABLE

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_LABNAME

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_SAMPLEINFO

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_PREPDATE

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_PREPTIME

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

.. c:macro:: TIFFTAG_MD_FILEUNITS

    http://research.stowers-institute.org/mcm/efg/ScientificSoftware/Utility/TiffTags/GEL-FileFormat.pdf 

IPTC TAG from RichTIFF specifications

.. c:macro:: TIFFTAG_RICHTIFFIPTC

.. c:macro:: TIFFTAG_INGR_PACKET_DATA_TAG

    Intergraph Application specific storage. 

.. c:macro:: TIFFTAG_INGR_FLAG_REGISTERS

    Intergraph Application specific flags. 

.. c:macro:: TIFFTAG_IRASB_TRANSORMATION_MATRIX

    Originally part of Intergraph's GeoTIFF tags, but likely understood by IrasB only. 

.. c:macro:: TIFFTAG_MODELTIEPOINTTAG

    GeoTIFF 

34016-34029 are reserved for ANSI IT8 TIFF/IT <dkelly@apago.com)

.. c:macro:: TIFFTAG_IT8SITE

    site name 

.. c:macro:: TIFFTAG_IT8COLORSEQUENCE

    color seq. [RGB,CMYK,etc] 

.. c:macro:: TIFFTAG_IT8HEADER

    DDES Header 

.. c:macro:: TIFFTAG_IT8RASTERPADDING

    raster scanline padding 

.. c:macro:: TIFFTAG_IT8BITSPERRUNLENGTH

    # of bits in short run 

    .. c:macro:: TIFFTAG_IT8BITSPEREXTENDEDRUNLENGTH

        # of bits in long run

.. c:macro:: TIFFTAG_IT8COLORTABLE

    LW colortable 

.. c:macro:: TIFFTAG_IT8IMAGECOLORINDICATOR

    BP/BL image color switch 

.. c:macro:: TIFFTAG_IT8BKGCOLORINDICATOR

    BP/BL bg color switch 

.. c:macro:: TIFFTAG_IT8IMAGECOLORVALUE

    BP/BL image color value 

.. c:macro:: TIFFTAG_IT8BKGCOLORVALUE

    BP/BL bg color value 

.. c:macro:: TIFFTAG_IT8PIXELINTENSITYRANGE

    MP pixel intensity value 

.. c:macro:: TIFFTAG_IT8TRANSPARENCYINDICATOR

    HC transparency switch 

.. c:macro:: TIFFTAG_IT8COLORCHARACTERIZATION

    color character. table 

.. c:macro:: TIFFTAG_IT8HCUSAGE

    HC usage indicator 

    .. c:macro:: TIFFTAG_IT8TRAPINDICATOR

        Trapping indicator (untrapped=0, trapped=1)

.. c:macro:: TIFFTAG_IT8CMYKEQUIVALENT

    CMYK color equivalents 

tags 34232-34236 are private tags registered to Texas Instruments

.. c:macro:: TIFFTAG_FRAMECOUNT

    Sequence Frame Count 

.. c:macro:: TIFFTAG_MODELTRANSFORMATIONTAG

    Used in interchangeable GeoTIFF files 

    tag 34377 is private tag registered to Adobe for PhotoShop

.. c:macro:: TIFFTAG_PHOTOSHOP

    tags 34665, 34853 and 40965 are documented in EXIF specification 

.. c:macro:: TIFFTAG_EXIFIFD

    Pointer to EXIF private directory 

    tag 34750 is a private tag registered to Adobe?

.. c:macro:: TIFFTAG_ICCPROFILE

    ICC profile data 

.. c:macro:: TIFFTAG_IMAGELAYER

    !TIFF/FX image layer information 

    tag 34750 is a private tag registered to Pixel Magic

.. c:macro:: TIFFTAG_JBIGOPTIONS

    JBIG options 

.. c:macro:: TIFFTAG_GPSIFD

    Pointer to GPS private directory 

tags 34908-34914 are private tags registered to SGI

.. c:macro:: TIFFTAG_FAXRECVPARAMS

    encoded Class 2 ses. params 

.. c:macro:: TIFFTAG_FAXSUBADDRESS

    received SubAddr string 

.. c:macro:: TIFFTAG_FAXRECVTIME

    receive time (secs) 

.. c:macro:: TIFFTAG_FAXDCS

    encoded fax ses. params, Table 2/T.30 

tags 37439-37443 are registered to SGI <gregl@sgi.com>

.. c:macro:: TIFFTAG_STONITS

    Sample value to Nits 

tag 34929 is a private tag registered to FedEx

.. c:macro:: TIFFTAG_FEDEX_EDR

    unknown use 

.. c:macro:: TIFFTAG_IMAGESOURCEDATA

    http://justsolve.archiveteam.org/wiki/PSD, http://www.adobe.com/devnet-apps/photoshop/fileformatashtml/ 

.. c:macro:: TIFFTAG_INTEROPERABILITYIFD

    Pointer to Interoperability private directory 

.. c:macro:: TIFFTAG_GDAL_METADATA

    Used by the GDAL library 

.. c:macro:: TIFFTAG_GDAL_NODATA

    Used by the GDAL library 

.. c:macro:: TIFFTAG_OCE_SCANJOB_DESCRIPTION

    Used in the Oce scanning process 

.. c:macro:: TIFFTAG_OCE_APPLICATION_SELECTOR

    Used in the Oce scanning process. 

.. c:macro:: TIFFTAG_OCE_IDENTIFICATION_NUMBER

.. c:macro:: TIFFTAG_OCE_IMAGELOGIC_CHARACTERISTICS

tags 50674 to 50677 are reserved for ESRI

.. c:macro:: TIFFTAG_LERC_PARAMETERS

    Stores LERC version and additional compression method 

    Adobe Digital Negative (DNG) format tags

.. c:macro:: TIFFTAG_DNGVERSION

    &DNG version number 

.. c:macro:: TIFFTAG_DNGBACKWARDVERSION

    &DNG compatibility version 

.. c:macro:: TIFFTAG_UNIQUECAMERAMODEL

    &name for the camera model 

.. c:macro:: TIFFTAG_LOCALIZEDCAMERAMODEL

    &localized camera model name

.. c:macro:: TIFFTAG_CFAPLANECOLOR

    &CFAPattern->LinearRaw space mapping

.. c:macro:: TIFFTAG_CFALAYOUT

    &spatial layout of the CFA 

.. c:macro:: TIFFTAG_LINEARIZATIONTABLE

    &lookup table description 

.. c:macro:: TIFFTAG_BLACKLEVELREPEATDIM

    &repeat pattern size for the BlackLevel tag

.. c:macro:: TIFFTAG_BLACKLEVEL

    &zero light encoding level 

.. c:macro:: TIFFTAG_BLACKLEVELDELTAH

    &zero light encoding level differences (columns)

.. c:macro:: TIFFTAG_BLACKLEVELDELTAV

    &zero light encoding level differences (rows)

.. c:macro:: TIFFTAG_WHITELEVEL

    &fully saturated encoding level

.. c:macro:: TIFFTAG_DEFAULTSCALE

    &default scale factors 

.. c:macro:: TIFFTAG_DEFAULTCROPORIGIN

    &origin of the final image area

.. c:macro:: TIFFTAG_DEFAULTCROPSIZE

    &size of the final image area

.. c:macro:: TIFFTAG_COLORMATRIX1

    &XYZ->reference color space transformation matrix 1

.. c:macro:: TIFFTAG_COLORMATRIX2

    &XYZ->reference color space transformation matrix 2

.. c:macro:: TIFFTAG_CAMERACALIBRATION1

    &calibration matrix 1 

.. c:macro:: TIFFTAG_CAMERACALIBRATION2

    &calibration matrix 2 

.. c:macro:: TIFFTAG_REDUCTIONMATRIX1

    &dimensionality reduction matrix 1

.. c:macro:: TIFFTAG_REDUCTIONMATRIX2

    &dimensionality reduction matrix 2

.. c:macro:: TIFFTAG_ANALOGBALANCE

    &gain applied the stored raw values

.. c:macro:: TIFFTAG_ASSHOTNEUTRAL

    &selected white balance in linear reference space

.. c:macro:: TIFFTAG_ASSHOTWHITEXY

    &selected white balance in x-y chromaticity coordinates

.. c:macro:: TIFFTAG_BASELINEEXPOSURE

    &how much to move the zero point

.. c:macro:: TIFFTAG_BASELINENOISE

    &relative noise level 

.. c:macro:: TIFFTAG_BASELINESHARPNESS

    &relative amount of sharpening

.. c:macro:: TIFFTAG_BAYERGREENSPLIT

    &how closely the values of the green pixels in the blue/green rows track the values of the green pixels in the red/green rows

.. c:macro:: TIFFTAG_LINEARRESPONSELIMIT

    &non-linear encoding range 

.. c:macro:: TIFFTAG_CAMERASERIALNUMBER

    &camera's serial number 

.. c:macro:: TIFFTAG_LENSINFO

    info about the lens 

.. c:macro:: TIFFTAG_CHROMABLURRADIUS

    &chroma blur radius 

.. c:macro:: TIFFTAG_ANTIALIASSTRENGTH

    &relative strength of the camera's anti-alias filter

.. c:macro:: TIFFTAG_SHADOWSCALE

    &used by Adobe Camera Raw 

.. c:macro:: TIFFTAG_DNGPRIVATEDATA

    &manufacturer's private data 

.. c:macro:: TIFFTAG_MAKERNOTESAFETY

    &whether the EXIF MakerNote tag is safe to preserve along with the rest of the EXIF data

.. c:macro:: TIFFTAG_CALIBRATIONILLUMINANT1

    &illuminant 1 

.. c:macro:: TIFFTAG_CALIBRATIONILLUMINANT2

    &illuminant 2 

.. c:macro:: TIFFTAG_BESTQUALITYSCALE

    &best quality multiplier 

.. c:macro:: TIFFTAG_RAWDATAUNIQUEID

    &unique identifier for the raw image data

.. c:macro:: TIFFTAG_ORIGINALRAWFILENAME

    &file name of the original raw file

.. c:macro:: TIFFTAG_ORIGINALRAWFILEDATA

    &contents of the original raw file

.. c:macro:: TIFFTAG_ACTIVEAREA

    &active (non-masked) pixels of the sensor

.. c:macro:: TIFFTAG_MASKEDAREAS

    &list of coordinates of fully masked pixels

.. c:macro:: TIFFTAG_ASSHOTICCPROFILE

    &these two tags used to 

.. c:macro:: TIFFTAG_ASSHOTPREPROFILEMATRIX

    map cameras's color space into ICC profile space

.. c:macro:: TIFFTAG_CURRENTICCPROFILE

    & 

.. c:macro:: TIFFTAG_CURRENTPREPROFILEMATRIX

    & 

.. c:macro:: TIFFTAG_RPCCOEFFICIENT

    Define by GDAL for geospatial georeferencing through RPC: http://geotiff.maptools.org/rpc_prop.html 


.. c:macro:: TIFFTAG_ALIAS_LAYER_METADATA

    Alias Sketchbook Pro layer usage description. 


    GeoTIFF DGIWG

.. c:macro:: TIFFTAG_TIFF_RSID

    https://www.awaresystems.be/imaging/tiff/tifftags/tiff_rsid.html 

.. c:macro:: TIFFTAG_GEO_METADATA

    https://www.awaresystems.be/imaging/tiff/tifftags/geo_metadata.html 


.. c:macro:: TIFFTAG_EXTRACAMERAPROFILES

    http://wwwimages.adobe.com/www.adobe.com/content/dam/Adobe/en/products/photoshop/pdfs/dng_spec_1.4.0.0.pdf 


    tag 65535 is an undefined tag used by Eastman Kodak

.. c:macro:: TIFFTAG_DCSHUESHIFTVALUES

    hue shift correction data 

"Pseudo-tags"
-------------

The following are "pseudo-tags" that can be used to control
codec-specific functionality.  These tags are not written to file.
Note that these values start at 0xffff+1 so that they'll never
collide with Aldus-assigned tags.

If you want your private pseudo tags "registered" (i.e. added to
this file), please post a bug report (see :doc:`/project/bugs`)
with the appropriate C definitions to add.

.. c:macro:: TIFFTAG_FAXMODE

    Group 3/4 format control 

The following fax modes are supported:

.. c:macro:: FAXMODE_CLASSIC

    default, include RTC

.. c:macro:: FAXMODE_NORTC

    no RTC at end of data

.. c:macro:: FAXMODE_NOEOL

    no EOL code at end of row

.. c:macro:: FAXMODE_BYTEALIGN

    byte align row

.. c:macro:: FAXMODE_WORDALIGN

    word align row

.. c:macro:: FAXMODE_CLASSF

    TIFF Class F

.. c:macro:: TIFFTAG_JPEGQUALITY

    Compression quality level 

    Note: quality level is on the IJG 0-100 scale.  Default value is 75

.. c:macro:: TIFFTAG_JPEGCOLORMODE

    Auto RGB<=>YCbCr convert? 

The following JPEG color modes are supported:

.. c:macro:: JPEGCOLORMODE_RAW

    no conversion (default)

.. c:macro:: JPEGCOLORMODE_RGB

    do auto conversion

.. c:macro:: TIFFTAG_JPEGTABLESMODE

    What to put in JPEGTables 

The following JPEG tables modes are supported:

.. c:macro:: JPEGTABLESMODE_QUANT

    include quantization tbls

.. c:macro:: JPEGTABLESMODE_HUFF

    include Huffman tbls

Note: default is :c:expr:`JPEGTABLESMODE_QUANT | JPEGTABLESMODE_HUFF`

.. c:macro:: TIFFTAG_FAXFILLFUNC

    G3/G4 fill function 

.. c:macro:: TIFFTAG_PIXARLOGDATAFMT

    PixarLogCodec I/O data sz 

The following PixarLog data formats are supported:

.. c:macro:: PIXARLOGDATAFMT_8BIT

    regular u_char samples

.. c:macro:: PIXARLOGDATAFMT_8BITABGR

    ABGR-order u_chars

.. c:macro:: PIXARLOGDATAFMT_11BITLOG

    11-bit log-encoded (raw)

.. c:macro:: PIXARLOGDATAFMT_12BITPICIO

    as per PICIO (1.0==2048)

.. c:macro:: PIXARLOGDATAFMT_16BIT

    signed short samples

.. c:macro:: PIXARLOGDATAFMT_FLOAT

    IEEE float samples

    65550-65556 are allocated to Oceana Matrix <dev@oceana.com>

.. c:macro:: TIFFTAG_DCSIMAGERTYPE

    imager model & filter 

The following DCS imager types are supported:

.. c:macro:: DCSIMAGERMODEL_M3

    M3 chip (1280 x 1024)

.. c:macro:: DCSIMAGERMODEL_M5

    M5 chip (1536 x 1024)

.. c:macro:: DCSIMAGERMODEL_M6

    M6 chip (3072 x 2048)

.. c:macro:: DCSIMAGERFILTER_IR

    infrared filter

.. c:macro:: DCSIMAGERFILTER_MONO

    monochrome filter

.. c:macro:: DCSIMAGERFILTER_CFA

    color filter array

.. c:macro:: DCSIMAGERFILTER_OTHER

    other filter

.. c:macro:: TIFFTAG_DCSINTERPMODE

    interpolation mode 

The following DCS interpolation modes are supported:

.. c:macro:: DCSINTERPMODE_NORMAL

    whole image, default

.. c:macro:: DCSINTERPMODE_PREVIEW

    preview of image (384x256)

.. c:macro:: TIFFTAG_DCSBALANCEARRAY

    color balance values 

.. c:macro:: TIFFTAG_DCSCORRECTMATRIX

    color correction values 

.. c:macro:: TIFFTAG_DCSGAMMA

    gamma value 

.. c:macro:: TIFFTAG_DCSTOESHOULDERPTS

    toe & shoulder points 

.. c:macro:: TIFFTAG_DCSCALIBRATIONFD

    calibration file desc 

    Note: quality level is on the ZLIB 1-9 scale. Default value is -1

.. c:macro:: TIFFTAG_ZIPQUALITY

    compression quality level 

.. c:macro:: TIFFTAG_PIXARLOGQUALITY

    PixarLog uses same scale 

    65559 is allocated to Oceana Matrix <dev@oceana.com>

.. c:macro:: TIFFTAG_DCSCLIPRECTANGLE

    area of image to acquire 

.. c:macro:: TIFFTAG_SGILOGDATAFMT

    SGILog user data format 

The following SGILog data formats are supported:

.. c:macro:: SGILOGDATAFMT_FLOAT

    IEEE float samples

.. c:macro:: SGILOGDATAFMT_16BIT

    16-bit samples

.. c:macro:: SGILOGDATAFMT_RAW

    uninterpreted data

.. c:macro:: SGILOGDATAFMT_8BIT

    8-bit RGB monitor values

.. c:macro:: TIFFTAG_SGILOGENCODE

    SGILog data encoding control

The following SGILog data encodings are supported:

.. c:macro:: SGILOGENCODE_NODITHER

    do not dither encoded values

.. c:macro:: SGILOGENCODE_RANDITHER

    randomly dither encd values

.. c:macro:: TIFFTAG_LZMAPRESET

    LZMA2 preset (compression level) 

.. c:macro:: TIFFTAG_PERSAMPLE

    interface for per sample tags 

The following persample options are supported:

.. c:macro:: PERSAMPLE_MERGED

    present as a single value

.. c:macro:: PERSAMPLE_MULTI

    present as multiple values

.. c:macro:: TIFFTAG_ZSTD_LEVEL

    ZSTD compression level 

.. c:macro:: TIFFTAG_LERC_VERSION

    LERC version 

    .. c:macro:: LERC_VERSION_2_4

.. c:macro:: TIFFTAG_LERC_ADD_COMPRESSION

    LERC additional compression 

The following LERC compression options are supported:

.. c:macro:: LERC_ADD_COMPRESSION_NONE
.. c:macro:: LERC_ADD_COMPRESSION_DEFLATE
.. c:macro:: LERC_ADD_COMPRESSION_ZSTD

.. c:macro:: TIFFTAG_LERC_MAXZERROR

    LERC maximum error 

.. c:macro:: TIFFTAG_WEBP_LEVEL

    WebP compression level 

.. c:macro:: TIFFTAG_WEBP_LOSSLESS

    WebP lossless/lossy 

.. c:macro:: TIFFTAG_DEFLATE_SUBCODEC

    ZIP codec: to get/set the sub-codec to use. Will default to libdeflate when available 

The following Deflate subcoded options are supported:

.. c:macro:: DEFLATE_SUBCODEC_ZLIB
.. c:macro:: DEFLATE_SUBCODEC_LIBDEFLATE

EXIF tags
---------

.. c:macro:: EXIFTAG_EXPOSURETIME

    Exposure time 

.. c:macro:: EXIFTAG_FNUMBER

    F number 

.. c:macro:: EXIFTAG_EXPOSUREPROGRAM

    Exposure program 

.. c:macro:: EXIFTAG_SPECTRALSENSITIVITY

    Spectral sensitivity 

.. c:macro:: EXIFTAG_ISOSPEEDRATINGS

    ISO speed rating 

.. c:macro:: EXIFTAG_PHOTOGRAPHICSENSITIVITY

    Photographic Sensitivity (new name for tag 34855) 

.. c:macro:: EXIFTAG_OECF

    Optoelectric conversion factor 

.. c:macro:: EXIFTAG_EXIFVERSION

    Exif version 

.. c:macro:: EXIFTAG_DATETIMEORIGINAL

    Date and time of original data generation 

.. c:macro:: EXIFTAG_DATETIMEDIGITIZED

    Date and time of digital data generation 

.. c:macro:: EXIFTAG_COMPONENTSCONFIGURATION

    Meaning of each component 

.. c:macro:: EXIFTAG_COMPRESSEDBITSPERPIXEL

    Image compression mode 

.. c:macro:: EXIFTAG_SHUTTERSPEEDVALUE

    Shutter speed 

.. c:macro:: EXIFTAG_APERTUREVALUE

    Aperture 

.. c:macro:: EXIFTAG_BRIGHTNESSVALUE

    Brightness 

.. c:macro:: EXIFTAG_EXPOSUREBIASVALUE

    Exposure bias 

.. c:macro:: EXIFTAG_MAXAPERTUREVALUE

    Maximum lens aperture 

.. c:macro:: EXIFTAG_SUBJECTDISTANCE

    Subject distance 

.. c:macro:: EXIFTAG_METERINGMODE

    Metering mode 

.. c:macro:: EXIFTAG_LIGHTSOURCE

    Light source 

.. c:macro:: EXIFTAG_FLASH

    Flash 

.. c:macro:: EXIFTAG_FOCALLENGTH

    Lens focal length 

.. c:macro:: EXIFTAG_SUBJECTAREA

    Subject area 

.. c:macro:: EXIFTAG_MAKERNOTE

    Manufacturer notes 

.. c:macro:: EXIFTAG_USERCOMMENT

    User comments 

.. c:macro:: EXIFTAG_SUBSECTIME

    DateTime subseconds 

.. c:macro:: EXIFTAG_SUBSECTIMEORIGINAL

    DateTimeOriginal subseconds 

.. c:macro:: EXIFTAG_SUBSECTIMEDIGITIZED

    DateTimeDigitized subseconds 

.. c:macro:: EXIFTAG_FLASHPIXVERSION

    Supported Flashpix version 

.. c:macro:: EXIFTAG_COLORSPACE

    Color space information 

.. c:macro:: EXIFTAG_PIXELXDIMENSION

    Valid image width 

.. c:macro:: EXIFTAG_PIXELYDIMENSION

    Valid image height 

.. c:macro:: EXIFTAG_RELATEDSOUNDFILE

    Related audio file 

.. c:macro:: EXIFTAG_FLASHENERGY

    Flash energy 

.. c:macro:: EXIFTAG_SPATIALFREQUENCYRESPONSE

    Spatial frequency response 

.. c:macro:: EXIFTAG_FOCALPLANEXRESOLUTION

    Focal plane X resolution 

.. c:macro:: EXIFTAG_FOCALPLANEYRESOLUTION

    Focal plane Y resolution 

.. c:macro:: EXIFTAG_FOCALPLANERESOLUTIONUNIT

    Focal plane resolution unit 

.. c:macro:: EXIFTAG_SUBJECTLOCATION

    Subject location 

.. c:macro:: EXIFTAG_EXPOSUREINDEX

    Exposure index 

.. c:macro:: EXIFTAG_SENSINGMETHOD

    Sensing method 

.. c:macro:: EXIFTAG_FILESOURCE

    File source 

.. c:macro:: EXIFTAG_SCENETYPE

    Scene type 

.. c:macro:: EXIFTAG_CFAPATTERN

    CFA pattern 

.. c:macro:: EXIFTAG_CUSTOMRENDERED

    Custom image processing 

.. c:macro:: EXIFTAG_EXPOSUREMODE

    Exposure mode 

.. c:macro:: EXIFTAG_WHITEBALANCE

    White balance 

.. c:macro:: EXIFTAG_DIGITALZOOMRATIO

    Digital zoom ratio 

.. c:macro:: EXIFTAG_FOCALLENGTHIN35MMFILM

    Focal length in 35 mm film 

.. c:macro:: EXIFTAG_SCENECAPTURETYPE

    Scene capture type 

.. c:macro:: EXIFTAG_GAINCONTROL

    Gain control 

.. c:macro:: EXIFTAG_CONTRAST

    Contrast 

.. c:macro:: EXIFTAG_SATURATION

    Saturation 

.. c:macro:: EXIFTAG_SHARPNESS

    Sharpness 

.. c:macro:: EXIFTAG_DEVICESETTINGDESCRIPTION

    Device settings description 

.. c:macro:: EXIFTAG_SUBJECTDISTANCERANGE

    Subject distance range 

.. c:macro:: EXIFTAG_IMAGEUNIQUEID

    Unique image ID 

.. c:macro:: EXIFTAG_SENSITIVITYTYPE

    The SensitivityType tag indicates which one of the parameters of ISO12232 is the PhotographicSensitivity tag. 

.. c:macro:: EXIFTAG_STANDARDOUTPUTSENSITIVITY

    This tag indicates the standard output sensitivity value of a camera or input device defined in ISO 12232. 

.. c:macro:: EXIFTAG_RECOMMENDEDEXPOSUREINDEX

    recommended exposure index 

.. c:macro:: EXIFTAG_ISOSPEED

    ISO speed value 

.. c:macro:: EXIFTAG_ISOSPEEDLATITUDEYYY

    ISO speed latitude yyy 

.. c:macro:: EXIFTAG_ISOSPEEDLATITUDEZZZ

    ISO speed latitude zzz 

.. c:macro:: EXIFTAG_OFFSETTIME

    offset from UTC of the time of DateTime tag. 

.. c:macro:: EXIFTAG_OFFSETTIMEORIGINAL

    offset from UTC of the time of DateTimeOriginal tag. 

.. c:macro:: EXIFTAG_OFFSETTIMEDIGITIZED

    offset from UTC of the time of DateTimeDigitized tag. 

.. c:macro:: EXIFTAG_TEMPERATURE

    Temperature as the ambient situation at the shot in dergee Celsius 

.. c:macro:: EXIFTAG_HUMIDITY

    Humidity as the ambient situation at the shot in percent 

.. c:macro:: EXIFTAG_PRESSURE

    Pressure as the ambient situation at the shot hecto-Pascal (hPa) 

.. c:macro:: EXIFTAG_WATERDEPTH

    WaterDepth as the ambient situation at the shot in meter (m) 

.. c:macro:: EXIFTAG_ACCELERATION

    Acceleration (a scalar regardless of direction) as the ambient situation at the shot in units of mGal (10-5 m/s^2) 

.. c:macro:: EXIFTAG_CAMERAELEVATIONANGLE

    Elevation/depression. angle of the orientation of the camera(imaging optical axis) as the ambient situation at the shot in degree from -180deg to +180deg. 

.. c:macro:: EXIFTAG_CAMERAOWNERNAME

    owner of a camera 

.. c:macro:: EXIFTAG_BODYSERIALNUMBER

    serial number of the body of the camera 

.. c:macro:: EXIFTAG_LENSSPECIFICATION

    minimum focal length (in mm), maximum focal length (in mm), minimum F number in the minimum focal length, and minimum F number in the maximum focal length, 

.. c:macro:: EXIFTAG_LENSMAKE

    the lens manufacturer 

.. c:macro:: EXIFTAG_LENSMODEL

    the lens model name and model number 

.. c:macro:: EXIFTAG_LENSSERIALNUMBER

    the serial number of the interchangeable lens 

.. c:macro:: EXIFTAG_GAMMA

    value of coefficient gamma 

.. c:macro:: EXIFTAG_COMPOSITEIMAGE

    composite image 

.. c:macro:: EXIFTAG_SOURCEIMAGENUMBEROFCOMPOSITEIMAGE

    source image number of composite image 

.. c:macro:: EXIFTAG_SOURCEEXPOSURETIMESOFCOMPOSITEIMAGE

    source exposure times of composite image 


EXIF GPS tags
-------------

.. c:macro:: GPSTAG_VERSIONID	

    Indicates the version of GPSInfoIFD.	 

.. c:macro:: GPSTAG_LATITUDEREF	

    Indicates whether the latitude is north or south latitude.	 

.. c:macro:: GPSTAG_LATITUDE	

    Indicates the latitude.	 

.. c:macro:: GPSTAG_LONGITUDEREF	

    Indicates whether the longitude is east or west longitude.	 

.. c:macro:: GPSTAG_LONGITUDE	

    Indicates the longitude.	 

.. c:macro:: GPSTAG_ALTITUDEREF	

    Indicates the altitude used as the reference altitude.	 

.. c:macro:: GPSTAG_ALTITUDE	

    Indicates the altitude based on the reference in GPSAltitudeRef.	 

.. c:macro:: GPSTAG_TIMESTAMP	

    Indicates the time as UTC (Coordinated Universal Time).	 

.. c:macro:: GPSTAG_SATELLITES	

    Indicates the GPS satellites used for measurements.	 

.. c:macro:: GPSTAG_STATUS	

    Indicates the status of the GPS receiver when the image is recorded.	 

.. c:macro:: GPSTAG_MEASUREMODE	

    Indicates the GPS measurement mode.	 

.. c:macro:: GPSTAG_DOP	

    Indicates the GPS DOP (data degree of precision).	 

.. c:macro:: GPSTAG_SPEEDREF	

    Indicates the unit used to express the GPS receiver speed of movement.	 

.. c:macro:: GPSTAG_SPEED	

    Indicates the speed of GPS receiver movement.	 

.. c:macro:: GPSTAG_TRACKREF	

    Indicates the reference for giving the direction of GPS receiver movement.	 

.. c:macro:: GPSTAG_TRACK	

    Indicates the direction of GPS receiver movement.	 

.. c:macro:: GPSTAG_IMGDIRECTIONREF	

    Indicates the reference for giving the direction of the image when it is captured.	 

.. c:macro:: GPSTAG_IMGDIRECTION	

    Indicates the direction of the image when it was captured.	 

.. c:macro:: GPSTAG_MAPDATUM	

    Indicates the geodetic survey data used by the GPS receiver. (e.g. WGS-84)	 

.. c:macro:: GPSTAG_DESTLATITUDEREF	

    Indicates whether the latitude of the destination point is north or south latitude.	 

.. c:macro:: GPSTAG_DESTLATITUDE	

    Indicates the latitude of the destination point.	 

.. c:macro:: GPSTAG_DESTLONGITUDEREF	

    Indicates whether the longitude of the destination point is east or west longitude.	 

.. c:macro:: GPSTAG_DESTLONGITUDE	

    Indicates the longitude of the destination point.	 

.. c:macro:: GPSTAG_DESTBEARINGREF	

    Indicates the reference used for giving the bearing to the destination point.	 

.. c:macro:: GPSTAG_DESTBEARING	

    Indicates the bearing to the destination point.	 

.. c:macro:: GPSTAG_DESTDISTANCEREF	

    Indicates the unit used to express the distance to the destination point.	 

.. c:macro:: GPSTAG_DESTDISTANCE	

    Indicates the distance to the destination point.	 

.. c:macro:: GPSTAG_PROCESSINGMETHOD	

    A character string recording the name of the method used for location finding.	 

.. c:macro:: GPSTAG_AREAINFORMATION	

    A character string recording the name of the GPS area.	 

.. c:macro:: GPSTAG_DATESTAMP	

    A character string recording date and time information relative to UTC (Coordinated Universal Time).	 

.. c:macro:: GPSTAG_DIFFERENTIAL	

    Indicates whether differential correction is applied to the GPS receiver.	 

.. c:macro:: GPSTAG_GPSHPOSITIONINGERROR	

    Indicates horizontal positioning errors in meters.		 

See also
--------

:doc:`TIFFGetField` (3tiff),
:doc:`TIFFSetField` (3tiff),
:doc:`libtiff` (3tiff)
