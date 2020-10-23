"""An API requests helper class."""
import urllib
import requests
from requests.exceptions import ConnectionError as ConnErr

# pylint: disable=import-error
from utils.caching import load_cache, save_cache


class ApiRequests:
    """Helper class for API calls.

    Use-case: API with both localhost and online endpoints.
    The localhost_url is used by default (if given).
    """

    def __init__(self, base_url: str, headers=None, localhost_url: str = None):
        self.__base_url = base_url
        self.headers = headers or {}
        self.__localhost_url = localhost_url or ""
        self.base_url = localhost_url or base_url
        self.__is_online = False


    def get(self, endpoint: str, args: dict = None, headers=None, nocache: bool = False) -> dict:
        """Performs a GET request to the desired endpoint.
        
        Endpoint is the part of the URL that's not in the base URL.
        """
        url = self.base_url + endpoint
        if args:
            url += urllib.parse.urlencode(args)

        cache_content = load_cache({ "url": url }, cancel=nocache)
        if cache_content:
            return cache_content

        try:
            response = requests.get(url, headers=headers or self.headers)
        except ConnErr:
            return None

        data = _validate_response(response)

        save_cache(data, { "url": url }, cancel=nocache)

        return data


    def post(self, endpoint: str, payload: dict,
             headers=None, nocache: bool = False) -> dict:
        """Performs a POST request to the desired endpoint.
        
        Endpoint is the part of the URL that's not in the base URL.
        """
        cache_content = load_cache(payload, cancel=nocache)
        if cache_content:
            return cache_content

        try:
            response = requests.post(self.base_url + endpoint,
                json=payload,
                headers=headers or self.headers)
        except ConnErr:
            return None

        data = _validate_response(response)

        save_cache(data, payload, cancel=nocache)

        return data


    def go_online(self):
        """Switch to the `online` base URL."""
        self.base_url = self.__base_url
        self.__is_online = True


    def go_offline(self):
        """Switch to the `offline` base URL (aka. localhost)."""
        self.base_url = self.__localhost_url
        self.__is_online = False


    def toggle_online(self, value: bool = None):
        """Toggle online/offline base URLs."""
        if (not value is None and value) or not self.__is_online:
            self.go_online()
        else:
            self.go_offline()


    def is_online(self) -> bool:
        """Returns a bool indicating whether the online endpoint is in use."""
        return self.__is_online


def _validate_response(response: requests.Response) -> str:
    if response.status_code != 200:
        print(response.status_code, response.reason)
        print(response.text)
        return None
    return response.text
