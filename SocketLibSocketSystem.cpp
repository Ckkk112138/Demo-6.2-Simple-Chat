#include "SocketLibSystem.h"
#include "SocketLibErrors.h"

#pragma warning(disable:4996)
namespace SocketLib
{
#ifdef WIN32
	class System
	{
	protected:
		WSADATA m_WSAData;
	public:
		System()
		{
			WSAStartup(MAKEWORD(2, 2), &m_WSAData);
		}

		~System()
		{
			WSACleanup();
		}
	};

	System g_system;
#endif // WIN32

	bool IsIPAddress(const std::string p_address)
	{
		for (size_t i = 0; i < p_address.length(); ++i)
		{
			if ((p_address[i] < '0' || p_address[i] > '9') && p_address[i] != '.')
			{
				return false;
			}
			
		}
		return true;
	}

	ipaddress GetIPAddress(const std::string p_address)
	{
		if (IsIPAddress(p_address))
		{
			ipaddress addr = inet_addr(p_address.c_str());
				if (addr == INADDR_NONE)
				{
					throw Exception(EDNSNotFound);
			}
			return addr;
		}
		else
		{

			hostent* host = gethostbyname(p_address.c_str());
			if (host == 0)
			{
				throw Exception(GetError(false));
			}
			return *((ipaddress*)host->h_addr);
		}
		
	}

	std::string GetIPString(ipaddress p_address)
	{
		char* str = inet_ntoa(*((in_addr*)&p_address));
		if (str == 0)
		{
			return std::string("Invalid IP Address");
		}
		return std::string(str);
	}

	std::string GetHostNameString(ipaddress p_address)
	{
		hostent* host = gethostbyaddr((char*)&p_address, 4, AF_INET);
		if (host == 0)
		{
			throw Exception(GetError(false));
		}
		return std::string(host->h_name);
	}

}