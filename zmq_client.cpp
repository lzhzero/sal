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
    socket.connect ("tcp://localhost:5555");

    //boost chrono timer
    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();


    for (int request_nbr = 0; request_nbr != 10000; request_nbr++) {
        zmq::message_t request (15);
        memcpy (request.data (), "ZF,zf_1k.bin", 15);
//        std::cout << "Sending " << "ZF zf_10m.bin" << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
//	std::string replyMessage = std::string(static_cast<char *>(reply.data()), reply.size());
//        std::cout << "Received " << replyMessage << std::endl;
    }
    std::cout << boost::chrono::steady_clock::now()-start << std::endl;
    return 0;
}
