#!/usr/bin/env python3
import unittest
import re
import json
from tests.context import GeocacheApi, captured_output


class TestGeocaching(unittest.TestCase):
    def setUp(self):
        self.username = "mholdg16"
        self.password = "mholdg16"

    def test_token(self):
        api = GeocacheApi()
        with captured_output() as (out, _err):
            api.signin("nobody", "123")
        api.close()
        result = bool(re.search("Aquired token:", out.getvalue()))
        self.assertEqual(True, result)

    def test_signin(self):
        api = GeocacheApi()
        with captured_output() as (out, _err):
            api.signin(self.username, self.password)
        api.close()
        result = bool(re.search("Login success:", out.getvalue()))
        self.assertEqual(True, result)

    def test_search(self):
        with captured_output() as (_out, _err):
            api = GeocacheApi(self.username, self.password)
            json_data = api.search(latitude=57.011817, longitude=9.993127, count=50)
        api.close()
        data = json.loads(json_data)["results"]
        expected = 50
        self.assertEqual(expected, len(data))


if __name__ == '__main__':
    unittest.main()
