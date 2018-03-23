#include <iostream>
#include <memory>
#include <string>
#include <boost/chrono.hpp>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "protos/basicrpc.grpc.pb.h"
#else
#include "basicrpc.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using basicrpc::ZeroRequest;
using basicrpc::ZeroReply;
using basicrpc::Executor;

class FSClient {
 public:
  FSClient(std::shared_ptr<Channel> channel)
      : stub_(Executor::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string ZeroFile(const std::string& fname) {
    // Data we are sending to the server.
    ZeroRequest request;
    request.set_fname(fname);
    request.set_operation("ZeroFile");
    // Container for the data we expect from the server.
    ZeroReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->ZeroFile(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }
 private:
  std::unique_ptr<Executor::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  FSClient fsc(grpc::CreateChannel(
      "192.168.0.2:50051", grpc::InsecureChannelCredentials()));
  std::string exps[6]{"/mnt/mem/zf_1k.bin","/mnt/mem/zf_10k.bin","/mnt/mem/zf_100k.bin","/mnt/mem/zf_1m.bin","/mnt/mem/zf_10m.bin","ZF,/mnt/mem/100m.bin"};

  for (int i = 0; i < 5; i++) {
    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();
    std::string fname(exps[i]);
    for (int request_nbr = 0; request_nbr != 10000; request_nbr++) {
      std::string reply = fsc.ZeroFile(fname);
    }
    std::cout << exps[i]  << " time is: "<< boost::chrono::steady_clock::now()-start << std::endl;
  }
  return 0;
}
