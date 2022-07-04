.. _public-data-types:

TIFFtypes
=========

Synopsis
--------

.. highlight:: c

::

    #include <tiffio.h>


Description
-----------

LibTIFF uses several custom datatypes in its programming interfaces,
which are detailed here.  These types are use to promote portability.
Two sets of typedefs are used, one for communication with clients
of the library, and one for internal data structures and parsing of the
TIFF format.  The following typedefs are exposed to users either through
function definitions or through parameters passed through the varargs
interfaces.

Structures
----------

.. c:struct:: TIFF

    An opaque data type representing an open TIFF file.

Integer types
-------------

.. doxygentypedef:: ttag_t

.. doxygentypedef:: tdir_t

.. doxygentypedef:: tsample_t

.. doxygentypedef:: tstrip_t

.. doxygentypedef:: ttile_t

.. doxygentypedef:: tmsize_t

.. doxygendefine:: TIFF_TMSIZE_T_MAX

.. doxygentypedef:: tmsize_t

.. doxygentypedef:: tsize_t

.. doxygentypedef:: tdata_t

.. doxygentypedef:: thandle_t

.. doxygentypedef:: toff_t

Note that :c:type:`tstrip_t`, :c:type:`ttile_t`, and :c:type:`tsize_t`
are constrained to be no more than 32-bit quantities by 32-bit fields
they are stored in in the TIFF image.  Likewise :c:type:`tsample_t` is
limited by the 16-bit field used to store the ``SamplesPerPixel`` tag.
:c:type:`tdir_t` constrains the maximum number of IFDs that may appear
in an image and may be an arbitrary size (w/o penalty).  :c:type:`ttag_t`
must be either :c:expr:`int`, :c:expr:`unsigned int`, pointer, or
:c:expr:`double`, because the library uses a varargs interface and
C restricts the type of the parameter before an ellipsis to be a
promoted type.  :c:type:`toff_t`  is defined as :c:type:`uint64_t`
because TIFF file offsets are (unsigned) 32-bit quantities, and BigTIFF
file offsets are unsigned 64-bit quantities.  A signed value is used
because some interfaces return -1 on error. Finally, note that
user-specified data references are passed as opaque handles and only
cast at the lowest layers where their type is presumed.

.. TODO: Check why this toff_t was switched to unsigned and update description.


I/O types
---------

.. doxygentypedef:: TIFFReadWriteProc

.. doxygentypedef:: TIFFSeekProc

.. doxygentypedef:: TIFFCloseProc

.. doxygentypedef:: TIFFSizeProc

.. doxygentypedef:: TIFFMapFileProc

.. doxygentypedef:: TIFFUnmapFileProc

See also
--------

:doc:`libtiff` (3tiff)
