#!/usr/bin/env python3
"""
Test suite for the openroute submodule.
"""
import unittest

from tests.context import openroute, matrix_utils, captured_output


class TestOpenRoute(unittest.TestCase):
    """
    Test suite for the openroute submodule.
    """
    def setUp(self):
        self.locations = [
            [13.401833,52.518417],
            [13.401833,52.518417],
            [13.40085,52.516317],
            [13.400967,52.514017],
            [13.407133,52.521467],
            [13.39,52.5171],
            [13.4033,52.524817],
            [13.4042,52.512683],
            [13.39855,52.525967],
            [13.410583,52.521833]
        ]
        self.location_count = 10

        if not openroute.check_status():
            openroute.api.toggle_online()


    def test_check_status(self):
        """
        Test whether the openroute service is ready
        """
        initial_online = openroute.api.is_online()

        openroute.api.go_offline()
        local_ready = openroute.check_status()
        print("[{}] localhost".format(' OK ' if local_ready else 'FAIL'))

        openroute.api.go_online()
        azure_ready = openroute.check_status()
        print("[{}] azure".format(' OK ' if azure_ready else 'FAIL'))

        if not initial_online:
            openroute.api.go_offline()

        print('Using: {}'.format('azure' if openroute.api.is_online() else 'localhost'))

        result = local_ready or azure_ready
        expected = True
        self.assertEqual(expected, result)


    def test_matrix(self):
        """
        Test matrix.
        """
        count = self.location_count

        with captured_output() as (out, _err):
            data = openroute.matrix(None, data=self.locations, return_string=False)

        if len(data) == 0:
            print(out)

        (durations, distances) = parse_data(data)

        result = durations == (count, count) and distances == (count, count)
        expected = True
        self.assertEqual(expected, result)


    def test_matrix_otm(self):
        """
        Test one-to-many.
        """
        count = self.location_count

        with captured_output() as (out, _err):
            data = openroute.matrix_otm(None, 0, data=self.locations, return_string=False)

        if len(data) == 0:
            print(out)

        (durations, distances) = parse_data(data)

        result = durations == (1, count) and distances == (1, count)
        expected = True
        self.assertEqual(expected, result)


    def test_matrix_mto(self):
        """
        Test many-to-one.
        """
        count = self.location_count

        with captured_output() as (out, _err):
            data = openroute.matrix_mto(None, count-1, data=self.locations, return_string=False)

        if len(data) == 0:
            print(out)

        (durations, distances) = parse_data(data)

        result = durations == (count, 1) and distances == (count, 1)
        expected = True
        self.assertEqual(expected, result)


def parse_data(data) -> (int, int):
    """
    Common data parser, returns the dimensions of the matrices.
    """
    durations = (0, 0)
    distances = (0, 0)

    if "durations" in data:
        durations = matrix_utils.get_matrix_dimensions(data['durations'])
    if "distances" in data:
        distances = matrix_utils.get_matrix_dimensions(data['distances'])

    return (durations, distances)


if __name__ == '__main__':
    unittest.main()
