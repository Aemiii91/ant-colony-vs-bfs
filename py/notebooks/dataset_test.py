import json
from context import openroute, matrix_utils
import numpy as np

np.set_printoptions(edgeitems=30, linewidth=100000)


def load_data(filepath: str):
    data = {}
    with open(filepath, 'r') as infile:
        data = json.load(infile)
    return parse_data(data)


def parse_data(data: dict):
    locations = data['metadata']['query']['locations']
    cost_matrix = data['durations']

    return (locations, cost_matrix)


locations_ors, cost_matrix_ors = load_data("notebooks/data/matrix10_ors.json")
locations_new, cost_matrix_new = parse_data(openroute.matrix_builder_dir(locations_ors))

matrix_utils.print_matrix(cost_matrix_ors, "Openrouteservice (ors)")

print('\n')

matrix_utils.print_matrix(cost_matrix_new, "Openrouteservice (new)")

print('\n')

print('Diff (ors<>new):\n')
print(np.array(matrix_utils.matrix_diff(cost_matrix_ors, cost_matrix_new)))
