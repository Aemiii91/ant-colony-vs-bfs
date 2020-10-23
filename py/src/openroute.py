"""
A wrapper for the OpenRouteService api.
"""

import json
from tqdm import tqdm

from utils.api_requests import ApiRequests
import utils.caching as caching


api = ApiRequests(
    base_url='https://d509e20-ors-app.azurewebsites.net/ors/v2/',
    localhost_url='http://localhost:8080/ors/v2/',
    headers={
        'Accept': 'application/json, application/geo+json; charset=utf-8',
        'Authorization': '5b3ce3597851110001cf624865c2d3b02c2c4f43b9d877849d66b13c',
        'Content-Type': 'application/json'
    }
)


def check_status() -> bool:
    """
    Check status of API
    """
    health = json.loads(api.get("health", nocache=True) or "{}")

    if health and 'status' in health:
        return health['status'] == 'ready'

    return False


def request_matrix(data: dict, profile: str = 'foot-walking', nocache: bool = False) -> dict:
    """
    API handle for the `matrix` endpoint.
    Returns duration and distance matrix for mutliple points.
    """
    return json.loads(api.post(f'matrix/{profile}', data, nocache=nocache) or "{}")


def matrix(locations: str,
           profile: str = 'foot-walking',
           return_string: bool = True,
           data: dict = None) -> str:
    """
    Returns duration and distance matrix for mutliple points.
    A symmetric duration matrix is returned where every point
    in locations is paired with each other. The result is null
    if a value can’t be determined.
    """
    response = api.post(f'matrix/{profile}', {
        "locations": json.loads(locations) if locations else data,
        "metrics": ["distance", "duration"]
    })
    return _validate_return(response, return_string)


def matrix_otm(locations: str, source_index: int,
               profile: str = 'foot-walking',
               return_string: bool = True,
               data: dict = None) -> str:
    """
    Returns a one-to-many duration and distance matrix.
    The result is null if a value can’t be determined.
    """
    response = api.post(f'matrix/{profile}', {
        "locations": json.loads(locations) if locations else data,
        "sources": [source_index],
        "metrics": ["distance", "duration"]
    })
    return _validate_return(response, return_string)


def matrix_mto(locations: str, destination_index: int,
               profile: str = 'foot-walking',
               return_string: bool = True,
               data: dict = None) -> str:
    """
    Returns a many-to-one duration and distance matrix.
    The result is null if a value can’t be determined.
    """
    response = api.post(f'matrix/{profile}', {
        "locations": json.loads(locations) if locations else data,
        "destinations": [destination_index],
        "metrics": ["distance", "duration"]
    })
    return _validate_return(response, return_string)


def matrix_builder(data: list, increments: int = 1,
                   profile: str = 'foot-walking', nocache: bool = False) -> dict:
    """
    Builds a complete matrix in increments.

    E.g. call with a data list of length 500, and increments set to 20,
    will result in 25 calls to the matrix API.
    """
    if not nocache:
        cache_content = caching.load_cache(payload=data)
        if cache_content:
            return json.loads(cache_content)

    snapped_locations = data
    collected_response = {
        "distances": [],
        "durations": [],
        "destinations": None,
        "metadata": None
    }

    for index in tqdm(range(int(len(data) / increments))):
        start = index * increments
        response = request_matrix({
            "sources": list(range(start, start + increments)),
            "locations": snapped_locations,
            "metrics": ["distance", "duration"]
        }, profile, nocache=True)
        if not response:
            break
        if index == 0:
            snapped_locations = [dest['location'] for dest in response['destinations']]
        _merge_matrix_response(collected_response, response)

    if not nocache:
        caching.save_cache(json.dumps(collected_response), payload=data)

    return collected_response


def _merge_matrix_response(target: dict, response: dict):
    if 'distances' in response:
        target['distances'].extend(response['distances'])
    if 'durations' in response:
        target['durations'].extend(response['durations'])
    if not target['metadata']:
        target['metadata'] = response['metadata']
    if not target['destinations']:
        target['destinations'] = response['destinations']


def _validate_return(data: str, as_string: bool):
    if as_string:
        return data or ""
    return json.loads(data or "{}")
