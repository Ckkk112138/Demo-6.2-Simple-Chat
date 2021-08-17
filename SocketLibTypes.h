#ifndef SOCKETLIBTYPES_H
#define SOCKETLIBTYPES_H

#ifdef WIN32               
#include "Ws2tcpip.h"

#ifndef socklen_t
typedef int socklen_t;
#endif

#else                       // UNIX/Linux
#include <sys/types.h>      // header containing all basic data types and
// typedefs
#include <sys/socket.h>     // header containing socket data types and
                            // functions
#include <netinet/in.h>     // IPv4 and IPv6 stuff
#include <unistd.h>         // for gethostname()
#include <netdb.h>          // for DNS - gethostbyname()
#include <arpa/inet.h>      // contains all inet_* functions
#include <errno.h>          // contains the error functions
#include <fcntl.h>          // file control
#endif

namespace SocketLib
{
#ifdef WIN32
    typedef SOCKET sock;
#else
    typedef int sock;
#endif // WIN32

    typedef unsigned short int port;
    typedef unsigned long int ipaddress;

}

#endif // !SOCKETLIBTYPES_H

