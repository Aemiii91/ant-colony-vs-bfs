#include "geocacheapi.h"

using namespace std;

bool GeocacheAPI::Search()
{
  if (!_loggedIn) {
    string token = _GetRequestVerificationToken();

    if (!_SignIn(token))
      return false;
  }

  long double latitude = 57.011817l;
  long double longitude = 9.993127l;

  std::ostringstream url;
  url << "https://www.geocaching.com/api/proxy/web/search/v2?";
  url << "origin=" << latitude << "," << longitude;

  CURL *curl;
  CURLcode res;
  string readBuffer;

  curl = _HttpsRequest("GET", url.str());

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _WriteCallback);
    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    cout << "Request status: " << res << endl;
    cout << readBuffer << endl;

    if (res == CURLE_OK) {
      cout << "Search result: OK" << endl;
      // cout << readBuffer << endl;

      return true;
    }
  }

  return false;
}

string GeocacheAPI::_GetRequestVerificationToken()
{
  CURL *curl;
  CURLcode res;
  string token;
  string readBuffer;
  std::regex findTokenEx (
    ".*?RequestVerificationToken[^<>]*?([A-Za-z0-9_-]{92}).*?", 
    std::regex::extended
  );

  curl = _HttpsRequest("GET", "https://www.geocaching.com/account/signin");
  
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _WriteCallback);
    res = curl_easy_perform(curl);
  }

  curl_easy_cleanup(curl);
  
  if (res == CURLE_OK) {
    std::smatch match;
    regex_match(readBuffer, match, findTokenEx);

    if (match.size() == 2) {
      std::ssub_match sub_match = match[1];
      token = sub_match.str();
      cout << "Geocaching: Aquired token: " << token << endl;
    }
    else {
      cout << "Geocaching: Token request failed" << endl;
      cout << "Buffer dump: " << readBuffer << endl;
    }
  }
  else {
    cout << "Geocaching: Bad request: " << curl_easy_strerror(res) << endl;
  }

  return token;
}

bool GeocacheAPI::_SignIn(string token)
{
  CURL *curl;
  CURLcode res;

  curl = _HttpsRequest("http", "https://www.geocaching.com/account/signin");

  if (curl) {
    std::ostringstream formData;
    formData << "UsernameOrEmail=" << USERNAME << "&";
    formData << "Password=" << PASSWORD << "&";
    formData << "__RequestVerificationToken=" << token;

    cout << "Geocaching: Signin form data: " << formData.str() << endl;

    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, formData.str().c_str());
    res = curl_easy_perform(curl);
  }

  curl_easy_cleanup(curl);

  if (res != CURLE_OK) {
    cout << "Geocaching: Login failed: " << curl_easy_strerror(res) << endl;
    return false;
  }

  cout << "Geocaching: Login success" << endl;

  _loggedIn = true;
  return true;
}

CURL * GeocacheAPI::_HttpsRequest(string requestType, string url)
{
  CURL *curl;
  cout << "Geocaching: HttpsRequest: " << url << endl;

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, requestType.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    struct curl_slist *headers = NULL;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  }

  return curl;
}

size_t GeocacheAPI::_WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}