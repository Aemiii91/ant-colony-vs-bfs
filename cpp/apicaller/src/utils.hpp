#include <string>

/**
 * Utility functions for use with the Python C-API.
 */
namespace apicaller::utils
{
    /**
     * Converts a wchar array to a string.
     * 
     * @param wchar_string The wchar array to convert.
     * @return A std::string representation of the input.
     */
    std::string wchar_to_str(wchar_t *wchar_string);
}