/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-14 22:46:30
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-15 22:50:25
 */
#include "../include/util.h"

namespace calmk {

pid_t GetThreadId() {
    return syscall(SYS_gettid);
}

u_int32_t GetFiberId() {
    return 0;
}


}