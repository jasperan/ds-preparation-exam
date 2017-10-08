/*

3GChat - mesage service for mobile devices. all messages pass through HQ

Develop using sockets

Who are clients/servers:
- In the most part of the message exchange, the servers would be the set of computers in the 3gchat headquarters, as they are the passive part, receiving the messages from a client initially. Afterwards, they will act as a client for sending information to the respective recipient of the message; as well as for sending the notifications for pending messages to the recipients. However, this action is caused by the initial passive nature of the servers.
- The clients will be the set of users in the system, sending messages, acting as the active part.

Protocol:

- As the message order for a client is important (since, otherwise, users could get confused by messages not arriving in-order) we will use TCP as our transport protocol.

Naming:

Clients:
192.168.0.1 port 2048
192.168.0.2 port 2048
192.68.0.3 port 2048

192.168.0.4 Listening server address, one port for each of the clients. (to allow concurrency)

Server features
- Multithreaded to allow multiple clients to send messages at the same time, in order for the server to be able to process them concurrently, as well as sending them concurrently.
- Stateful, as it shall preserve the identifier for each one of the connected users in the network, as well as the listening sport for each one of these users.

Security.
- We need tyo implement some kind of security / encryption for the sending of the messageas, as well as an authenticatyion mechanism to prevent man in the middle attacks between users.

Messages

struct message_req
{
	int sender;
	int recipient;
	char message[256];
	int opcode;
	int size_photo;
	char photo[MAX_SIZE_PHOTO];
};

struct message_res
{
	char res;
	int error_code;
};

struct req_processing
{
	int recipient;
	char message[256];
	int sender;
	char photo[MAX_SIZE_PHOTO];
	int size_photo;
};

struct notify
{
	int recipient;
	int type_content;
};

*/



#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_SIZE_PHOTO 9192;

int main(int argc, char **argv)
{
  // Server:
}
