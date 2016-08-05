#include <iostream>
#include <string>
#include <sstream>

#include "pyapi_wrapper.h"

PyAPIWrapper::PyAPIWrapper(std::string const & name, std::string const & apikey, std::string const & apisecret)
: m_name(name)
, m_api_key(apikey)
, m_api_secret(apisecret)
{
}

std::string PyAPIWrapper::perform_api_action(const std::string & some_value)
{
    std::stringstream ss;
    ss << "PyAPI(" + this->m_name + ") running PerformAction with String(" << some_value.c_str() << ")" << std::endl;
    return ss.str();
}
