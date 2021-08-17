// ThreadLib.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifndef THREADLIB_H
#define THREADLIB_H

#include <map>
#ifdef WIN32                
#include <windows.h>
#else                       // Linux
#include <pthread.h>
#endif


namespace ThreadLib
{
	typedef void (*ThreadFunc)(void*);
#ifdef WIN32                
	typedef DWORD ThreadID;
	extern std::map< DWORD, HANDLE > g_handlemap;
#else                       // Linux
	typedef pthread_t ThreadID;
#endif
	class DummyData
	{
	public:
		ThreadFunc m_func;
		void* m_data;

	};

#ifdef WIN32
	DWORD WINAPI DummyRun(void* p_data);
#else
	void* DummyRun(void* p_data);
#endif 
	

	inline ThreadID Create(ThreadFunc p_func, void* p_param)
	{
		ThreadID t;
		DummyData* data = new DummyData;
		data->m_func = p_func;
		data->m_data = p_param;
#ifdef WIN32
		HANDLE h;
		h = CreateThread(NULL, 0, DummyRun, data, 0, &t);
		if (h != 0)
		{
			// insert handle to the map;
			g_handlemap[t] = h;
		}
#else
		pthread_create(&t, 0, DummyRun, data);
#endif // WIN32
		if (t == 0)
		{
			delete data;
			return -1;
		}
		return t;
	}

	inline ThreadID GetID()
	{
#ifdef WIN32
		return GetCurrentThreadId();
#else
		return pthread_self();
#endif

	}

	inline void WaitForFinish(ThreadID p_thread)
	{
#ifdef WIN32
		WaitForSingleObject(g_handlemap[p_thread], INFINITY);
		CloseHandle(g_handlemap[p_thread]);
		g_handlemap.erase(p_thread);
#else
		pthread_join(p_thread, NULL);
#endif // WIN32

	}

	inline void Kill(ThreadID& p_thread)
	{
#ifdef WIN32
		TerminateThread(g_handlemap[p_thread], 0);
		CloseHandle(g_handlemap[p_thread]);
		g_handlemap.erase(p_thread);
#else
		pthread_cancel(p_thread);
#endif // WIN32
	}

	inline void YieldThread(int p_milliseconds = 1)
	{
#ifdef WIN32
		Sleep(p_milliseconds);
#else
		usleep(p_milliseconds * 1000);
#endif
	}

	class Mutex
	{
		protected:
		#ifdef WIN32
		CRITICAL_SECTION m_mutex;
		#else
		pthread_mutex_t m_mutex;
		#endif // WIN32
	public:

		Mutex()
		{
#ifdef WIN32
			InitializeCriticalSection(&m_mutex);
#endif // WIN32

		}

		~Mutex()
		{
#ifdef WIN32
			DeleteCriticalSection(&m_mutex);
#else
			pthread_mutex_destroy(&m_mutex);
#endif // WIN32

		}

		inline void Lock()
		{
#ifdef WIN32
			EnterCriticalSection(&m_mutex);
#else
			pthread_mutex_lock(&m_mutex);
#endif // WIN32

		}

		inline void UnLock()
		{
#ifdef WIN32
			LeaveCriticalSection(&m_mutex);
#else
			pthread_mutex_unlock(&m_mutex);
#endif // WIN32
		}
	};

	


};
#endif // !THREADLIB_H




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
