#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char **argv) // socket - sockaddr - connect.
{
  int sc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sc < 0)
  {
    perror("Error declaring socket");
    return -1;
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(atoi(argv[2]));
  server_address.sin_addr.s_addr = inet_aton(argv[1]);
  bzero(&(server_address.sin_zero), 8);

  if (connect_attempt(sc, (struct sockaddr *)server_address, sizeof(struct sockaddr)) < 0)
  {
    perror("Error connecting");
    return -1;
  }
  else
  {
    printf("Successfully connected.\n");
  }

  int firstnum, secondnum;
  read(sc, &firstnum, sizeof(int));
  read(sc, &secondnum, sizeof(int));
  printf("%d\n", firstnum);
  printf("%d\n", secondnum);

}

int connect_attempt(int sc, struct sockaddr * server_address, int num_tries)
{
  int aux;
  for (aux = 0; aux < num_tries; aux++)
  {
    if (connect(sc, server_address, sizeof(struct sockaddr)) < 0)
    {
      sleep(5);
    }
    else return 1;
  }
  return -1; // In case any of the tries has allowed a connection.

}
