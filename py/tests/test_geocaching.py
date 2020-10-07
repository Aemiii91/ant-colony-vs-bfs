import unittest, json
from geocaching import geocaching

class GeocachingTest(unittest.TestCase):
  def test_search(self):
    json_data = geocaching.search(57.011817, 9.993127, 50)
    data = json.loads(json_data)["results"]
    expected = 50
    self.assertEqual(expected, len(data))

if __name__ == '__main__':
  unittest.main()