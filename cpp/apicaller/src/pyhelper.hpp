/*
Source: https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
*/
#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include <filesystem>
#include <string>
#include <Python.h>

class CPyInstance
{
public:
    CPyInstance()
    {
        Py_Initialize();
        std::filesystem::path cwd = std::filesystem::current_path();
        std::string pycode = "import sys; sys.path.append('" + cwd.string() + "/../../py')";
        PyRun_SimpleString(pycode.c_str());
    }

    ~CPyInstance()
    {
        Py_Finalize();
    }
};

class CPyObject
{
private:
    PyObject *p;

public:
    CPyObject() : p(NULL)
    {
    }

    CPyObject(PyObject *_p) : p(_p)
    {
    }

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

#endif