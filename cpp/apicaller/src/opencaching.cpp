#include "opencaching.hpp"

using namespace std;
using namespace apicaller;

string apicaller::opencaching(double latitude, double longitude, int count)
{
    CPyInstance pInstance;

    CPyObject pOpencaching = PyImport_Import(PyUnicode_DecodeFSDefault("apicaller.opencaching"));

    if (!pOpencaching) {
        cout << "<cpp> Error: Module not imported" << endl;
        return "";
    }

    CPyObject pOpencaching_search = PyObject_GetAttrString(pOpencaching, "search");

    if (!pOpencaching_search || !PyCallable_Check(pOpencaching_search)) {
        cout << "<cpp> Error: Couldn't find 'search' function." << endl;
        return "";
    }

    CPyObject pResults = PyObject_CallFunction(pOpencaching_search, "(d,d,i)", latitude, longitude, count);

    return utils::wchar_to_str(PyUnicode_AsWideCharString(pResults, NULL));
}