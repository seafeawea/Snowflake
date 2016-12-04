#include "TcpConnection.h"

namespace snowflake
{

	TcpConnection::TcpConnection(SockPtr socket, MessageCallback readcallback) :state_(kConnected), socket_(socket), readCallback_(readcallback)
	{
	}

	TcpConnection::~TcpConnection()
	{
		assert(state_ == kDisconnected);
	}

	void TcpConnection::send(const string& message)
	{
		if (state_ == kConnected)
		{
			assert(socket_->is_open());
			socket_->async_write_some(boost::asio::buffer(message), boost::bind(&TcpConnection::sendCallback, shared_from_this(), _1));
		}
	}

	void TcpConnection::sendCallback(boost::system::error_code ec)
	{
		if (ec)
		{
			state_ = kDisconnected;
			return;
		}
	}

	void TcpConnection::asyncRead() {
		socket_->async_read_some(
			boost::asio::buffer(this->asyncBuffer_, MAX_NETBUFFER_SIZE),
			boost::bind(&TcpConnection::socketAsyncReadHandle, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void TcpConnection::socketAsyncReadHandle(const boost::system::error_code& ec, std::size_t bytes_transferred)
	{
		if (ec == boost::asio::error::eof || ec == ((boost::asio::error::basic_errors)10054) || ec == ((boost::asio::error::basic_errors)10009) || ec == ((boost::asio::error::basic_errors)995))
		{
			state_ = kDisconnected;
			return;
		}

		assert(ec == 0);

		inputBuffer_.GetData(asyncBuffer_, bytes_transferred);
		readCallback_(shared_from_this(), &inputBuffer_);

		asyncRead();
	}

}