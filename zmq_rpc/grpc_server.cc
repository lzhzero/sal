#include <iostream>
#include <memory>
#include <string>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <grpc++/grpc++.h>
#define min(x,y)  ( x<y?x:y )

#ifdef BAZEL_BUILD
#include "protos/basicrpc.grpc.pb.h"
#else
#include "basicrpc.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using basicrpc::ZeroRequest;
using basicrpc::ZeroReply;
using basicrpc::Executor;

// Logic and data behind the server's behavior.
class ExecutorServiceImpl final : public Executor::Service {
  Status ZeroFile(ServerContext* context, const ZeroRequest* request,
                  ZeroReply* reply) override {
    
    if (request->operation() == "ZeroFile"){
      zero_file(request->fname().c_str());
      reply->set_message("zero done");
    }
    else reply->set_message("only accepting ZeroFile command");

    return Status::OK;
  }

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
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  ExecutorServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
