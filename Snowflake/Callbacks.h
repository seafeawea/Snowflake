#ifndef SNOWFLAKE_CALLBACKS_H
#define SNOWFLAKE_CALLBACKS_H

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "Buffer.h"

namespace snowflake
{
	class TcpConnection;
	
	typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
	typedef boost::function<void(const TcpConnectionPtr&, muduo::net::Buffer*)> MessageCallback;
}

#endif // !SNOWFLAKE_CALLBACKS_H

