/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-21 21:58:04
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-21 22:27:29
 */
#include "../include/config.h"
#include "../include/log.h"

calmk::ConfigVar<int>::ptr g_int_value_config = 
    calmk::Config::Lookup("system.port", (int)8080, "system port");

int main(int argc, char** agrv) {
    
    CALMK_LOG_INFO(CALMK_LOG_ROOT()) << g_int_value_config->getValue();
    CALMK_LOG_INFO(CALMK_LOG_ROOT()) << g_int_value_config->toString();
    return 0;
}

