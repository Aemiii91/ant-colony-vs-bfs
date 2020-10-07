#!/usr/bin/env python3
"""
Test suite for the geocaching submodule.
"""
import unittest
import re
import json

from tests.context import GeocacheApi, captured_output


class TestGeocaching(unittest.TestCase):
    """
    Test suite for the geocaching submodule.
    """
    def setUp(self):
        self.username = "mholdg16"
        self.password = "mholdg16"

    def test_token(self):
        """
        Test whether signin successfully aquired a token.
        """
        api = GeocacheApi()
        with captured_output() as (out, _err):
            api.signin("nobody", "123")
        api.close()
        result = bool(re.search("Aquired token:", out.getvalue()))
        self.assertEqual(True, result)

    def test_signin(self):
        """
        Test whether signin successfully signed in.
        """
        api = GeocacheApi()
        with captured_output() as (out, _err):
            api.signin(self.username, self.password)
        api.close()
        result = bool(re.search("Login success:", out.getvalue()))
        self.assertEqual(True, result)

    def test_search(self):
        """
        Test whether search returned the right amount of geocaches.
        """
        with captured_output() as (_out, _err):
            api = GeocacheApi(self.username, self.password)
            json_data = api.search(latitude=57.011817, longitude=9.993127, count=50)
        api.close()
        data = json.loads(json_data)["results"]
        expected = 50
        self.assertEqual(expected, len(data))


if __name__ == '__main__':
    unittest.main()
