TIFFFieldSetGetSize
===================

Synopsis
--------

.. highlight:: c

::

    #include <tiffio.h>

.. c:function:: int TIFFFieldSetGetSize(const TIFFField* fip)

Description
-----------

:c:func:`TIFFFieldGetSetSize` returns the internal storage size of the field data type in bytes.

:c:var:`fip` is a field information pointer previously returned by
:c:func:`TIFFFindField`,
:c:func:`TIFFFieldWithTag`,
:c:func:`TIFFFieldWithName`.

Return values
-------------

:c:func:`TIFFFieldGetSizeSize` returns the field data type size in bytes, or zero if the
:c:var:`fip` pointer was NULL or the type was invalid.

See also
--------

:doc:`libtiff`
