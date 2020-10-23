""" Matrix utilities"""

import numpy as np


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


def matrix_diff(matrix_a: list, matrix_b: list) -> float:
    """Returns the average difference between two matrices."""
    diffs = []

    for (i, a_row) in enumerate(matrix_a):
        b_row = matrix_b[i]
        for (j, a_col) in enumerate(a_row):
            b_col = b_row[j]
            diffs.append(b_col - a_col)

    avg = sum(diffs) / len(diffs)
    return avg
