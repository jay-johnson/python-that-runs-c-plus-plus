#include <iostream>
#include <string>
#include <sstream>

#include <boost/python.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

// Include custom classes to expose
#include "pyapi_wrapper.h"

// C++ method to demo 
std::string demo_print_method(int test_int, std::string test_string)
{
    std::stringstream ss;
    ss << " - Testing Conversion Integer(" << test_int << ") String(" << test_string.c_str() << ")" << std::endl;
    return ss.str();
}

// Expose methods between C++ and Python
BOOST_PYTHON_MODULE(libpyapi_wrapper_ext)
{
    using namespace boost::python;
    def("demo_print_method", demo_print_method);

    // Expose the class PyAPIWrapper to Python
    class_<PyAPIWrapper>("PyAPIWrapper",
        init<std::string const &, std::string const &, std::string const &>())
        .def("get_address", &PyAPIWrapper::get_address)
        .def("perform_api_action", &PyAPIWrapper::perform_api_action)
        .add_property("m_name", &PyAPIWrapper::get_name, &PyAPIWrapper::set_name)
    ;
}
