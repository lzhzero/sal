#include <iostream>
#include <memory>
#include <string>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <zmq.hpp>
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


void ZmqMode() {
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind("tcp://*:6666");
//  zmq::message_t reply (2);
//  memcpy(reply.data(), "OK",2);
  while (true) {
    zmq::message_t request;
    socket.recv(&request);
    std::string s(static_cast<char*>(request.data()), request.size());
//    std::cout<< s  << std::endl;
    zero_file(s.c_str());    
    zmq::message_t reply (2);
    memcpy(reply.data(), "OK",2);
    socket.send(reply);
  }
}
int main(int argc, char** argv) {
//  RunServer();
  ZmqMode();
  return 0;
}
