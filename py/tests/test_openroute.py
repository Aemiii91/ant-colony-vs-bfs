#!/usr/bin/env python3
"""
Test suite for the OpenRoute submodule.
"""
import unittest
import json

from tests.context import openroute, captured_output


class TestOpenRoute(unittest.TestCase):
    """
    Test suite for the OpenRoute submodule.
    """
    def setUp(self):
        self.locations = "[[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281],[115.663757,38.106467]]"
        self.location_count = 4

    def test_matrix(self):
        """
        Test matrix.
        """
        count = self.location_count

        with captured_output() as (out, _err):
            json_data = openroute.matrix(self.locations)

        if len(json_data) == 0:
            print(out)

        (durations, distances) = parse_data(json_data)

        result = (durations["cols"] == count and
                  durations["rows"] == count and
                  distances["cols"] == count and
                  distances["rows"] == count)
        expected = True
        self.assertEqual(expected, result)


    def test_matrix_otm(self):
        """
        Test one-to-many.
        """
        count = self.location_count

        with captured_output() as (out, _err):
            json_data = openroute.matrix_otm(self.locations, 0)

        if len(json_data) == 0:
            print(out)

        (durations, distances) = parse_data(json_data)

        result = (durations["cols"] == 1 and
                  durations["rows"] == count and
                  distances["cols"] == 1 and
                  distances["rows"] == count)
        expected = True
        self.assertEqual(expected, result)


    def test_matrix_mto(self):
        """
        Test many-to-one.
        """
        count = self.location_count

        with captured_output() as (out, _err):
            json_data = openroute.matrix_mto(self.locations, count - 1)

        if len(json_data) == 0:
            print(out)

        (durations, distances) = parse_data(json_data)

        result = (durations["cols"] == count and
                  durations["rows"] == 1 and
                  distances["cols"] == count and
                  distances["rows"] == 1)
        expected = True
        self.assertEqual(expected, result)


def parse_data(json_data):
    """
    Common data parser, returns the dimensions of the matrices.
    """
    data = json.loads(json_data)
    durations = { "cols": 0, "rows": 0 }
    distances = { "cols": 0, "rows": 0 }

    if "durations" in data:
        durations["cols"] = len(data["durations"])
        durations["rows"] = len(data["durations"][0]) if durations["cols"] > 0 else 0
    if "distances" in data:
        distances["cols"] = len(data["distances"])
        distances["rows"] = len(data["distances"][0]) if distances["cols"] > 0 else 0

    return (durations, distances)


if __name__ == '__main__':
    unittest.main()
