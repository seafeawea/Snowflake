#ifndef SNOWFLAKE_GLOBAL_H
#define SNOWFLAKE_GLOBAL_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
//#include "Buffer.h"

using namespace boost::asio;
using namespace boost::asio::ip;
//using namespace muduo::net;

namespace snowflake
{

	typedef tcp::acceptor						acceptor_type;
	typedef tcp::endpoint						endpoint_type;
	typedef tcp::socket							socket_type;
	typedef boost::shared_ptr<socket_type>		SockPtr;

	//typedef boost::function<void(const TcpConnectionPtr&, Buffer*)> MessageCallback;

}
#endif