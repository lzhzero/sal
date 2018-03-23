#include <iostream>
#include <memory>
#include <string>
#include <boost/chrono.hpp>
#include <zmq.hpp>

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
//  FSClient fsc(grpc::CreateChannel(
//      "192.168.0.2:50051", grpc::InsecureChannelCredentials()));

  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ);
  socket.connect ("tcp://192.168.0.2:6666");
  std::string exps[6]{"/mnt/mem/zf_1k.bin","/mnt/mem/zf_10k.bin","/mnt/mem/zf_100k.bin","/mnt/mem/zf_1m.bin","/mnt/mem/zf_10m.bin","ZF,/mnt/mem/100m.bin"};

  for (int i = 0; i < 5; i++) {
    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();
//    std::string fname(exps[i]);
//    zmq::message_t request (exps[i].size());
//    memcpy(request.data(), exps[i].c_str(),exps[i].size());
//    zmq::message_t reply;
    for (int request_nbr = 0; request_nbr != 10000; request_nbr++) {
      std::string fname(exps[i]);
      zmq::message_t request (exps[i].size());
      memcpy(request.data(), exps[i].c_str(),exps[i].size());
      zmq::message_t reply;
      socket.send(request);
      socket.recv(&reply);
    }
    std::cout << exps[i]  << " time is: "<< boost::chrono::steady_clock::now()-start << std::endl;
  }
  return 0;
}
