import argparse
import math
import hashlib
import time
import datetime
import json
from typing import Callable
from ant_colony import AntColony


def main():
    parser = argparse.ArgumentParser(description='ACO')
    parser.add_argument('--node_count', default=10, type=int)
    parser.add_argument('--ant_count', default=50, type=int)
    parser.add_argument('--alpha', default=0.5, type=float)
    parser.add_argument('--beta', default=1.2, type=float)
    parser.add_argument('--evaporation', default=0.4, type=float)
    parser.add_argument('--pheromone_constant', default=1000.0, type=float)
    parser.add_argument('--iterations', default=80, type=int)
    args = parser.parse_args()
    opts = vars(args).copy()
    opts.pop('node_count')

    with open("data/matrix500.json", 'r') as infile:
        matrix_data = json.load(infile)

    locations = matrix_data['metadata']['query']['locations']

    nodes = dict(enumerate(locations[:args.node_count]))
    time_matrix = matrix_data['durations']

    for (i, matrix_row) in enumerate(time_matrix):
        for (j, value) in enumerate(matrix_row):
            if value == 0.0:
                time_matrix[i][j] = 1.0

    # ...we can make a colony of ants...
    colony = AntColony(nodes, cost_matrix=time_matrix, **opts)

    # ...that will find the optimal solution with ACO
    answer = colony.mainloop(_create_log(vars(args)))

    optimal_path = answer[0]
    lowest_cost = answer[1]
    cost_str = str(datetime.timedelta(seconds=math.floor(lowest_cost)))

    print(f'Lowest cost: {lowest_cost:.3f} ({cost_str})\n')
    print('Optimal path: ', optimal_path)


def _create_log(data: dict) -> Callable[[dict], None]:
    hash_object = hashlib.md5(json.dumps(data).encode("utf-8"))
    hex_dig = hash_object.hexdigest()
    filename = f"log_aco_n{data['node_count']}_a{data['ant_count']}_{hex_dig}"

    with open('logs/' + filename + '.csv', 'w+') as log:
        log.write('iteration,runtime,cost,path_length\r\n')

    with open('logs/' + filename + '.jsonl', 'w+') as log:
        log.write(json.dumps({
            'type': 'metadata',
            'metadata': data
        }) + '\r\n')

    start_time = time.process_time()

    return lambda data: _log_entry(filename, data, start_time)


def _log_entry(filename: str, data: dict, start_time: float):
    current_time = time.process_time()
    data['runtime'] = round((current_time - start_time) * 1000)

    with open('logs/' + filename + '.csv', 'a+') as log:
        log.write(f"{data['iteration']},{data['runtime']},{data['cost']:.0f},{len(data['path'])}\r\n")

    with open('logs/' + filename + '.jsonl', 'a+') as pathlog:
        pathlog.write(json.dumps({
            'type': 'entry',
            'data': data
        }) + '\r\n')


if __name__ == "__main__":
    main()
