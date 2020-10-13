#!/usr/bin/env python3
"""
A wrapper for OKAPI. Enables search.
"""
import argparse
import urllib
import json
import requests


BASE_URL = "https://www.opencaching.de/okapi/"
CONSUMER_KEY = "ya8Hd2vV4PLX22h28t4z"


def search(latitude: float = 52.518848, longitude: float = 13.399411, count: int = 100):
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
        "consumer_key": CONSUMER_KEY
    }
    print(f":: Getting geocaches near [{latitude}, {longitude}]...")
    response = requests.get(
        BASE_URL +
        "services/caches/shortcuts/search_and_retrieve?" +
        urllib.parse.urlencode(args)
    )
    return response.text


def parse_results(json_data: str):
    data = json.loads(json_data)
    if not "results" in data:
        if "error" in data:
            print(f":: Error: {data['error']['developer_message']}")
        return None
    results = data["results"]
    formatted = list(
        map(lambda cache_code: format_result(results[cache_code]), results))
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
    json_data = search(args.latitude, args.longitude, args.count)
    if not json_data or len(json_data) == 0:
        print("No results")
        sys.exit()
    if args.output:
        outputfile = open(args.output, "w")
        outputfile.write(json_data)
        outputfile.close()
        print(f"Results saved in '{args.output}'")
    else:
        results = parse_results(json_data)
        if results:
            print(f"Found {len(results)} geocaches")


if __name__ == '__main__':
    import sys
    __main__(sys.argv[1:])
