"""
Context file for testing. Make sure to import needed submodules.
"""
import sys
import os
from contextlib import contextmanager
from io import StringIO
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))


# pylint: disable=unused-import,wrong-import-position
from apicaller import GeocacheApi
from apicaller import OpenrouteApi
from apicaller import opencaching


@contextmanager
def captured_output():
    """
    Context manager for redirecting stdout and stderr.
    Usage: `with captured_output() as (out, err):`
    """
    new_out, new_err = StringIO(), StringIO()
    old_out, old_err = sys.stdout, sys.stderr
    try:
        sys.stdout, sys.stderr = new_out, new_err
        yield sys.stdout, sys.stderr
    finally:
        sys.stdout, sys.stderr = old_out, old_err
