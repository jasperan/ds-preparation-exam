#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>


// Process a number, and print it.
pthread_cond_t cond;
pthread_t thid;
int isfinished = 0;
pthread_mutex_t mutex;
pthread_attr_t attr;

void thread(int * info);

int main(int argc, char **argv)
{
  if (pthread_cond_init(&cond, NULL) != 0)
  {
    perror("Error cond init");
    return -1;
  }

  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
    perror("Error mutex init");
    return -1;
  }

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  struct mq_attr at;
  at.mq_msgsize = sizeof(int);
  at.mq_maxmsg = 10;

  mqd_t mq_id_server;
   mq_id_server = mq_open("/server_queue", O_CREAT|O_RDONLY, 0777, at);
   if (mq_id_server < 0)
   {
     perror("Error opening queue");
     return -1;
   }
  mqd_t mq_id_client;
   mq_id_client = mq_open("/client_queue", O_WRONLY, 0777, 0);
   if (mq_id_client < 0)
   {
     perror("Error opening queue");
     return -1;
   }

    while (1)
    {
      int storer;
      pthread_mutex_lock(&mutex);
      if (mq_receive(mq_id_server, (char*)storer, sizeof(int), 0) < 0) // 0 is priority in mq_receive, mq_send.
      {
        perror("Error receiving integer.");
        return -1;
      }
      pthread_create(&thid, &attr, (void*)thread, &storer);
      pthread_mutex_unlock(&mutex);

      // Got the integer in var 'storer'.
      pthread_mutex_lock(&mutex);
      while (isfinished == 0)
      {
        pthread_cond_wait(&cond, &mutex);
      }
      isfinished = 0;
      pthread_mutex_unlock(&mutex);

    }
    mq_close(mq_id_server);
    mq_close(mq_id_client);
    mq_unlink(mq_id_server);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_attr_destroy(&attr);
}

void thread(int * info)
{
  pthread_mutex_lock(&mutex);
  int val = *info;
  isfinished = 1;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);

  if (mq_send(mq_id_server, (char*)&val, sizeof(int), 0) < 0)
  {
    perror("Error sending return value");
  }
  pthread_exit(0);
}
