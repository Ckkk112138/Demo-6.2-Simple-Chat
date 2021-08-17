#include "SCChat.h"

namespace SocketLib
{
	SCChat::SCChat(Connection<Telnet>& p_conn)
	:Telnet::handler(p_conn)
	{

	}

	void SCChat::Enter()
	{
		SendAll(bold + yellow + UserDatabase::find(m_connection)->name + " has entered the room.");
	}

	void SCChat::Leave()
	{
		UserDatabase::DeleteUser(m_connection);
	}

	void SCChat::Handle(std::string p_data)
	{
		std::string name = UserDatabase::find(m_connection)->name;
		if (p_data[0] == '/')
		{
			std::string command = BasicLib::ParseWord(p_data, 0);
			std::string data = BasicLib::RemoveWord(p_data, 0);
			if (command == "/who")
			{
				std::string wholist = magenta + bold + "Who is in the room: ";
				UserDatabase::iterator itr = UserDatabase::begin();
				while (itr != UserDatabase::end())
				{
					wholist += (*itr).name;
					++itr;
					if (itr != UserDatabase::end())
						wholist += ", ";
				}
				wholist += newline;
				m_connection->Protocol().SendString(*m_connection, wholist);
			}
			else if (command == "/quit")
			{
				CloseConnection("has quit. Message: " + data);
				m_connection->Close();
			}
		}
		else
		{
			if (BasicLib::TrimWihitespace(p_data).size() > 0)
			{
				SendAll(green + bold + "<" + name + "> " + reset + p_data);
			}
		}
	}

	void SCChat::SendAll(const std::string p_msg)
	{
		UserDatabase::iterator itr = UserDatabase::begin();
		while (itr != UserDatabase::end())
		{
			itr->connection->Protocol().SendString(*itr->connection, p_msg + newline);
			++itr;
		}
	}

	void SCChat::CloseConnection(const std::string p_reason)
	{
		SendAll(bold + red + UserDatabase::find(m_connection)->name + " " + p_reason);
	}
}	
