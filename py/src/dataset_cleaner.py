import argparse
import json


def clean_matrix_data(matrix_data: dict):
    num_locations = len(matrix_data['metadata']['query']['locations'])
    print(f"Dataset contains {num_locations} node{'s' if num_locations != 1 else ''}.")    

    try:
        del matrix_data['sources']
        del matrix_data['metadata']['query']['sources']
        del matrix_data['metadata']['query']['metricsStrings']
        del matrix_data['metadata']['engine']['graph_date']
    except:
        pass

    culprit, missing = find_culprit(matrix_data)

    while culprit:
        print(culprit, get_location(matrix_data, culprit), f"Missing {missing} edge{'s' if missing != 1 else ''}.")
        remove_node(matrix_data, culprit)
        culprit, missing = find_culprit(matrix_data)

    num_cleaned = len(matrix_data['metadata']['query']['locations'])
    removed = num_locations - num_cleaned

    print(f"Removed {removed} node{'s' if removed != 1 else ''}.")
    print(f"Cleaned dataset contains {num_cleaned} node{'s' if num_cleaned != 1 else ''}.")

    print('Checking matrices:')
    check_matrices(matrix_data)


def get_location(matrix_data: dict, nodeIndex: int):
    return matrix_data['metadata']['query']['locations'][nodeIndex]


def find_culprit(matrix_data: dict):
    matrix = matrix_data['distances']
    missing_counts = [0]*len(matrix)
    rng = range(len(matrix))

    for i in rng:
        for j in rng:
            if i != j and not matrix[i][j]:
                missing_counts[i] += 1

    max_value = max(missing_counts)

    if max_value == 0:
        return (None, 0)
    
    return (missing_counts.index(max_value), max_value)


def remove_node(matrix_data: dict, nodeIndex: int):
    remove_node_from_matrix(matrix_data['distances'], nodeIndex)
    remove_node_from_matrix(matrix_data['durations'], nodeIndex)
    del matrix_data['metadata']['query']['locations'][nodeIndex]
    del matrix_data['geocaches'][nodeIndex]
    del matrix_data['destinations'][nodeIndex]


def remove_node_from_matrix(matrix: list, nodeIndex: int):
    del matrix[nodeIndex]

    for row in matrix:
        del row[nodeIndex]


def check_matrices(matrix_data: dict):
    check_matrix(matrix_data, 'distances')
    check_matrix(matrix_data, 'durations')


def check_matrix(matrix_data: list, matrix_name: str):
    matrix = matrix_data[matrix_name]

    is_square = matrix_is_square(matrix)
    is_symmetrical = matrix_is_symmetrical(matrix)
    zero_diagonal_only = matrix_zero_diagonal_only(matrix)

    print(f"Matrix '{matrix_name}' checks: is_square={is_square}, is_symmetrical={is_symmetrical}, zero_diagonal_only={zero_diagonal_only}.")


def matrix_is_square(matrix: list) -> bool:
    size = len(matrix)

    for row in matrix:
        if len(row) != size:
            return False

    return True


def matrix_is_symmetrical(matrix: list) -> bool:
    size = len(matrix)

    for i in range(size):
        for j in range(i):
            if i != j and abs(matrix[i][j] - matrix[j][i]) > 0.01:
                return False

    return True


def matrix_zero_diagonal_only(matrix: list) -> bool:
    size = len(matrix)

    for i in range(size):
        for j in range(i):
            if i == j and matrix[i][j] != 0:
                return False
            elif i != j and matrix[i][j] == 0:
                return False

    return True


def main():
    parser = argparse.ArgumentParser(description='Dataset Cleaner')
    parser.add_argument('--input', default=None, type=str)
    parser.add_argument('--output', default=None, type=str)
    parser.add_argument('--save', help='Overwrite input file', action='store_true')
    args = parser.parse_args()

    if not args.input:
        print('No dataset specified')
        return

    matrix_data = None

    with open(args.input, 'r') as infile:
        matrix_data = json.load(infile)

    if not matrix_data:
        print('Couln\'t read dataset.')
        return

    clean_matrix_data(matrix_data)

    if args.output or args.save:
        if args.save and not args.output:
            filepath = args.input
        else:
            filepath = args.output

        with open(filepath, 'w+') as outfile:
            json.dump(matrix_data, outfile)
        print(f"Saved to '{filepath}'.")


if __name__ == "__main__":
    main()
