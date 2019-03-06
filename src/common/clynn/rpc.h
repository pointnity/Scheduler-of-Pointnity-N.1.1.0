/********************************
 FileName: common/clynn/rpc.h


 Version:  0.1
 Description: rpc with thrift 
*********************************/

#ifndef COMMON_RPC_H
#define COMMON_RPC_H

#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>
#include <transport/TServerSocket.h>
#include <transport/TTransportUtils.h>
#include <transport/TSocket.h>

#include <string>

#include <sys/types.h>
#include <dirent.h>

using std::string;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

using boost::shared_ptr;

template <typename T>
class Proxy {
public:
    Proxy(const T& client, const shared_ptr<TTransport>& connector)
    : m_client(client), m_connector(connector) {
        m_connector->open();
    }

    ~Proxy() {
        m_connector->close();  
    }
    
    /// @brief: overwrite ()
    T& operator()() {
        return m_client;
    }
private:
    T m_client;
    shared_ptr<TTransport> m_connector;
};

//duprecated
template <typename T, typename P>
class Rpc {
public:
    //TODO move the configuration out of here into a single file
    static const int DEFAULT_THREAD_NUM = 4;
    static const int TIME_OUT = 2000;

    static void Listen(int port) {

        shared_ptr<T> handler(new T);
        shared_ptr<TProcessor> processor(new P(handler));
        shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
        shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
        shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
        
        //Single-threaded server
        /*  
        TSimpleServer server(processor,  
                            serverTransport,  
                            transportFactory,  
                            protocolFactory);  
        */
        
        //Each request is processed by one thread
        TThreadedServer server(processor, 
                               serverTransport, 
                               transportFactory, 
                               protocolFactory); 
        
        //Thread pool enabled
        /* 
        //It is easy to hang when 13 physical machines are started.
        shared_ptr<ThreadManager> threadManager =
            ThreadManager::newSimpleThreadManager(DEFAULT_THREAD_NUM);
        shared_ptr<PosixThreadFactory> thread_factory(new PosixThreadFactory());
        threadManager->threadFactory(thread_factory);
        threadManager->start();
        TThreadPoolServer server(processor,
                                 serverTransport,
                                 transportFactory,
                                 protocolFactory,
                                 threadManager);
        */

        server.serve();
    }

    static Proxy<T> GetProxy(const string& endpoint, int timeout = TIME_OUT) {
        // split endpoint into ip and port
        string ip = endpoint.substr(0, endpoint.find(":"));
        string str_port = endpoint.substr(endpoint.find(":") + 1);
        int port = atoi(str_port.c_str());
        TSocket* sc = new TSocket(ip, port);
