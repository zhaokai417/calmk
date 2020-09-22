/*
 * @Descripttion: 
 * @version: 
 * @Author: zhaokai
 * @Date: 2020-09-20 19:37:12
 * @LastEditors: zhaokai
 * @LastEditTime: 2020-09-21 22:26:40
 */
#pragma once

#include <memory>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "../include/log.h"


namespace calmk {

class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name, const std::string& description = "")
        :m_name(name)
        ,m_description(description) {}
    virtual ~ConfigVarBase() { }

    const std::string& getName() { return m_name; }
    const std::string& getDescription() {return m_description; }
    virtual std::string toString() = 0;
    virtual bool fromString(const std::string& val) = 0;
    
private:
    std::string m_name;
    std::string m_description;

};

template<typename T>
class ConfigVar : public ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVar> ptr;

    ConfigVar(const std::string& name
                ,const T& default_value
                , const std::string& description = "")
        :ConfigVarBase(name, description)
        ,m_val(default_value) {
    
    }
    
    std::string toString() override {
        try{
            return boost::lexical_cast<std::string>(m_val);
        } catch (std::exception& e) {
            CALMK_LOG_ERROR(CALMK_LOG_ROOT()) << "ConfigVar::toString exception" 
                << e.what() << " convert: " << typeid(m_val).name() << " to string";
        }
        return "";
    }
    
    bool fromString(const std::string& val) override {
        try {
            m_val = boost::lexical_cast<T>(val);
        } catch (std::exception& e) {
            CALMK_LOG_ERROR(CALMK_LOG_ROOT()) << "ConfigVar::toString exception" 
                << e.what() << " convert: string to " << typeid(m_val).name();
        }
        return false;
    }

    const T getValue() const { return m_val;}
    void setValue(T& v) { m_val = v; }

private:
    T m_val;
};

class Config {
public:
    typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;
    
    template<typename T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name,
            const T& default_value, const std::string& description = "") {
        auto tmp = Lookup<T>(name);
        if (tmp) {
            CALMK_LOG_INFO(CALMK_LOG_ROOT()) << "Lookup name" << name << "exists";
            return tmp;
        } 

        if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._0123456789")
            != std::string::npos) {
                CALMK_LOG_ERROR(CALMK_LOG_ROOT()) << "Lookup name invalid " << name;
                throw std::invalid_argument(name);
        }

        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
        s_dates[name] = v;
        return v;
    }

    template<typename T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name) {
        auto it = s_dates.find(name);
        if (it == s_dates.end()) {
            return nullptr;
        }
        return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
    }
    
private:
    static ConfigVarMap s_dates;
};


}