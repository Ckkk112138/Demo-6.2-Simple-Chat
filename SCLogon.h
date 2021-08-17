#ifndef SCLOGON_H
#define SCLOGON_H

#include "Telnet.h"
#include "SocketLibErrors.h"
#include "SCUserDB.h"
#include "SCChat.h"


namespace SocketLib
{
	class SCLogon : public Telnet::handler
	{
	public:
		SCLogon(Connection<Telnet>& p_conn);
		void Handle(std::string p_data);
		void Enter();
		void Leave() {};
		void Hungup() {};
		void Flooded() {};
		static void NoRoom(Connection<Telnet>& p_conn);

	};
}
#endif // !SCLOGON_H

