#include "BasicLib.h"

namespace BasicLib
{
#ifdef WIN32
	class Win32PerformanceCounter {
	public:
		Win32PerformanceCounter() {
			QueryPerformanceFrequency((LARGE_INTEGER*)(&m_frequency));
			m_frequency = m_frequency / 1000;
		}
		sint64 m_frequency;
	};
	Win32PerformanceCounter g_win32counter;
#endif

	sint64 GetTimeS()
	{
		return GetTimeMS() / 1000;
	}

	sint64 GetTimeM()
	{
		return GetTimeMS() / 60000;
	}

	sint64 GetTimeH()
	{
		return GetTimeMS() / 3600000;
	}

	std::string SearchAndReplace(const std::string& p_target, const std::string& p_search, const std::string& p_replace)
	{

		if (p_target.size() <= 0)
			return "";
		std::string str = p_target;
		int begin = 0;
		while (true)
		{

			begin = 0;
			begin = str.find(p_search);
			if (begin != std::string::npos)
			{
				str.replace(begin, p_search.size(), p_replace);
			}
			else
			{
				break;
			}
		}
		return str;

	}

	std::string RemoveWord(const std::string& p_string, int p_index)
	{
		int wss = p_string.find_first_not_of(WHITESPACE);
		while (p_index > 0)
		{
			p_index--;
			wss = p_string.find_first_of(WHITESPACE, wss);
			wss = p_string.find_first_not_of(WHITESPACE, wss);

		}
		int wse = p_string.find_first_of(WHITESPACE, wss);
		wse = p_string.find_first_not_of(WHITESPACE, wss);
		if (wss == std::string::npos)
		{
			wss = 0;
			wse = 0;
		}
		std::string str = p_string;
		str.erase(wss, wse - wss);
		return str;
	}

	std::string ParseWord(const std::string& p_string, int p_index)
	{
		int wss = p_string.find_first_not_of(WHITESPACE);
		while (p_index > 0)
		{
			p_index--;
			wss = p_string.find_first_of(WHITESPACE, wss);
			wss = p_string.find_first_not_of(WHITESPACE, wss);

		}
		int wse = p_string.find_first_of(WHITESPACE, wss);
		if (wss == std::string::npos)
		{
			wss = 0;
			wse = 0;
		}
		return p_string.substr(wss, wse - wss);
	}

	std::string TrimWihitespace(const std::string& p_string)
	{
		int wsf, wsb;
		wsf = p_string.find_first_not_of(WHITESPACE);
		wsb = p_string.find_last_not_of(WHITESPACE);
		if (wsf == std::string::npos)
		{
			wsf = 0;
			wsb = -1;
		}
		return p_string.substr(wsf, wsb - wsf + 1);
	}

	std::string LowerCase(const std::string& p_string)
	{
		std::string str = p_string;
		for (int i = 0; i < str.size(); ++i)
		{
			str[i] = std::tolower(str[i]);
		}
		return str;
	}

	std::string UppercCase(const std::string& p_string)
	{
		std::string str = p_string;
		for (int i = 0; i < str.size(); ++i)
		{
			str[i] = std::toupper(str[i]);
		}
		return str;
	}

	std::string DateStamp()
	{
		char str[11];
		time_t a = time(0);
		tm b;
		gmtime_s(&b, &a);
		strftime(str, 11, "%Y.%m.%d", &b);
		return str;
	}

	std::string TimeStamp()
	{
		char str[9];
		time_t a = time(0);
		tm b;
		gmtime_s(&b, &a);
		strftime(str, 9, "%H:%M:%S", &b);
		return str;
	}

	sint64 GetTimeMS()
	{

#ifdef WIN32
		sint64 t;
		QueryPerformanceCounter((LARGE_INTEGER*)(&t));
		return t / g_win32counter.m_frequency;
#else
		struct timeval t;
		sint64 s;
		gettimeofday(&t, 0);
		s = t.tv_sec;
		s *= 1000;
		s += (t.tv_usec / 1000);
		return s;
#endif
	
	}
	void BasicLib::Timer::Reset(BasicLib::sint64 p_timepassed)
	{
		m_starttime = p_timepassed;
		m_inittime = BasicLib::GetTimeMS();
	}

	BasicLib::sint64 BasicLib::Timer::GetMS()
	{
		return (BasicLib::GetTimeMS() - m_inittime) + m_starttime;
	}

	BasicLib::sint64 BasicLib::Timer::GetS()
	{
		return GetMS() / 1000;
	}

	BasicLib::sint64 BasicLib::Timer::GetM()
	{
		return GetS() / 60;
	}

	BasicLib::sint64 BasicLib::Timer::GetH()
	{
		return GetMS() / 3600000;
	}

	BasicLib::sint64 BasicLib::Timer::GetD()
	{
		return GetH() / 24;
	}

	BasicLib::sint64 BasicLib::Timer::GetY()
	{
		return GetD() / 365;
	}
};








