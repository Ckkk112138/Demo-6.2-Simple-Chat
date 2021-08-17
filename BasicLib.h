#ifndef BASICLIB_H
#define BASICLIB_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <time.h>
#include <cctype>
#include <sstream>
#include <fstream>
#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996)

namespace BasicLib
{
#ifdef __GNUC__   // Linux
    typedef long long int sint64;
    typedef unsigned long long int uint64;
#endif

#ifdef WIN32    // Windows
    typedef long long sint64;
    typedef unsigned long long uint64;
#endif

    



    sint64 GetTimeMS();
    sint64 GetTimeS();
    sint64 GetTimeM();
    sint64 GetTimeH();

    std::string TimeStamp();
    

    std::string DateStamp();
    

    class Timer
    {
        public:
            Timer(sint64 p_timepassed = 0);
            void Reset(sint64 p_timepassed = 0);
            sint64 GetMS();
            sint64 GetS();
            sint64 GetM();
            sint64 GetH();
            sint64 GetD();
            sint64 GetY();
        protected:
            sint64 m_inittime;
            sint64 m_starttime;

    };

    std::string UppercCase(const std::string& p_string);
    

    std::string LowerCase(const std::string& p_string);
    

    const std::string WHITESPACE = " \t\n\r";
    std::string TrimWihitespace(const std::string& p_string);
    

    std::string ParseWord(const std::string& p_string, int p_index);
    

    std::string RemoveWord(const std::string& p_string, int p_index);
    

    template<class type>
    inline std::string tostring(const type& p_type)
    {
        std::stringstream str;
        str << p_type;
        return str.str();
    }

    template<class type>
    inline type totype(const std::string& p_string)
    {
        std::stringstream str;
        str << p_string;
        type t;
        str >> t;
        return t;
    }

    std::string SearchAndReplace(const std::string& p_target, const std::string& p_search, const std::string& p_replace);
    
    class TextDecorator {
    public:
        static std::string FileHeader(const std::string& p_title) {
            return "==================================================\n" +
                p_title + "\n" +
                "==================================================\n\n";
        }
        static std::string SessionOpen() {
            return "\n";
        }
        static std::string SessionClose() {
            return "\n";
        }
        static std::string Decorate(const std::string& p_string) {
            return p_string + "\n";
        }
    };

    template<class decorator>
    class Logger
    {
        public:
            Logger(
                const std::string& p_filename,
                const std::string& p_logtitle,
                bool p_timestamp = false,
                bool p_datestamp = false
            );
            ~Logger();
            void Log(const std::string& p_entry);
    protected:
        std::fstream m_logfile;
        bool m_timestamp;
        bool m_datestamp;

    };

    template<class decorator>
    BasicLib::Logger<decorator>::Logger(const std::string& p_filename,
        const std::string& p_logtitle,
        bool p_timestamp,
        bool p_datestamp)
    {
        std::fstream filetester(p_filename.c_str(), std::ios::in);
        if (filetester.is_open())
        {
            filetester.close();
            m_logfile.open(p_filename.c_str(), std::ios::out | std::ios::app);

        }
        else
        {
            m_logfile.open(p_filename.c_str(), std::ios::out);
            m_logfile << decorator::FileHeader(p_logtitle);
        }
        m_timestamp = true;
        m_datestamp = true;
        m_logfile << decorator::SessionOpen();
        Log("Session opened.");
        m_timestamp = p_timestamp;
        m_datestamp = p_datestamp;
    }

    template<class decorator>
    BasicLib::Logger<decorator>::~Logger()
    {
        m_timestamp = true;
        m_datestamp = true;
        Log("Session closed.");
        m_logfile << decorator::SessionClose();
    }

    template<class decorator>
    void BasicLib::Logger<decorator>::Log(const std::string& p_entry)
    {
        std::string msg;
        if (m_datestamp)
        {
            msg += "[" + DateStamp() + "] ";
        }
        if (m_timestamp)
        {
            msg += "[" + TimeStamp() + "] ";
        }
        msg += p_entry;
        m_logfile << decorator::Decorate(msg);
    }
    typedef Logger<TextDecorator> TextLog;
    

};

#endif // !BASICLIB_H

