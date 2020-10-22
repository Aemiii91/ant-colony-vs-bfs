#include "opencaching.hpp"

using namespace apicaller::utils;

std::string apicaller::opencaching::search(double latitude, double longitude, int count)
{
    CPyInstance pInstance;
    CPyObject pFunc, pResults;

    if (!(pFunc = pInstance.getFunction("opencaching", "search")))
        return "";

    // python: opencaching.search(latitude: float, longitude: float, count: int)
    pResults = PyObject_CallFunction(pFunc, "(d,d,i)", latitude, longitude, count);

    return wchar_to_str(PyUnicode_AsWideCharString(pResults, NULL));
}