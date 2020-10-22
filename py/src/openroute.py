"""
A wrapper for the OpenRouteService api.
"""
import requests


BASE_URL = "https://api.openrouteservice.org"
HEADERS = {
    'Accept': 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8',
    'Authorization': '5b3ce3597851110001cf624865c2d3b02c2c4f43b9d877849d66b13c',
    'Content-Type': 'application/json'
}


def post(endpoint: str, body: str):
    """
    Abstraction of POST method
    """
    response = requests.post(BASE_URL + endpoint, body, headers=HEADERS)

    if response.status_code != 200:
        print(response.status_code, response.reason)
        print(response.text)
        return ""

    return response.text


def matrix(locations: str, profile: str = "foot-walking"):
    """
    Returns duration and distance matrix for mutliple points.
    A symmetric duration matrix is returned where every point
    in locations is paired with each other. The result is null
    if a value can’t be determined.
    """
    return post(f"/v2/matrix/{profile}", """{
        "locations": """ + locations + """,
        "metrics": ["distance", "duration"]
    }""")


def matrix_otm(locations: str, source_index: int, profile: str = "foot-walking"):
    """
    Returns a one-to-many duration and distance matrix.
    The result is null if a value can’t be determined.
    """
    return post(f"/v2/matrix/{profile}", """{
        "locations": """ + locations + """,
        "sources": [""" + str(source_index) + """],
        "metrics": ["distance", "duration"]
    }""")


def matrix_mto(locations: str, destination_index: int, profile: str = "foot-walking"):
    """
    Returns a many-to-one duration and distance matrix.
    The result is null if a value can’t be determined.
    """
    return post(f"/v2/matrix/{profile}", """{
        "locations": """ + locations + """,
        "destinations": [""" + str(destination_index) + """],
        "metrics": ["distance", "duration"]
    }""")
