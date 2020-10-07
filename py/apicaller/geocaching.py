#!/usr/bin/env python3
"""
A wrapper for the geocaching.com api. Enables signin and search.
"""
import argparse
import re
import json
import requests


class GeocacheApi:
    """
    A wrapper for the geocaching.com api. Enables signin and search.
    """
    __USERNAME = "mholdg16"
    __PASSWORD = "mholdg16"
    __token_re = re.compile(
        r"RequestVerificationToken[^<>]*?([A-Za-z0-9_-]{92})", re.MULTILINE)
    __userdata_re = re.compile(
        r"dataLayer = \[(.*?)\];", re.MULTILINE | re.DOTALL)
    __userdata: object = None
    __session = None

    def __init__(self, username: str = None, password: str = None):
        if username and password:
            self.signin(username, password)

    def signin(self, username: str = None, password: str = None):
        """
        Start new session and sign in to geocaching.com, and return a bool indicating success.
        """
        username = username or self.__USERNAME
        password = password or self.__PASSWORD
        if self.__userdata:
            self.close()
        self.__session = requests.Session()
        token = self.__request_verification_token()
        print(f":: Signing in as {username}...")
        response = self.__session.post("https://www.geocaching.com/account/signin", data={
            "UsernameOrEmail": username,
            "Password": password,
            "__RequestVerificationToken": token
        })
        match = self.__userdata_re.search(response.text)
        if match:
            self.__userdata = json.loads(match.group(1))
            print(
                f"Login success: {self.__userdata['username']} ",
                f"(ID: {self.__userdata['accountId']}, ",
                f"Membership: {self.__userdata['membershipLevel']})"
            )
            return True
        print("Login failed")
        return False

    def search(self, latitude: float = 57.011817, longitude: float = 9.993127, count: int = 1000):
        """
        Search for geocaches near a point, and return results as str
        """
        if not self.__userdata:
            print("Not signed in")
            return None
        print(f":: Getting geocaches near [{latitude}, {longitude}]...")
        response = self.__session.get(
            "https://www.geocaching.com/api/proxy/web/search/v2?" +
            "sort=distance&" +
            f"take={count}&" +
            f"origin={latitude},{longitude}"
        )
        if len(response.text) > 0:
            return response.text
        return None

    def close(self):
        """
        Close the session
        """
        self.__session.close()
        self.__session = None
        self.__userdata = None

    def __request_verification_token(self):
        print(":: Getting token...")
        response = self.__session.get(
            "https://www.geocaching.com/account/signin")
        match = self.__token_re.search(response.text)
        if match:
            token = match.group(1)
            print(f"Aquired token: {token}")
            return token
        print("Failed getting token")
        return None


def __main__(args):
    parser = argparse.ArgumentParser(
        description="Get a list (json) of geocaches near a point.")
    parser.add_argument('-y', '--latitude', default=57.011817, type=float)
    parser.add_argument('-x', '--longitude', default=9.993127, type=float)
    parser.add_argument('-c', '--count', default=50, type=int,
                        help="Number of geocaches to find (default=50, max=1000)")
    parser.add_argument('-u', '--username', default=None,
                        help="Username or email for geocaching.com")
    parser.add_argument('-p', '--password', default=None,
                        help="Password for geocaching.com")
    parser.add_argument('-o', '--output', default=None, metavar="OUTPUT_FILE_PATH",
                        help="Specify a file path to save the result")
    args = parser.parse_args(args)
    api = GeocacheApi()
    api.signin(args.username, args.password)
    json_data = api.search(args.latitude, args.longitude, args.count)
    api.close()
    if not json_data:
        print("No results")
        sys.exit()
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


if __name__ == '__main__':
    import sys
    __main__(sys.argv[1:])
