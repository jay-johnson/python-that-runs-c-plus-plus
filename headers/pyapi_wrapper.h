#ifndef PYAPI_WRAPPER_H
#define PYAPI_WRAPPER_H

#include <iostream>
#include <string>

#include <list>

class PyAPIWrapper {

private:

    std::string m_name;
    std::string m_api_key;
    std::string m_api_secret;

    bool m_debug;
    
public:

    // No default constructor

    // Named Constructor
    PyAPIWrapper(std::string const & name, std::string const & apikey, std::string const & apisecret);

    // Copy assignment
    PyAPIWrapper & operator=(PyAPIWrapper const & in_other) {
        this->m_name = in_other.m_name;
        return *this;
    }

    // Utility method to get the memory address of the instance
    uintptr_t get_address() const {
        return reinterpret_cast<uintptr_t>(this);
    }

    // Get name
    std::string get_name() const {
        return this->m_name;
    }

    // Set name
    void set_name(const std::string & in_name) {
        this->m_name = in_name;
    }

    // Example Perform API action
    std::string perform_api_action(const std::string & some_value);
};

#endif
