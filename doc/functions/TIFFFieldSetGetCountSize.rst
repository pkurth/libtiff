TIFFFieldSetGetCountSize
========================

Synopsis
--------

.. highlight:: c

::

    #include <tiffio.h>

.. c:function:: int TIFFFieldSetGetCountSize(const TIFFField* fip)

Description
-----------

:c:func:`TIFFFieldGetSetSize` returns the size of the count parameter of the field.

:c:var:`fip` is a field information pointer previously returned by
:c:func:`TIFFFindField`,
:c:func:`TIFFFieldWithTag`,
:c:func:`TIFFFieldWithName`.

Return values
-------------

:c:func:`TIFFFieldGetSizeSize` returns the datatype size of the count parameter, or zero if the
:c:var:`fip` pointer was NULL or the type was invalid.  The size will be 2 if the type is
:c:type:`uint16_t`, or 4 is the type is :c:type:`uint32_t`.

See also
--------

:doc:`libtiff`
