#include "openrouteapi.h"


std::string OpenRouteApi::GetWalkingMatrix() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openrouteservice.org/v2/matrix/driving-car");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Authorization: 5b3ce3597851110001cf624865c2d3b02c2c4f43b9d877849d66b13c");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        const char *data = "{\"locations\":[[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281],[115.663757,38.106467]]}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &OpenRouteApi::write_data);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        res = curl_easy_perform(curl);
        std::cout << "keklmao" << std::endl;
        std::cout << readBuffer;
    }
    curl_easy_cleanup(curl);
    return "hej";
}

