/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-13 10:21:02
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-22 21:30:48
 */
#include <iostream>
#include <thread>
#include "../include/log.h"
#include "../include/util.h"

int main() {
    calmk::Logger::ptr logger(new calmk::Logger);
    logger->addAppender(calmk::LogAppender::ptr(new calmk::StdoutLogAppender));

    calmk::FileLogAppender::ptr file_appender(new calmk::FileLogAppender("./log.txt"));
    
    calmk::LogFormatter::ptr fmt(new calmk::LogFormatter("%d %T %m %n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(calmk::LogLevel::ERROR);
    logger->addAppender(file_appender);

    //calmk::LogEvent::ptr event(new calmk::LogEvent(logger, logger->getLevel(), __LINE__, 0, calmk::GetRThreadId(), calmk::GetFiberId(), time(0)));
    //event->getSS() << "Hello zhaokai log eventn";
    
    //logger->log(calmk::LogLevel::DEBUG, event);

    std::cout << "Hello calmkm log!" << std::endl;

    CALMK_LOG_INFO(logger) << "test macro";
    CALMK_LOG_WARN(logger) << "test macro warn";

    CALMK_LOG_FMT_ERROR(logger, "[error]:fsdgs   %s fdsg", "aa");

    auto l = calmk::LoggerMgr::GetInstance()->getLogger("xx");
    CALMK_LOG_INFO(l) << "signalton log info.";

    return 0;
}

