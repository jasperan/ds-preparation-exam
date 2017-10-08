#include <rpc/rpc.h>
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  if (argc != 4)
  {
    perror("Error arguments");
    return -1;
  }
  if (strlen(argv[1]) > 17)
  {
    perror("Invalid hostname");
    return -1;
  }
  if (atoi(argv[2]) < 0)
  {
    perror("Error first number");
    return -1;
  }
  if (atoi(argv[3]) < 0)
  {
    perror("Error second number");
    return -1;
  }

  int num1, num2;
  char *hostname;
  num1 = atoi(argv[2]);
  num2 = atoi(argv[3]);
  strcpy(hostname, argv[1]);

  CLIENT * clnt = clnt_create(hostname, 1, 99, "TCP");
  if (clnt == NULL)
  {
    clnt_pcreateerror(hostname);
    return -1;
  }
  enum clnt_stat retval;

  struct passer * args = (struct passer * )malloc(sizeof(struct passer));
  args->a1 = num1;
  args->a2 = num2;
  int result;
  retval = add_99(args, &result, clnt);
  if (retval != RPC_SUCCESS)
  {
    perror("Error with RPC call");
    return -1;
  }

  printf("Correct result is %d\n", result);


  clnt_destroy(clnt);
}
