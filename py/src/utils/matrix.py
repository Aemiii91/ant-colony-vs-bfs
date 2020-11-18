""" Matrix utilities"""

import numpy as np


def init_matrix(size: int, value: float = 0.0):
    return [[value] * size for _ in range(size)]


def get_matrix_dimensions(matrix: list) -> (int, int):
    """Get the dimensions of a matrix. Returns tuple of (rows, columns)."""
    rows = len(matrix)
    cols = len(matrix[0]) if rows > 0 else 0
    return (rows, cols)


def print_matrix(matrix: list, name: str):
    """Pretty print a matrix to the console."""
    rows, cols = get_matrix_dimensions(matrix)
    print(f"{name} ({rows}x{cols} matrix):")
    print(np.array(matrix))


def directional_diff(matrix: list) -> float:
    """Returns the average difference between two matrices."""
    rng = range(len(matrix))
    diffs = [[matrix[i][j] - matrix[j][i] for j in rng] for i in rng]

    return diffs


def matrix_diff(matrix_a: list, matrix_b: list) -> float:
    """Returns the average difference between two matrices."""
    rng = range(len(matrix_a))
    diffs = [[matrix_b[i][j] - matrix_a[i][j] for j in rng] for i in rng]

    return diffs
