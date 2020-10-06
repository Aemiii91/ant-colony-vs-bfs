import requests, re, json, argparse

class GeocacheApi:
  __USERNAME = "mholdg16"
  __PASSWORD = "mholdg16"
  __token_re = re.compile(r"RequestVerificationToken[^<>]*?([A-Za-z0-9_-]{92})", re.MULTILINE)
  __userdata_re = re.compile(r"dataLayer = \[(.*?)\];", re.MULTILINE | re.DOTALL)
  __token = None
  __userdata: object = None

  def __init__(self, username: str = None, password: str = None):
    if username:
      self.__username = username
    else:
      self.__username = self.__USERNAME
    if password:
      self.__password = password
    else:
      self.__password = self.__PASSWORD
    self.__session = requests.Session()

  # Search for geocaches near a point
  def search(self, latitude: float, longitude: float, count: int = 1000):
    if not self.__userdata:
      if not self.__request_verification_token() or not self.__signin():
        return None
    return self.__get_results(latitude, longitude, count)

  # A token is needed for signin
  def __request_verification_token(self):
    print(f":: Getting token...")
    response = self.__session.get("https://www.geocaching.com/account/signin")
    match = self.__token_re.search(response.text)
    if match:
      self.__token = match.group(1)
      print(f"Aquired token: {self.__token}")
      return True
    print("Failed getting token")
    return False

  # Sign in to geocaching.com
  def __signin(self):
    print(f":: Signing in as {self.__username}...")
    response = self.__session.post("https://www.geocaching.com/account/signin", data = {
      "UsernameOrEmail": self.__username,
      "Password": self.__password,
      "__RequestVerificationToken": self.__token
    })
    match = self.__userdata_re.search(response.text)
    if match:
      self.__userdata = json.loads(match.group(1))
      print(f"Login succes: {self.__userdata['username']} (ID: {self.__userdata['accountId']}, Membership: {self.__userdata['membershipLevel']})")
      return True
    print("Login failed")
    return False

  # Query geocaching.com api for geocaches
  def __get_results(self, longitude: float, latitude: float, count: int):
    print(f":: Getting geocaches near [{longitude}, {latitude}]...")
    response = self.__session.get(f"https://www.geocaching.com/api/proxy/web/search/v2?sort=distance&take={count}&origin={longitude},{latitude}")
    if len(response.text) > 0:
      return response.text
    return None

  # Log out of geocaching.com (currently not in use)
  def __logout(self):
    self.__session.post("https://www.geocaching.com/account/logout")
    self.__userdata = None
    self.__token = None
    self.__session = requests.Session()

# Export an instance for immediate use
geocaching = GeocacheApi()

# Handle execution through commandline
def __main__():
  parser = argparse.ArgumentParser(description="Get a list (json) of geocaches near a point.")
  parser.add_argument('-y', '--latitude', default=57.011817, type=float)
  parser.add_argument('-x', '--longitude', default=9.993127, type=float)
  parser.add_argument('-c', '--count', default=1000, type=int, help="Number of geocaches to find (max 1000)")
  parser.add_argument('-u', '--username', default=None, help="Username or email for geocaching.com")
  parser.add_argument('-p', '--password', default=None, help="Password for geocaching.com")
  parser.add_argument('-o', '--output', default=None, metavar="OUTPUT_FILE_PATH", help="Specify a file path to save the result")
  args = parser.parse_args()
  api = GeocacheApi(args.username, args.password)
  json_data = api.search(args.latitude, args.longitude, args.count)
  if json_data:
    if args.output:
      outputfile = open(args.output, "w")
      outputfile.write(json_data)
      outputfile.close()
      print(f"Results saved in '{args.output}'")
    else:
      data = json.loads(json_data)
      if "results" in data:
        results = data["results"]
        print(f"Found {len(results)} geocaches")
      elif "errorMessage" in data:
        lines = json.loads(json.loads(data["errorMessage"])["message"])
        print(f":: Error: {data['statusMessage']}")
        for line in lines:
          if len(line) > 0:
            print(line[0])
  else:
    print("No results")

if __name__ == "__main__":
  __main__()