====================
Python that runs C++
====================

Here is how to use C++ from Python 2.7

This repository builds a shared object file using cmake_. This shared object file maps and binds C++ methods, objects and classes with `boost python`_ so they can be used in python after importing the file with ``import libpyapi_wrapper_ext``

I plan to use this repository for integrating a new third-party API that is distributed only in C++.

.. _cmake: https://cmake.org/
.. _boost python: https://wiki.python.org/moin/boost.python/GettingStarted

How to run C++ methods from Python
----------------------------------

Here is the python demo code:

::

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

How it Works
------------

#.  Import the C++ shared object file

    ::

        import libpyapi_wrapper_ext

#.  Call the ``demo_print_method``

    ::

        print libpyapi_wrapper_ext.demo_print_method(some_test_int, some_test_str)

    Under the hood, this code calls a C++ method `src/lib_pyapi_wrapper_ext.cpp#L24`_ that is bound by the line:

    ::

        def("demo_print_method", demo_print_method);

    Which runs the C++ method below from `src/lib_pyapi_wrapper_ext.cpp#L13`_

    ::

        std::string demo_print_method(int test_int, std::string test_string)
        {
            std::stringstream ss;
            ss << " - Testing Conversion Integer(" << test_int << ") String(" << test_string.c_str() << ")" << std::endl;
            return ss.str();
        }
    
    .. _src/lib_pyapi_wrapper_ext.cpp#L24: https://github.com/jay-johnson/python-that-runs-c-plus-plus/blob/master/src/lib_pyapi_wrapper_ext.cpp#L24
    .. _src/lib_pyapi_wrapper_ext.cpp#L13: https://github.com/jay-johnson/python-that-runs-c-plus-plus/blob/master/src/lib_pyapi_wrapper_ext.cpp#L13

#.  Create a Python-C++ API Object

    This creates a python wrapper object for demoing how to use a C++ API from python. The sample **PyAPIWrapper** class is defined in the `headers/pyapi_wrapper.h`_

    ::

        api_key     = "ASDFASDFASDF"
        api_skey    = "APISECRET"
        wrapper     = libpyapi_wrapper_ext.PyAPIWrapper("demoapi", api_key, api_skey)

    .. _headers/pyapi_wrapper.h: https://github.com/jay-johnson/python-that-runs-c-plus-plus/blob/master/headers/pyapi_wrapper.h


#.  Once the wrapper object is instantiated in python, it can invoke methods exposed by the shared object library file `src/lib_pyapi_wrapper_ext.cpp#L25`_. Here is the code for exposing one of the PyAPIWrapper member methods:

    ::

        .def("perform_api_action", &PyAPIWrapper::perform_api_action)

    This code binds the **PyAPIWrapper::perform_api_action** method from the cpp implementation file `src/pyapi_wrapper.cpp#L14`_

    .. _src/pyapi_wrapper.cpp#L14: https://github.com/jay-johnson/python-that-runs-c-plus-plus/blob/master/src/pyapi_wrapper.cpp#L14
    .. _src/pyapi_wrapper.cpp#L25: https://github.com/jay-johnson/python-that-runs-c-plus-plus/blob/master/src/pyapi_wrapper.cpp#L25
        

Build Steps
-----------

#. Build the C++ wrapper using CMake

    ::
        
        $ cmake .
        -- The C compiler identification is GNU 5.1.1
        -- The CXX compiler identification is GNU 5.1.1
        -- Check for working C compiler: /usr/lib64/ccache/cc
        -- Check for working C compiler: /usr/lib64/ccache/cc -- works
        -- Detecting C compiler ABI info
        -- Detecting C compiler ABI info - done
        -- Detecting C compile features
        -- Detecting C compile features - done
        -- Check for working CXX compiler: /usr/lib64/ccache/c++
        -- Check for working CXX compiler: /usr/lib64/ccache/c++ -- works
        -- Detecting CXX compiler ABI info
        -- Detecting CXX compiler ABI info - done
        -- Detecting CXX compile features
        -- Detecting CXX compile features - done
        -- Boost version: 1.57.0
        -- Found the following Boost libraries:
        --   filesystem
        --   system
        --   date_time
        --   python
        ---- Boost Include:  /usr/include
        ---- Boost Libs:     /usr/lib64/libboost_filesystem.so/usr/lib64/libboost_system.so/usr/lib64/libboost_date_time.so/usr/lib64/libboost_python.so
        -- Found PythonLibs: /usr/lib64/libpython2.7.so (found version "2.7.10") 
        ---- Python Include: /usr/include/python2.7
        ---- Python Libs:    /usr/lib64/libpython2.7.so
        -- Found PythonLibs: python2.7 (found version "2.7.10") 
        -- Boost version: 1.57.0
        -- Boost version: 1.57.0
        -- Found the following Boost libraries:
        --   python
        -- Configuring done
        -- Generating done
        -- Build files have been written to: <path>


#.  Make it 

    ::

        $ make -j4
        Scanning dependencies of target pyapi_wrapper_ext
        [ 33%] Building CXX object CMakeFiles/pyapi_wrapper_ext.dir/src/pyapi_wrapper.cpp.o
        [ 66%] Building CXX object CMakeFiles/pyapi_wrapper_ext.dir/src/lib_pyapi_wrapper_ext.cpp.o
        [100%] Linking CXX shared module libpyapi_wrapper_ext.so
        [100%] Built target pyapi_wrapper_ext
        $


#.  Run the demo


    ::
    
        $ ./run_api_demo.py 
        ----------------------------
        Running C++ method from Python
         - Testing Conversion Integer(7) String(This is how to setup Python to call a C++ API)

        Trying C++ Class from Python
        PyAPI(demoapi) running PerformAction with String(Passing a string into C++)

        $

Adding Custom Code
------------------

#.  Add your own cpp files to the source list found in the `CMakeLists.txt`_

.. _CMakeLists.txt: https://github.com/jay-johnson/python-that-runs-c-plus-plus/blob/master/CMakeLists.txt#L55

#.  Run ``cmake .``

#.  Run ``make``

License
-------

MIT
