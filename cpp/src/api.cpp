#include "api.h"

size_t Api::write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)buffer, size * nmemb);
    return size * nmemb;
}

