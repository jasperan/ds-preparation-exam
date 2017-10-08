#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>

struct thread_args{
  int arg1;
  int arg2;
  int socket_client;
  struct sockaddr_in client_address;
  size_t len_address;
};

pthread_t thid;
pthread_attr_t attr;
pthread_mutex_t mutex;
pthread_cond_t cond;
int isfinished;

int main(int argc, char ** argv) // socket, sockaddr, bind, listen, accept.
{
  int listening_socket = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in client_address;
  // Imagine I get server address from argv[1];
  memset((char*)&client_address, 0, sizeof(struct sockaddr_in));
  if (argc != 2)
  {
    perror("Invalid number of arguments");
    return -1;
  }

  else if (atoi(argv[2]) < 1024 || atoi(argv[2]) > 65535)
  {
    perror("Invalid port number specified");
    return -1;
  }

  client_address.sin_addr.s_addr = INADDR_ANY;
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(atoi(argv[2]));
  bzero(&(client_address.sin_zero), 8);



  if (bind(listening_socket, (struct sockaddr *)&client_address, sizeof(struct sockaddr)) < 0)
  {
    perror("Error binding server address");
    return -1;
  }

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


  while (1)
  {
    int value_received;
    recvfrom(listening_socket, &value_received, sizeof(int), 0, NULL, NULL);

    struct thread_args * args = (struct thread_args * )malloc(sizeof(struct thread_args));
    args->arg1 = value_received;
    args->socket_client = socket_client;
    args->client_address = client_address;
    size_t len_address = sizeof(socklen_t);
    args->len_address = len_address;

    pthread_create(&thid, &attr, (void*)thread, (void*)args);

    pthread_mutex_lock(&mutex);
    while (isfinished == 0)
    {
      pthread_cond_wait(&cond, &mutex);
    }
    isfinished = 0;
    free(args);
    pthread_mutex_unlock(&mutex);
  }
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
  pthread_attr_destroy(&attr);
}

void thread (void * args)
{
  pthread_mutex_lock(&mutex);
  struct thread_args * arguments;
  memcpy(arguments, &args, sizeof(struct thread_args));
  isfinished = 1;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  free(arguments);

  int num1, num2;
  num1 = args->arg1;
  num2 = args->arg2;

  if (sendto(args->socket_client, &num1, sizeof(int), 0, (struct sockaddr *)args->client_address, (socklen_t *)&args->len_address) < 0)
  {
    perror("Error sending");
    return;
  }

}
