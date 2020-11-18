"""
A wrapper for OKAPI. Enables search.
"""
import urllib
import json
import requests


BASE_URL = "https://www.opencaching.de/okapi/"
CONSUMER_KEY = "ya8Hd2vV4PLX22h28t4z"


def search(latitude: float = 52.518848, longitude: float = 13.399411, count: int = 100, types: str = "-Multi|Quiz|Moving"):
    """
    Search for geocaches near a point, and return results as str
    """
    args = {
        "search_method": "services/caches/search/nearest",
        "search_params": json.dumps({
            "center": f"{latitude}|{longitude}",
            "type": types,
            "status": "Available",
            "limit": count
        }),
        "retr_method": "services/caches/geocaches",
        "retr_params": json.dumps({
            "fields": "location|type"
        }),
        "wrap": "true",
        "consumer_key": CONSUMER_KEY
    }
    response = requests.get(
        BASE_URL +
        "services/caches/shortcuts/search_and_retrieve?" +
        urllib.parse.urlencode(args)
    )
    return response.text


def parse_results(json_data: str):
    """
    Parse results, returns a list.
    """
    data = json.loads(json_data)
    if not "results" in data:
        if "error" in data:
            print(f":: Error: {data['error']['developer_message']}")
        return None
    results = data["results"]
    formatted = list(
        map(lambda cache_code: format_result(cache_code, results[cache_code]), results))
    return formatted


def format_result(cache_code: str, item: dict):
    """
    Formats result item to { code: str, latitude: float, longitude: float }
    """
    location = item["location"].split("|")
    return {
        "code": cache_code,
        "type": item["type"],
        "latitude": float(location[0]),
        "longitude": float(location[1])
    }
