#ifndef SCCHAT_H
#define SCCHAT_H

#include "Telnet.h"
#include "SCUserDB.h"

namespace SocketLib
{
	class SCChat : public Telnet::handler
	{
	public:
		SCChat(Connection<Telnet>& p_conn);
		void Handle(std::string p_data);
		void Enter();
		void Leave();
		void Hungup()
		{
			CloseConnection("has hung up!");
		}
		void Flooded()
		{
			CloseConnection("has been kicked for flooding!");
		}
		void CloseConnection(const std::string p_reason);
		void SendAll(const std::string p_data);


	};
}
#endif // !SCCHAT_H

