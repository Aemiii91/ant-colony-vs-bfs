#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <string>
#include "pyhelper.hpp"
#include "utils.hpp"

using namespace std;

namespace apicaller {
    string opencaching(double latitude, double longitude, int count = 100);
}