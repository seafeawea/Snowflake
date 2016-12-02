// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

//#include <muduo/net/Buffer.h>
#include "Buffer.h"

//#include <muduo/net/SocketsOps.h>

//#include <errno.h>
//#include <sys/uio.h>

#include "Global.h"

using namespace muduo;
using namespace muduo::net;

const char Buffer::kCRLF[] = "\r\n";

const size_t Buffer::kCheapPrepend;
const size_t Buffer::kInitialSize;

void ArrayCopy(char * su, int index, char *des, int index2, int len) {
	for (int i = 0; i<len; i++)
	{
		des[index2 + i] = su[index + i];
	}
}

int Buffer::GetData(char * buf, size_t bytes_transferred)
{
	// saved an ioctl()/FIONREAD call to tell how much to read
	const size_t writable = writableBytes();
	char * write_base = begin();
	
	// when there is enough space in this buffer, don't read into extrabuf.
	// when extrabuf is used, we read 128k-1 bytes at most.

	//const int n = sockets::readv(fd, vec, iovcnt);
	ArrayCopy(buf, 0, write_base, writerIndex_, writable);

	if (implicit_cast<size_t>(bytes_transferred) <= writable)
	{
		writerIndex_ += bytes_transferred;
	}
	else
	{
		writerIndex_ = buffer_.size();
		append(buf + writable, bytes_transferred - writable);
	}
	// if (n == writable + sizeof extrabuf)
	// {
	//   goto line_30;
	// }
	return bytes_transferred;
}

//int Buffer::readFd(int fd, int* savedErrno)
//{
//	// saved an ioctl()/FIONREAD call to tell how much to read
//	char extrabuf[65536];
//	struct iovec vec[2];
//	const size_t writable = writableBytes();
//	vec[0].iov_base = begin() + writerIndex_;
//	vec[0].iov_len = writable;
//	vec[1].iov_base = extrabuf;
//	vec[1].iov_len = sizeof extrabuf;
//	// when there is enough space in this buffer, don't read into extrabuf.
//	// when extrabuf is used, we read 128k-1 bytes at most.
//	const int iovcnt = (writable < sizeof extrabuf) ? 2 : 1;
//	const int n = sockets::readv(fd, vec, iovcnt);
//	if (n < 0)
//	{
//		*savedErrno = errno;
//	}
//	else if (implicit_cast<size_t>(n) <= writable)
//	{
//		writerIndex_ += n;
//	}
//	else
//	{
//		writerIndex_ = buffer_.size();
//		append(extrabuf, n - writable);
//	}
//	// if (n == writable + sizeof extrabuf)
//	// {
//	//   goto line_30;
//	// }
//	return n;
//}

