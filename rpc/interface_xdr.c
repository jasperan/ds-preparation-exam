

#include "interface.h"

bool_t
xdr_passer (XDR *xdrs, passer *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->a1))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->a2))
		 return FALSE;
	return TRUE;
}
