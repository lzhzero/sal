//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
//#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <boost/chrono.hpp>
#define min(x,y)  ( x<y?x:y )

int zero_file(const char *filename) {
  FILE *file;
  int res;
  char str[100];

  strcpy(str, filename);
//  strcpy(str, "/working/");
//  strcat(str, filename);
  int fd;
//  char buf[4096];
  char buf[32786];
  struct stat st;
  off_t pos;
  ssize_t written;
  memset(buf, 0, 32786);
  fd = open(str, O_WRONLY);
  fstat(fd, &st);

  for(pos=0; pos < st.st_size; pos+=written)
    if ((written = write(fd, buf, min(st.st_size - pos, 32786))) <= 0)
      break;

  fsync(fd);
  close(fd);
  return 0;
}

int main ()
{
    //  Prepare our context and socket
//    zmq::context_t context (1);
//    zmq::socket_t socket (context, ZMQ_REQ);

//    std::cout << "Connecting to hello world server…" << std::endl;
//    socket.connect (("tcp://128.104.222.24:5555"));


    std::string exps[6]{"/mnt/nbd/zf_1k.bin","/mnt/nbd/zf_10k.bin","/mnt/nbd/zf_100k.bin","/mnt/nbd/zf_1m.bin","/mnt/nbd/zf_10m.bin","ZF,/mnt/nbd/100m.bin"};
    for (int i = 0; i < 5; i++) {
        
	//boost chrono timer
        boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();
        for (int request_nbr = 0; request_nbr != 10000; request_nbr++) {
///            zmq::message_t request (15);
///            memcpy (request.data (), exps[i].c_str(), 15);
//            std::cout << "Sending " << "ZF zf_10m.bin" << "…" << std::endl;
///            socket.send (request);

            //  Get the reply.
///            zmq::message_t reply;
///            socket.recv (&reply);
//	    std::string replyMessage = std::string(static_cast<char *>(reply.data()), reply.size());
//          std::cout << "Received " << replyMessage << std::endl;
//           std::cout << "Received" << std::endl;
        zero_file(exps[i].c_str());
	}
        std::cout << exps[i]  << " time is: "<< boost::chrono::steady_clock::now()-start << std::endl;
    }
    return 0;
}
