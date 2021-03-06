#include <string>
#include "SocketLibSocket.h"

namespace SocketLib
{
	void Socket::Close()
	{
#ifdef WIN32
		closesocket(m_sock);
#else
		colse(m_sock);
#endif // WIN32
		m_sock = -1;

	}

	void Socket::SetBlocking(bool p_bolckmode)
	{
		int err;
#ifdef WIN32
		unsigned long mode = !p_bolckmode;
		err = ioctlsocket(m_sock, FIONBIO, &mode);
#else
		int flags = fcntl(m_sock, F_GETFL, 0);
		if (p_bolckmode == false)
		{
			flags |= O_NONBLOCK;
		}
		else
		{
			flags &= ~O_NONBLOCK;
		}
		err = fcntl(m_sock, F_SETFL, flags);

#endif // DEBUG
		if (err == -1)
		{
			throw (Exception(GetError()));
		}
		m_isblocking = p_bolckmode;

	}

	Socket::Socket(sock p_socket):m_sock(p_socket)
	{
		if (p_socket != -1)
		{
			socklen_t s = sizeof(m_localinfo);
			getsockname(p_socket, (sockaddr*)(&m_localinfo), &s);
		}

		m_isblocking = true;
	}

	DataSocket::DataSocket(sock p_socket)
		:Socket(p_socket),m_connected(false)
	{
		if (p_socket != -1)
		{
			socklen_t s = sizeof(m_remoteinfo);
			getpeername(p_socket, (sockaddr*)&m_remoteinfo, &s);
			m_connected = true;

		}
		
	}	
	void DataSocket::Connect(ipaddress p_addr, port p_port)
	{
		int err;
		if (m_connected == true)
		{
			throw Exception(EAlreadyConnected);
		}

		if (m_sock == -1)
		{
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (m_sock == -1)
			{
				throw Exception(GetError());
			}
		}
		m_remoteinfo.sin_family = AF_INET;
		m_remoteinfo.sin_port = htons(p_port);
		m_remoteinfo.sin_addr.S_un.S_addr = p_addr;
		memset(&(m_remoteinfo.sin_zero), 0, 8);

		socklen_t s = sizeof(struct sockaddr);
		err = connect(m_sock, (sockaddr*)&m_remoteinfo, s);
		if (err == -1)
		{
			throw Exception(GetError());
		}
		m_connected = true;

		err = getsockname(m_sock, (sockaddr*)&m_localinfo, &s);
		if (err != 0)
		{
			throw Exception(GetError());
		}
	}

	int DataSocket::Send(const char* p_buffer, int p_size)
	{
		int err;
		if (!m_connected)
		{
			throw Exception(ENotConnected);
		}
		err = send(m_sock, p_buffer, p_size, 0);
		if (err == -1)
		{
			Error e = GetError();
			if (e != EOperationWouldBlock)
			{
				throw Exception(e);
			}
			err = 0;
		}
		return err;
	}

	int DataSocket::Receive(char* p_buffer, int p_size)
	{
		int err;
		if (!m_connected)
		{
			throw Exception(ENotConnected);
		}

		err = recv(m_sock, p_buffer, p_size, 0);
		if (err == 0)
		{
			throw Exception(EConnectionClosed);
		}
		if (err == -1)
		{
			throw Exception(GetError());
		}

		// return the number of bytes successfully received
		return err;
	}

	void DataSocket::Close()
	{
		if (m_connected)
		{
			shutdown(m_sock, 2);
		}
		Socket::Close();
		m_connected = false;
	}

	void ListeningSocket::Listen(port p_port)
	{
		int err;
		if (m_sock == -1)
		{
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (m_sock == -1)
			{
				throw Exception(GetError());
			}
		}
		int reuse = 1;
		err = setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
		if (err != 0)
		{
			throw Exception(GetError());
		}

		m_localinfo.sin_family = AF_INET;
		m_localinfo.sin_port = htons(p_port);
		m_localinfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		memset(&(m_localinfo.sin_zero), 0, 8);

		err = bind(m_sock, (sockaddr*)&m_localinfo, sizeof(sockaddr));
		if (err == -1)
		{
			throw Exception(GetError());
		}

		err = listen(m_sock, 8);
		if (err == -1)
		{
			throw Exception(GetError());
		}
		m_listening = true;

	}

	DataSocket ListeningSocket::Accept()
	{
		sock s;
		sockaddr_in socketaddress;
		socklen_t size = sizeof(sockaddr);
		s = accept(m_sock, (sockaddr*)&socketaddress, &size);
		if (s == -1)
		{
			throw Exception(GetError());
		}
		return DataSocket(s);
	}

	void ListeningSocket::Close()
	{
		Socket::Close();
		m_listening = false;
	}

	ListeningSocket::ListeningSocket()
	{
		m_listening = false;
	}
}