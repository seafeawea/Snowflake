#ifndef SNOWFLAKE_TCPCONNECTION_H
#define SNOWFLAKE_TCPCONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Global.h"
#include "Buffer.h"

#include <string>

using namespace std;
using namespace muduo::net;

#define MAX_NETBUFFER_SIZE 5120

namespace snowflake
{
	class tcpconnection : boost::noncopyable, public boost::enable_shared_from_this<tcpconnection>
	{
	public:
		tcpconnection();
		~tcpconnection();

		void send(const string& message);
		void socketAsyncReadHandle(const boost::system::error_code& error, std::size_t bytes_transferred);
		void asyncRead() {
			socket_->async_read_some(
				boost::asio::buffer(this->asyncBuffer_, MAX_NETBUFFER_SIZE), 
				boost::bind(&tcpconnection::socketAsyncReadHandle, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}

	private:
		SockPtr	socket_;
		Buffer inputBuffer_;
		Buffer outputBuffer_; 
		char	asyncBuffer_[MAX_NETBUFFER_SIZE];
	};

	tcpconnection::tcpconnection()
	{
	}

	tcpconnection::~tcpconnection()
	{
	}

	typedef boost::shared_ptr<tcpconnection> TcpConnectionPtr;
}

#endif