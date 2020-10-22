#include "openroute.hpp"

using namespace apicaller::utils;

std::string apicaller::openroute::matrix(std::string locations, std::string profile)
{
    CPyInstance pInstance;
    CPyObject pFunc, pResults;

    if (!(pFunc = pInstance.getFunction("openroute", "matrix")))
        return "";

    // python: openroute.matrix(locations: str, profile: str)
    pResults = PyObject_CallFunction(pFunc, "(s,s)", locations.c_str(), profile.c_str());

    return wchar_to_str(PyUnicode_AsWideCharString(pResults, NULL));
}

std::string apicaller::openroute::matrixOTM(std::string locations, int sourceIndex, std::string profile)
{
    CPyInstance pInstance;
    CPyObject pFunc, pResults;

    if (!(pFunc = pInstance.getFunction("openroute", "matrix_otm")))
        return "";

    // python: openroute.matrix(locations: str, source_index: int, profile: str)
    pResults = PyObject_CallFunction(pFunc, "(s,i,s)", locations.c_str(), sourceIndex, profile.c_str());

    return wchar_to_str(PyUnicode_AsWideCharString(pResults, NULL));
}

std::string apicaller::openroute::matrixMTO(std::string locations, int destinationIndex, std::string profile)
{
    CPyInstance pInstance;
    CPyObject pFunc, pResults;

    if (!(pFunc = pInstance.getFunction("openroute", "matrix_mto")))
        return "";

    // python: openroute.matrix_mto(locations: str, destination_index: int, profile: str)
    pResults = PyObject_CallFunction(pFunc, "(s,i,s)", locations.c_str(), destinationIndex, profile.c_str());

    return wchar_to_str(PyUnicode_AsWideCharString(pResults, NULL));
}