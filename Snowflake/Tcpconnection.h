#ifndef SNOWFLAKE_TcpConnection_H
#define SNOWFLAKE_TcpConnection_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "Global.h"
#include "Buffer.h"
#include "Callbacks.h"

#include <string>

using namespace std;
using namespace muduo::net;

#define MAX_NETBUFFER_SIZE 5120

namespace snowflake
{
	

	class TcpConnection : boost::noncopyable, public boost::enable_shared_from_this<TcpConnection>
	{
	public:
		TcpConnection(SockPtr socket, MessageCallback readcallback);
		~TcpConnection();

		void send(const string& message);
		
		void asyncRead();

	private:
		void TcpConnection::sendCallback(boost::system::error_code ec);
		void socketAsyncReadHandle(const boost::system::error_code& error, std::size_t bytes_transferred);

		enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

		StateE state_;  // FIXME: use atomic variable
		SockPtr	socket_;
		Buffer inputBuffer_;
		Buffer outputBuffer_; 
		char	asyncBuffer_[MAX_NETBUFFER_SIZE];
		MessageCallback readCallback_;
	};

	

	typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

}

#endif