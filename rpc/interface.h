

#ifndef _INTERFACE_H_RPCGEN
#define _INTERFACE_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct passer {
	int a1;
	int a2;
};
typedef struct passer passer;

#define ADDITION 1
#define VERSION_ADDITION 99

#if defined(__STDC__) || defined(__cplusplus)
#define add 1
extern  enum clnt_stat add_99(passer , int *, CLIENT *);
extern  bool_t add_99_svc(passer , int *, struct svc_req *);
extern int addition_99_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define add 1
extern  enum clnt_stat add_99();
extern  bool_t add_99_svc();
extern int addition_99_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_passer (XDR *, passer*);

#else /* K&R C */
extern bool_t xdr_passer ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_INTERFACE_H_RPCGEN */
