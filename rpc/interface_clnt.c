

#include <memory.h> /* for memset */
#include "interface.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat
add_99(passer arg1, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, add,
		(xdrproc_t) xdr_passer, (caddr_t) &arg1,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}
