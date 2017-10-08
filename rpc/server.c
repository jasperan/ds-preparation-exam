#include <rpc/rpc.h>
#include "interface.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


bool_t
add_99_svc(passer arg1, int *result,  struct svc_req *rqstp)
{
	bool_t retval;
  struct passer args;
  memcpy(&args, arg1, sizeof(struct passer));

  *result = args->a1 + args->a2;

	return retval = TRUE;
}

int
addition_99_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);
	return 1;
}
