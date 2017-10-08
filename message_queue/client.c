#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
  mqd_t mq_id_server;
  mqd_t mq_id_client;

  struct mq_attr attr;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = sizeof(int);

  mq_id_client = mq_open("/client_queue", O_CREAT|O_RDONLY, 0777, attr);
  if (mq_id_client < 0)
  {
    perror("Error opening queue");
    return -1;
  }
  mq_id_server = mq_open("/server_queue", O_WRONLY, 0777, 0);
  if (mq_id_server < 0)
  {
    perror("Error opening queue");
    return -1;
  }
  int number = 3;
  if (mq_send(mq_id_server, (char*)number, sizeof(int), 0) < 0)
  {
    perror("Error sending with message queue");
    return -1;
  }
  int storer;
  if(mq_receive(mq_id_client, (char*)storer, sizeof(int), 0) < 0)
  {
    perror("Error receiving with message queue");
    return -1;
  }
  mq_close(mq_id_client);
  mq_close(mq_id_server);
  mq_unlink(mq_id_client);
}
