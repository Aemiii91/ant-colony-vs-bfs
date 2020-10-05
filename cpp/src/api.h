#include <string>
#include <iostream>
#include <curl/curl.h>

class Api {
    public:
        size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
};
