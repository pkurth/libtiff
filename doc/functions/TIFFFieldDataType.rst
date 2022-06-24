TIFFFieldDataType
=================

Synopsis
--------

.. highlight:: c

::

    #include <tiffio.h>

.. c:enum:: TIFFDataType

    .. c:enumerator:: TIFF_NOTYPE

    placeholder

    .. c:enumerator:: TIFF_BYTE

    8-bit unsigned integer

    .. c:enumerator:: TIFF_ASCII

    8-bit bytes w/ last byte null

    .. c:enumerator:: TIFF_SHORT

    16-bit unsigned integer

    .. c:enumerator:: TIFF_LONG

    32-bit unsigned integer

    .. c:enumerator:: TIFF_RATIONAL

    64-bit unsigned fraction

    .. c:enumerator:: TIFF_SBYTE

    !8-bit signed integer

    .. c:enumerator:: TIFF_UNDEFINED

    !8-bit untyped data

    .. c:enumerator:: TIFF_SSHORT

    !16-bit signed integer

    .. c:enumerator:: TIFF_SLONG

    !32-bit signed integer

    .. c:enumerator:: TIFF_SRATIONAL

    !64-bit signed fraction

    .. c:enumerator:: TIFF_FLOAT

    !32-bit IEEE floating point

    .. c:enumerator:: TIFF_DOUBLE

    !64-bit IEEE floating point

    .. c:enumerator:: TIFF_IFD

    %32-bit unsigned integer (offset)

    .. c:enumerator:: TIFF_LONG8

    BigTIFF 64-bit unsigned integer

    .. c:enumerator:: TIFF_SLONG8

    BigTIFF 64-bit signed integer

    .. c:enumerator:: TIFF_IFD8

    BigTIFF 64-bit unsigned integer (offset)

.. c:macro:: TIFF_ANY

    An alias for :c:macro:`TIFF_NOTYPE`.

.. c:function:: TIFFDataType TIFFFieldDataType(const TIFFField* fip)

Description

:c:func:`TIFFFieldDataType` returns the data type stored in a TIFF field.
*fip* is a field information pointer previously returned by
:c:func:`TIFFFindField`, :c:func:`TIFFFieldWithTag`, or :c:func:`TIFFFieldWithName`.

Return values
-------------

:c:func:`TIFFFieldDataType` returns a member of the enum type
:c:type:`TIFFDataType`.

See also
--------

:doc:`libtiff` (3tiff)
