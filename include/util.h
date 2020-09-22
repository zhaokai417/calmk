/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-14 22:37:02
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-21 22:03:28
 */
#pragma once

#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>

namespace calmk {

pid_t GetThreadId();
u_int32_t GetFiberId();
    
}