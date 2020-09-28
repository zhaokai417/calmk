/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-04 21:52:27
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-23 22:03:19
 */

#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <functional>
#include <stdarg.h>
#include <time.h>
#include <stdarg.h>
#include "../include/singleton.h"
#include "../include/util.h"

#define CALMK_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        calmk::LogEvevtWarp(calmk::LogEvent::ptr(new calmk::LogEvent(logger, level, __FILE__, __LINE__, \
            0, calmk::GetThreadId(), calmk::GetFiberId(), time(0)))).getSS()

#define CALMK_LOG_DEBUG(logger) CALMK_LOG_LEVEL(logger, calmk::LogLevel::DEBUG)
#define CALMK_LOG_INFO(logger) CALMK_LOG_LEVEL(logger, calmk::LogLevel::INFO)
#define CALMK_LOG_WARN(logger) CALMK_LOG_LEVEL(logger, calmk::LogLevel::WARN)
#define CALMK_LOG_ERROR(logger) CALMK_LOG_LEVEL(logger, calmk::LogLevel::ERROR)
#define CALMK_LOG_FATAL(logger) CALMK_LOG_LEVEL(logger, calmk::LogLevel::FATAL)

#define CALMK_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        calmk::LogEvevtWarp(calmk::LogEvent::ptr(new calmk::LogEvent(logger, level, \
                            __FILE__, __LINE__, 0, calmk::GetThreadId(), calmk::GetFiberId(), \
                            time(0)))).getEvent()->format(fmt, __VA_ARGS__)

#define CALMK_LOG_FMT_DEBUG(logger, fmt, ...) CALMK_LOG_FMT_LEVEL(logger, calmk::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define CALMK_LOG_FMT_INFO(logger, fmt, ...) CALMK_LOG_FMT_LEVEL(logger, calmk::LogLevel::INFO, fmt, __VA_ARGS__)
#define CALMK_LOG_FMT_WARN(logger, fmt, ...) CALMK_LOG_FMT_LEVEL(logger, calmk::LogLevel::WARN, fmt, __VA_ARGS__)
#define CALMK_LOG_FMT_ERROR(logger, fmt, ...) CALMK_LOG_FMT_LEVEL(logger, calmk::LogLevel::ERROR, fmt, __VA_ARGS__)
#define CALMK_LOG_FMT_FATAL(logger, fmt, ...) CALMK_LOG_FMT_LEVEL(logger, calmk::LogLevel::FATAL, fmt, __VA_ARGS__)

#define CALMK_LOG_ROOT() calmk::LoggerMgr::GetInstance()->getRoot()
            
namespace calmk {

    class Logger;
    
    //日志等级
    class LogLevel {
    public:
        enum Level {
            UNKNOW = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
        static const char* ToString(LogLevel::Level level);
    };

    //日志事件
    class LogEvent {
    public:
        typedef std::shared_ptr<LogEvent> ptr;
        LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
                    , const char* file, int32_t line, uint32_t elapse
                    , uint32_t threadId, uint32_t fiberId, uint64_t time);
        const char* getFile() { return m_file; }
        int32_t getLine() { return m_line; }
        uint32_t getElapse() const { return m_elapse; } 
        uint32_t getThreadId() const { return m_threadId; }
        uint32_t getFiberId() const { return m_fiberId; }
        time_t getTime() const { return m_time; }
        std::string getContent() const { return m_ss.str(); }
        LogLevel::Level getLevel() const { return m_level; }
        std::string getThreadName() const {return m_threadName; }
        std::shared_ptr<Logger> getLogger() const { return m_logger; } 

        std::stringstream& getSS() { return m_ss; }
        void format(const char* fmt, ...);
        void format(const char* fmt, va_list al);
    private:
        const char *m_file = nullptr;       //文件名
        int32_t m_line = 0;                 //行号
        uint32_t m_elapse = 0;              //程序启动到现在的毫秒数
        uint32_t m_threadId = 0;            //线程id
        uint32_t m_fiberId = 0;             //协程id
        time_t m_time;                      //时间戳
        std::string m_threadName;           //线程名称
        std::stringstream ss;               //日志内容流
        std::shared_ptr<Logger> m_logger;   //日志器
        LogLevel::Level m_level = LogLevel::DEBUG;            //日志等级
        std::stringstream m_ss;             
    };
    
    class LogEvevtWarp{
    public:
        LogEvevtWarp(LogEvent::ptr e);
        ~LogEvevtWarp();
        std::stringstream& getSS();
        LogEvent::ptr getEvent() const { return m_event; }
        
    private:
        LogEvent::ptr m_event;
    };
    
    
    //日志格式器
    class LogFormatter {
    public:
    
        typedef std::shared_ptr<LogFormatter> ptr;

         /**
         * @brief 构造函数
         * @param[in] pattern 格式模板
         * @details 
         *  %m 消息
         *  %p 日志级别
         *  %r 累计毫秒数
         *  %c 日志名称
         *  %t 线程id
         *  %n 换行
         *  %d 时间
         *  %f 文件名
         *  %l 行号
         *  %T 制表符
         *  %F 协程id
         *  %N 线程名称
         *
         *  默认格式 "%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"
         */
        LogFormatter(const std::string &pattern);


        std::string format (std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    public:
        class FormatItem {
        public:
            typedef std::shared_ptr<FormatItem> ptr;

            /**
             * @brief: 析构函数
             * @msg: 
             * @param {type} 
             * @return {type} 
             */
            FormatItem(const std::string &fmt = "") {}
            virtual ~FormatItem () {}
            virtual void format (std::ostream &os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        };

        void init();

    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;
        bool m_error = false;

    };


     //日志输出地
    class LogAppender {
    friend class Logger;
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender () {}
        virtual void log (std::shared_ptr<Logger> logger, LogLevel::Level level, const LogEvent::ptr event) = 0;

        void setFormatter (LogFormatter::ptr val) { m_formatter = val; }
        LogFormatter::ptr getFormatter () { return m_formatter; }

        LogLevel::Level getLevel() const { return m_level; }
        void setLevel(LogLevel::Level level) { m_level = level; }

    protected:
        LogLevel::Level m_level = LogLevel::DEBUG;
        LogFormatter::ptr m_formatter;
    };

    //日志输出器
    class Logger :public std::enable_shared_from_this<Logger> {
    public:
        typedef std::shared_ptr<Logger> ptr;
        
        Logger (const std::string &name = "root");
        void log (LogLevel::Level level, const LogEvent::ptr event);
        void debug (LogEvent::ptr event);
        void info (LogEvent::ptr event);
        void warn (LogEvent::ptr event);
        void fatal (LogEvent::ptr event);
        void error (LogEvent::ptr event);

        void addAppender (LogAppender::ptr appender);
        void deleteAppender (LogAppender::ptr appender);
        LogLevel::Level getLevel() const { return m_level; }
        void setLevel (LogLevel::Level level) { m_level = level; }
        const std::string getName() { return m_name; }
    private:
        std::string m_name;                             //日志名称
        LogLevel::Level m_level;                        //日志级别
        std::list<LogAppender::ptr> m_appenders;        //Appender集合
        LogFormatter::ptr m_formatter;
    };

    //控制台appender
    class StdoutLogAppender : public LogAppender {
    public:
        typedef std::shared_ptr<StdoutLogAppender> ptr;
        void log (std::shared_ptr<Logger> logger, LogLevel::Level level, const LogEvent::ptr event) override;
    private:

    };

    //文件appender
    class FileLogAppender : public LogAppender {
    public:
        typedef std::shared_ptr<FileLogAppender> ptr;
        FileLogAppender (const std::string  &filename);
        void log (std::shared_ptr<Logger> logger, LogLevel::Level level, const LogEvent::ptr event) override;

        //重新打开文件，文件打开成功，返回true
        bool reopen();
    private:
        std::string m_filename;
        std::ofstream m_filestream;
    };

    class LoggerManager {
    public:
        LoggerManager();
        Logger::ptr getLogger(const std::string& name);
        
        void init();
        Logger::ptr getRoot() const { return m_root; }
    private:
        std::map<std::string, Logger::ptr> m_loggers;
        Logger::ptr m_root;
    };

    typedef calmk::Singleton<LoggerManager> LoggerMgr;

}

#endif
