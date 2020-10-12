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
                "fields": "code|location"
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
        if len(response.text) == 0:
            return None
        data = json.loads(response.text)
        if not "results" in data:
            if "error" in data:
                print(f":: Error: {data['error']['developer_message']}")
            return None
        results = data["results"]
        formatted = list(map(lambda cache_code: format_result(results[cache_code]), results))
        return formatted

def format_result(item: dict):
    """
    Formats result item to { code: str, latitude: float, longitude: float }
    """
    location = item["location"].split("|")
    return {
        "code": item["code"],
        "latitude": float(location[0]),
        "longitude": float(location[1])
    }

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
    results = api.search(args.latitude, args.longitude, args.count)
    if not results:
        print("No results")
        sys.exit()
    if args.output:
        outputfile = open(args.output, "w")
        outputfile.write(json.dumps({ "results": results }))
        outputfile.close()
        print(f"Results saved in '{args.output}'")
    else:
        print(f"Found {len(results)} geocaches")


if __name__ == '__main__':
    import sys
    __main__(sys.argv[1:])
