#include "SCLogon.h"

namespace SocketLib
{
	SCLogon::SCLogon(Connection<Telnet>& p_conn)
	:Telnet::handler(p_conn)
	{

	}
	void SCLogon::NoRoom(Connection<Telnet>& p_conn)
	{
		static std::string msg = "Sorry, there is no more room on this server.\r\n";
		try
		{
			p_conn.Send(msg.c_str(), (int)msg.size());
		}
		catch (Exception)
		{

		}

	}

	void SCLogon::Enter()
	{
		m_connection->Protocol().SendString(*m_connection, green + bold +
			"Welconme To SimpleChat!\r\n" + "Please enter your username: " + reset + bold);

	}

	void SCLogon::Handle(std::string p_data)
	{
		Connection<Telnet>* conn = m_connection;
		if (!UserDatabase::IsValidName(p_data))
		{
			conn->Protocol().SendString(*conn, red + bold + "Sorry, that is an invalid username.\r\n" +
				"Please enter another username: " + reset + bold);
			return;
		}
		if (UserDatabase::HasUser(p_data))
		{
			conn->Protocol().SendString(*conn, red + bold + "Sorry, that is already in use.\r\n" +
				"Please enter another username: " + reset + bold);
			return;
		}
		UserDatabase::AddUser(conn, p_data);
		conn->Protocol().SendString(*conn, "Thank you for joining us, " + p_data + newline);
		conn->RemoveHandler();
		conn->AddHandler(new SCChat(*conn));
	}	
}