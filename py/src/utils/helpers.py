import json
import hashlib

def hash_object(payload: dict) -> str:
    hash_object = hashlib.md5(json.dumps(payload).encode("utf-8"))
    return hash_object.hexdigest()