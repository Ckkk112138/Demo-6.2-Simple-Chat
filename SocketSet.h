#ifndef SOCKETSET_H
#define SOCKETSET_H

#include "BasicLib.h"
#include "SocketLibTypes.h"
#include "SocketLibSocket.h"
#include <set>

namespace SocketLib
{
	const int MAX = FD_SETSIZE;

	class SocketSet
	{
	protected:
		fd_set m_set;
		fd_set m_activityset;

		// for linux only since select()
		// in linux require the largest decriptor+1
#ifndef WIN32
		std::set<sock> m_socketdescs;
#endif
	public:
		SocketSet();
		void AddSocket(const Socket& p_sock);
		void RemoveSocket(const Socket& p_sock);
		inline int Poll(long p_time = 0)
		{
			// how long will select() wait
			struct timeval t = { 0,p_time * 1000 };

			m_activityset = m_set;
#ifdef WIN32
			return select(0, &m_activityset, 0, 0, &t);
#else
			if (m_socketdescs.size() == 0)
				return 0;
			return select(*(m_socketdescs.rbegin()) + 1; &m_activityset, 0, 0, &t);
#endif // WIN32

						 
		}

		inline bool HasActivity(const Socket& p_sock)
		{
			return FD_ISSET(p_sock.GetSock(), &m_activityset) != 0;
		}
	};
}
#endif
