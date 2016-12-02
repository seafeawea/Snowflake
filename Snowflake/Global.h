#ifndef SNOWFLAKE_GLOBAL_H
#define SNOWFLAKE_GLOBAL_H

#define MUDUO_STD_STRING

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

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

}
#endif