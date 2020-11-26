import argparse
import ast
import json


def analyze_path(dataset: str, path: list) -> list:
    cost_matrix = get_cost_matrix(dataset)
    visited = []
    path_knum = []

    for i in range(len(path)-2):
        fromIndex = path[i]
        toIndex = path[i+1]
        closest = get_closest_nodes_not_visited(fromIndex, cost_matrix, visited)

        knum = closest.index(toIndex) + 1
        path_knum.append(knum)

        visited.append(fromIndex)

    return path_knum


def get_cost_matrix(dataset: str) -> list:
    data = None
    with open(f"data/{dataset}.json", 'r') as infile:
        data = json.load(infile)
    return data['durations'] if 'durations' in data else []


def get_closest_nodes_not_visited(nodeIndex: int, cost_matrix: list, visited: list) -> list:
    closest = get_closest_nodes(nodeIndex, cost_matrix)
    return list(filter(lambda x: not x in visited, closest))


def get_closest_nodes(nodeIndex: int, cost_matrix: list) -> list:
    closest = get_node_edges(nodeIndex, cost_matrix)
    closest.sort(key=lambda x: x[1])
    return [x[0] for x in closest]


def get_node_edges(nodeIndex: int, cost_matrix: list) -> list:
    edges = [(index, cost) for (index, cost) in enumerate(cost_matrix[nodeIndex])]
    del edges[nodeIndex]    
    return edges


def main():
    dataset = 'munchen'
    path = '[77, 75, 76, 78, 79, 70, 64, 58, 57, 59, 56, 52, 49, 48, 50, 54, 62, 63, 67, 72, 55, 47, 43, 51, 69, 45, 37, 32, 22, 21, 14, 13, 17, 30, 31, 41, 40, 46, 44, 39, 33, 34, 27, 18, 29, 26, 42, 53, 71, 65, 80, 84, 94, 91, 102, 107, 114, 118, 110, 105, 90, 95, 97, 108, 103, 86, 88, 87, 92, 93, 83, 81, 77]'

    parser = argparse.ArgumentParser()
    parser.add_argument('--dataset', default=dataset)
    parser.add_argument('--path', default=path)
    args = parser.parse_args()

    path_knum = analyze_path(args.dataset, ast.literal_eval(args.path))

    print(path_knum)
    print('max(k) =', max(path_knum))


if __name__ == "__main__":
    main()