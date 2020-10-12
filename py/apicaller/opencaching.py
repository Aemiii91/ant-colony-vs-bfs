#!/usr/bin/env python3
"""
A wrapper for OKAPI. Enables search.
"""
import argparse
import urllib
import json
import requests


class OpencachingApi:
    """
    A wrapper for OKAPI. Enables search.
    """
    BASE_URL = "https://www.opencaching.de/okapi/"
    consumer_key = "ya8Hd2vV4PLX22h28t4z"

    def __init__(self, consumer_key: str = None):
        if consumer_key:
            self.consumer_key = consumer_key

    def search(self, latitude: float = 52.518848, longitude: float = 13.399411, count: int = 100):
        """
        Search for geocaches near a point, and return results as str
        """
        args = {
            "search_method": "services/caches/search/nearest",
            "search_params": json.dumps({
                "center": f"{latitude}|{longitude}",
                "status": "Available",
                "limit": count
            }),
            "retr_method": "services/caches/geocaches",
            "retr_params": json.dumps({
                "fields": "name|location|type|url"
            }),
            "wrap": "true",
            "consumer_key": self.consumer_key
        }
        print(f":: Getting geocaches near [{latitude}, {longitude}]...")
        response = requests.get(
            self.BASE_URL +
            "services/caches/shortcuts/search_and_retrieve?" +
            urllib.parse.urlencode(args)
        )
        if len(response.text) > 0:
            return response.text
        return None


def __main__(args):
    parser = argparse.ArgumentParser(
        description="Get a list (json) of geocaches near a point.")
    parser.add_argument('-y', '--latitude', default=52.518848, type=float)
    parser.add_argument('-x', '--longitude', default=13.399411, type=float)
    parser.add_argument('-c', '--count', default=100, type=int,
                        help="Maximum number of cache codes returned. (Default=100, Max=500)")
    parser.add_argument('-o', '--output', default=None, metavar="OUTPUT_FILE_PATH",
                        help="Specify a file path to save the result")
    args = parser.parse_args(args)
    api = OpencachingApi()
    json_data = api.search(args.latitude, args.longitude, args.count)
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
        elif "error" in data:
            error = data["error"]
            print(f":: Error: {error['developer_message']}")


if __name__ == '__main__':
    import sys
    __main__(sys.argv[1:])
