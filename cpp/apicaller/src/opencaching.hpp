#include <iostream>
#include <string>
#include "pyhelper.hpp"
#include "utils.hpp"

/**
 * Wrapper methods for the opencaching python script.
 */
namespace apicaller::opencaching {
    /**
     * Python wrapper for search.
     * Finds $n$ geocaches nearest a start coordinate.
     * 
     * @param latitude The latitude part of start coordinate
     * @param longitude The longitude part of start coordinate
     * @param count The amount of geocaches to fetch (max=500)
     * @return JSON string with the API result.
     */
    std::string search(double latitude, double longitude, int count = 100);
}