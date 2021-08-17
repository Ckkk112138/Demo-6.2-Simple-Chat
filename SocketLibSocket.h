#ifndef SOCKETLIBSOCKET_H
#define SOCKETLIBSOCKET_H

#include "BasicLib.h"
#include "SocketLibTypes.h"
#include "SocketLibErrors.h"


namespace SocketLib
{
	class Socket
	{
	protected:
		Socket(sock p_socket = -1);
		sock m_sock;
		struct sockaddr_in m_localinfo;
		bool m_isblocking;
	public:
		inline sock GetSock() const
		{
			return m_sock;
		}

		inline port GetLocalPort() const
		{
			return ntohs(m_localinfo.sin_port);
		}

		inline ipaddress GetLocalAddress() const
		{
			return m_localinfo.sin_addr.S_un.S_addr;
		}

		void Close();
		void SetBlocking(bool p_blockmode);

	};

	class DataSocket : public Socket
	{
	protected:
		bool m_connected;

		// about the remote connection addr;
		struct  sockaddr_in m_remoteinfo;

	public:
		DataSocket(sock p_socket = -1);
		inline ipaddress GetRemoteAddress() const
		{
			return m_remoteinfo.sin_addr.S_un.S_addr;
		}

		inline port GetRemotePort() const
		{
			return ntohs(m_remoteinfo.sin_port);
		}

		inline bool IsConnected() const
		{
			return m_connected;
		}

		void Connect(ipaddress p_addr, port p_port);
		int Send(const char* p_buffer, int p_size);
		int Receive(char* p_buffer, int p_size);
		void Close();
		
	};

	class ListeningSocket : public Socket
	{
	protected:
		bool m_listening;
	public:
		ListeningSocket();
		void Listen(port p_port);
		DataSocket Accept();
		inline bool IsListening() const
		{
			return m_listening;
		}
		void Close();
	};

};

#endif // !SOCKETLIBSOCKET_H

