#include "apicaller.h"

using namespace std;

void ApiCaller::openCaching()
{
    char filepath[] = "../../py/apicaller/opencaching.py";
    FILE* fp;

    float latitude = 52.518848F;
    float longitude = 13.399411F;

    wchar_t const *args[] = {
        L"opencaching.py",
        L"--latitude", Py_DecodeLocale(to_string(latitude).c_str(), NULL),
        L"--longitude", Py_DecodeLocale(to_string(longitude).c_str(), NULL),
        NULL
    };

    wchar_t const **argv = args;
    int argc = sizeof(args)/sizeof(args[0])-1;

    std::cout << "Calling OpenCaching api..." << endl;

    Py_SetProgramName(argv[0]);
    Py_Initialize();
    PySys_SetArgv(argc, const_cast<wchar_t**>(argv));

    fp = _Py_fopen(filepath, "r");

    PyRun_SimpleFile(fp, "opencaching.py");

    Py_Finalize();
}