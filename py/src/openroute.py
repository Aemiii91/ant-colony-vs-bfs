"""
A wrapper for the OpenRouteService api.
"""

import json
from ast import literal_eval
from tqdm import tqdm

from utils.api_requests import ApiRequests
import utils.caching as caching
import utils.matrix as matrix_helpers
import utils.helpers as helpers


api = ApiRequests(
    base_url='https://d509e20-ors-app.azurewebsites.net/ors/v2/',
    localhost_url='http://localhost:8080/ors/v2/',
    headers={
        'Accept': 'application/json, application/geo+json; charset=utf-8',
        'Content-Type': 'application/json'
    }
)


def check_status() -> bool:
    """
    Check status of API
    """
    health = json.loads(api.get("health", nocache=True, ignorestatus=503) or "{}")

    if health and 'status' in health:
        return health['status'] == 'ready'

    return False


def auto_switch() -> bool:
    api.go_offline()
    local_ready = check_status()
    print("[{}] localhost".format(' OK ' if local_ready else 'FAIL'))

    api.go_online()
    azure_ready = check_status()
    print("[{}] azure".format(' OK ' if azure_ready else 'FAIL'))

    api.toggle_online(not local_ready)

    return local_ready or azure_ready


def request_directions(data: dict, format_out: str = '',
                       profile: str = 'foot-walking', nocache: bool = False) -> dict:
    """
    API handle for the `directions` endpoint.
    """
    return json.loads(api.post(f'directions/{profile}{format_out}', data,
                               nocache=nocache) or "{}")


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


def _validate_return(data: str, as_string: bool):
    if as_string:
        return data or ""
    return json.loads(data or "{}")


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
        "sources": [],
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
            snapped_locations = [dest['location']
                                 for dest in response['destinations']]
        _merge_matrix_response(collected_response, response)

    metadata = dict(collected_response['metadata'] or {})

    if 'sources' in metadata:
        collected_response['metadata'].pop('sources')

    metadata['service'] = "matrix-builder"
    metadata['service-id'] = helpers.hash_object(data)
    collected_response['metadata'] = metadata

    if not nocache:
        caching.save_cache(json.dumps(collected_response), payload=data)

    return collected_response


def _merge_matrix_response(target: dict, response: dict):
    if 'distances' in response:
        target['distances'].extend(response['distances'])
    if 'durations' in response:
        target['durations'].extend(response['durations'])
    if 'sources' in response:
        target['sources'].extend(response['sources'])
    if not target['destinations']:
        target['destinations'] = response['destinations']
    if not target['metadata']:
        target['metadata'] = response['metadata']


def matrix_builder_dir(data: list, profile: str = 'foot-walking', nocache: bool = False) -> dict:
    cache_id = {"data": data, "action": "matrix_builder_dir"}

    if not nocache:
        cache_content = caching.load_cache(payload=cache_id)
        if cache_content:
            return json.loads(cache_content)

    matrix_size = len(data)
    locations = data
    result = request_matrix({
        "sources": [0],
        "locations": locations,
        "metrics": ["distance", "duration"]
    }, profile, nocache=True)

    if 'error' in result:
        return result

    result['durations'] = matrix_helpers.init_matrix(matrix_size)
    result['distances'] = matrix_helpers.init_matrix(matrix_size)
    result['sources'] = []

    steps = []
    for fromIndex in range(matrix_size):
        for toIndex in range(fromIndex):
            steps.append((fromIndex, toIndex))

    for fromIndex, toIndex in tqdm(steps):
        if (fromIndex == toIndex):
            continue

        fromNode = data[fromIndex]
        toNode = data[toIndex]

        (duration, distance) = _get_directions(fromNode, toNode)
        _set_mirrored_value(result['durations'], fromIndex, toIndex, duration)
        _set_mirrored_value(result['distances'], fromIndex, toIndex, distance)

    result['metadata']['service'] = "matrix-builder-dir"
    result['metadata']['service-id'] = helpers.hash_object(cache_id)

    if not nocache:
        caching.save_cache(json.dumps(result), payload=cache_id)

    return result


def _get_directions(fromNode: list, toNode: list) -> (float, float):
    duration = None
    distance = None

    directions = request_directions({
        'coordinates': [fromNode, toNode],
        'geometry': False,
        'instructions': False
    })

    if 'routes' in directions and len(directions['routes']) > 0:
        try:
            duration = directions['routes'][0]['summary']['duration']
            distance = directions['routes'][0]['summary']['distance']
        except:
            pass

    return (duration, distance)


def _set_mirrored_value(matrix: list, fromIndex: int, toIndex: int, value: float):
    matrix[fromIndex][toIndex] = value
    matrix[toIndex][fromIndex] = value
