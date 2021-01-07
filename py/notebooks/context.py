"""
Context file.
"""
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))


# pylint: disable=unused-import,wrong-import-position, import-error
import openroute
import opencaching
import utils.matrix as matrix_utils
import path_analyzer
import path_statictics
