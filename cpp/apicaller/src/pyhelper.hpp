// Based on: https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include <filesystem>
#include <string>
#include <Python.h>

/**
 * Helper class to encapsulate a PyObject*.
 * 
 * Once the class goes out of scope, the object is automatically dereferenced.
 * Also, the NULL object is automatically taken care of, and can also be
 * automatically type casted to PyObject*. To increase the reference pointer,
 * call the AddReff(), method of the CPyObject class.
 */
class CPyObject
{
private:
    PyObject *p;

public:
    CPyObject() : p(NULL) {}

    /// @param _p The PyObject to encapsulate.
    CPyObject(PyObject *_p) : p(_p) {}

    ~CPyObject()
    {
        Release();
    }

    PyObject *getObject()
    {
        return p;
    }

    PyObject *setObject(PyObject *_p)
    {
        return (p = _p);
    }

    PyObject *AddRef()
    {
        if (p)
        {
            Py_INCREF(p);
        }
        return p;
    }

    void Release()
    {
        if (p)
        {
            Py_DECREF(p);
        }

        p = NULL;
    }

    PyObject *operator->()
    {
        return p;
    }

    bool is()
    {
        return p ? true : false;
    }

    operator PyObject *()
    {
        return p;
    }

    PyObject *operator=(PyObject *pp)
    {
        p = pp;
        return p;
    }

    operator bool()
    {
        return p ? true : false;
    }
};

/**
 * Used to automatically initialize a Python instance.
 * When this object goes out of scope, the Python environment is destroyed.
 */
class CPyInstance
{
public:
    CPyInstance()
    {
        Py_Initialize();
        std::filesystem::path cwd = std::filesystem::current_path();
        std::string pycode = "import sys; sys.path.append('" + cwd.string() + "/../../py/src')";
        PyRun_SimpleString(pycode.c_str());
    }

    ~CPyInstance()
    {
        Py_Finalize();
    }

    /**
     * Helper for getting a specific function contained in a python module.
     * 
     * @param module The name of the python module.
     * @param function The name of the desired function.
     * @return Reference to the python function.
     */
    CPyObject getFunction(const char *module, const char *function)
    {
        CPyObject pModule = PyImport_Import(PyUnicode_DecodeFSDefault(module));

        if (!pModule) {
            std::cout << "<cpp> Error: Couldn't load module '" << module << "'." << std::endl;
            return CPyObject(NULL).AddRef();
        }

        CPyObject pFunc = PyObject_GetAttrString(pModule, function);

        if (!pFunc || !PyCallable_Check(pFunc)) {
            std::cout << "<cpp> Error: Couldn't get function '" << function << "'." << std::endl;
            return CPyObject(NULL).AddRef();
        }

        return pFunc.AddRef();
    }
};

#endif