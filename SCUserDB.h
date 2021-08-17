#ifndef SCUSERDB_H
#define SCUSERDB_H

#include <string>
#include <list>
#include "Connection.h"
#include "Telnet.h"

namespace SocketLib
{
	class User
	{
	public:
		std::string name;
		Connection<Telnet>* connection;
	public:
		User();
		User(Connection<Telnet>* p_conn, std::string& p_username);
	};



	class UserDatabase
	{
	public:
		typedef std::list<User> users;
		typedef std::list<User>::iterator iterator;
	protected:
		static users m_users;
	public:

		inline static iterator begin()
		{
			return m_users.begin();
		}
		inline static iterator end()
		{
			return m_users.end();
		}
		static iterator find(Connection<Telnet>* p_conn);
		static bool AddUser(Connection<Telnet>* p_conn, std::string p_username);
		static void DeleteUser(Connection<Telnet>* p_conn);
		static bool HasUser(std::string& p_username);
		static bool IsValidName(const std::string& p_username);
	};
}

#endif // !SCUSERDB_H

