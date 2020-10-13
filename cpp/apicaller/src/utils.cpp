#include "utils.hpp"

std::string apicaller::utils::wchar_to_str(wchar_t *wchar_string)
{
    std::wstring ws(wchar_string);
    std::string str(ws.begin(), ws.end());
    return str;
}