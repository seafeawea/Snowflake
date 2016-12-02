#include "Tcpconnection.h"

void tcpconnection::socketAsyncReadHandle(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
	if (ec == boost::asio::error::eof || ec == ((boost::asio::error::basic_errors)10054) || ec == ((boost::asio::error::basic_errors)10009) || ec == ((boost::asio::error::basic_errors)995))
	{
		return;
	}

	inputBuffer_.GetData(asyncBuffer_,  bytes_transferred);
	readCallback_(shared_from_this(), &inputBuffer_);

	asyncRead();
}