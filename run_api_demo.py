#!/usr/bin/python

# Import the PyAPI Wrapper shared object file (extension)
import libpyapi_wrapper_ext

# Pass python variables through the method
some_test_int = 7
some_test_str = "This is how to setup Python to call a C++ API"

# call C++ Wrapper demo method
print "----------------------------"
print "Running C++ demo method from Python"
print libpyapi_wrapper_ext.demo_print_method(some_test_int, some_test_str)

print "Trying C++ Class from Python"
api_key     = "ASDFASDFASDF"
api_skey    = "APISECRET"
wrapper     = libpyapi_wrapper_ext.PyAPIWrapper("demoapi", api_key, api_skey)

str_value   = "Passing a string into C++"
print wrapper.perform_api_action(str_value)

