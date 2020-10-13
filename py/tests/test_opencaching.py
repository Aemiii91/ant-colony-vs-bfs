#!/usr/bin/env python3
"""
Test suite for the OpenCaching submodule.
"""
import unittest

from tests.context import opencaching, captured_output


class TestOpenCaching(unittest.TestCase):
    """
    Test suite for the OpenCaching submodule.
    """
    def setUp(self):
        pass

    def test_search(self):
        """
        Test whether search returned the right amount of geocaches.
        """
        with captured_output() as (_out, _err):
            json_data = opencaching.search(latitude=52.518848, longitude=13.399411, count=50)
            results = opencaching.parse_results(json_data)
        expected = 50
        self.assertEqual(expected, len(results))


if __name__ == '__main__':
    unittest.main()
