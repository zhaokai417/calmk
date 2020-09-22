/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-20 11:16:21
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-20 11:22:26
 */
#pragma once

#include <memory>

namespace calmk {

template<typename T, typename X = void, int N = 0>
class Singleton {
public:
    static T* GetInstance() {
        static T v;
        return &v;
    }
};

template<typename T, typename X = void, int N = 0>
class SingletonPtr {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v(new T);
        return v;
    }
};

}