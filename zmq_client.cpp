//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <boost/chrono.hpp>
int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect (("tcp://192.168.0.2:5555"));


    std::string exps[6]{"ZF,zf_1k.bin","ZF,zf_10k.bin","ZF,zf_100k.bin","ZF,zf_1m.bin","ZF,zf_10m.bin","ZF,zf_100m.bin"};
    for (int i = 0; i < 5; i++) {
        
	//boost chrono timer
        boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();
        for (int request_nbr = 0; request_nbr != 100000; request_nbr++) {
            zmq::message_t request (exps[i].size());
            memcpy (request.data (), exps[i].c_str(), exps[i].size());
//            std::cout << "Sending " << "ZF zf_10m.bin" << "…" << std::endl;
            socket.send (request);

            //  Get the reply.
            zmq::message_t reply;
            socket.recv (&reply);
//	    std::string replyMessage = std::string(static_cast<char *>(reply.data()), reply.size());
//          std::cout << "Received " << replyMessage << std::endl;
//           std::cout << "Received" << std::endl;
        }
        std::cout << exps[i]  << " time is: "<< boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::steady_clock::now()-start)/100000.0 << std::endl;
    }
    return 0;
}
