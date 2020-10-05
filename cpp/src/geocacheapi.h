#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <curl/curl.h>

using namespace std;

class GeocacheAPI {
public:
  bool Search();
private:
  bool _loggedIn = false;
  const char *USERNAME = "mholdg16";
  const char *PASSWORD = "mholdg16";

  string _GetRequestVerificationToken();
  bool _SignIn(string token);
  bool _LogOut();
  CURL * _HttpsRequest(string requestType, string url);
  static size_t _WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};