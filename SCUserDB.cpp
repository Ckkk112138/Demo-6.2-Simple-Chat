#include "SCUserDB.h"

namespace SocketLib
{
	UserDatabase::users UserDatabase::m_users;
	User::User(Connection<Telnet>* p_conn, std::string& p_username)
	{
		connection = p_conn;
		name = p_username;
	}

	UserDatabase::iterator UserDatabase::find(Connection<Telnet>* p_conn)
	{
		UserDatabase::iterator itr = m_users.begin();
		while (itr != m_users.end())
		{
			if (itr->connection == p_conn)
				return itr;
			itr++;
		}
		return itr;
	}

	bool UserDatabase::AddUser(Connection<Telnet>* p_conn, std::string p_name)
	{
		if (!HasUser(p_name) && IsValidName(p_name))
		{
			m_users.push_back(User(p_conn, p_name));
			return true;
		}
		return false;
	}

	void UserDatabase::DeleteUser(Connection<Telnet>* p_conn)
	{
		iterator itr = find(p_conn);
		if (itr != m_users.end())
			m_users.erase(itr);
	}
	bool UserDatabase::HasUser(std::string& p_name)
	{
		iterator itr = m_users.begin();
		while (itr != m_users.end())
		{
			if (itr->name == p_name)
				return true;
		}
		return false;
	}

	bool UserDatabase::IsValidName(const std::string& p_name)
	{
		static std::string invalidChar = " \"'~!@#$%^&*+/\\[]{}<>()=.,?;:";
		if (p_name.find_first_of(invalidChar) != std::string::npos)
		{
			return false;
		}
		if (p_name.size() > 16 || p_name.size() < 3)
			return false;
		if (!std::isalpha(p_name[0]))
			return false;
		return true;
	}
}

