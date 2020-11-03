"""Cache implementation"""

import os.path
import hashlib
import re
import json


def load_cache(payload: dict = None, cache_dir: str = './cache', cancel: bool = False) -> str:
    """Loads a cache file if it exists.

    Payload is a dictionary containing unique information about the data.
    The filename of the cache file becomes a stringified and hashed version
    of the payload.
    """
    if cancel:
        return None

    cache_file_path = _cache_file_path(cache_dir, payload)

    if not os.path.exists(cache_file_path):
        return None

    with open(cache_file_path, 'r') as infile:
        data = infile.read()

    return data


def save_cache(content: str, payload: dict = None,
               cache_dir: str = './cache', cancel: bool = False):
    """Saves a cache file.

    Payload is a dictionary containing unique information about the data.
    The filename of the cache file becomes a stringified and hashed version
    of the payload.
    """
    if cancel:
        return

    _make_cache_dir(cache_dir)

    cache_file_path = _cache_file_path(cache_dir, payload)

    with open(cache_file_path, 'w+') as outfile:
        outfile.write(content or "")


def _make_cache_dir(cache_dir) -> bool:
    if not os.path.isdir(cache_dir):
        try:
            os.mkdir(cache_dir)
        except OSError:
            return False
    return True


def _cache_file_path(cache_dir: str, payload: dict) -> str:
    hash_object = hashlib.md5(json.dumps(payload).encode("utf-8"))
    hex_dig = hash_object.hexdigest()
    return os.path.join(cache_dir, f'{hex_dig}.json')


def _slugify(value: str) -> str:
    value = value.strip().lower()
    value = re.sub(r'[/]+', '_', value)
    value = re.sub(r'[^\w\s-]', '', value)
    value = re.sub(r'[-\s]+', '-', value)
    return value
