import re
import argparse
import json
from ast import literal_eval
import numpy as np
from statistics import mean, median, variance, stdev
import path_analyzer


np.set_printoptions(edgeitems=30, linewidth=100000)


def parse_entry(textentry: str, datasets: dict) -> dict:
    lines = textentry.split('\n')
    command = re.sub(r' +', ' ', lines[0]).replace('"', '').split(' ')[0:-1]
    params = lines[1]
    runtime = int(literal_eval(lines[2][0:-1])*1000)
    (cost, score) = literal_eval(lines[3])
    path = literal_eval(lines[4])

    dataset = command[command.index('--data')+1].replace('.json', '')
    path_knum = path_analyzer.analyze_path(datasets[dataset], path)

    return {
        'command': command,
        'params': params,
        'runtime': runtime,
        'cost': cost,
        'score': score,
        'path': path,
        'dataset': dataset,
        'k_num': path_knum
    }


def dataset_stats(dataset: list, entries: list) -> dict:
    k_nums = [entry['k_num'] for entry in entries]
    k = [value for row in k_nums for value in row]
    return {
        'k_mean': mean(k),
        'k_median': median(k),
        'k_min': min(k),
        'k_max': max(k),
        'k_variance': variance(k),
        'k_stdev': stdev(k),
        'entries': entries
    }


def main():
    datasets = {
        'berlin': path_analyzer.get_cost_matrix('berlin'),
        'hamburg': path_analyzer.get_cost_matrix('hamburg'),
        'munchen': path_analyzer.get_cost_matrix('munchen')
    }
    data = ''

    with open('data/multiconfres.txt', 'r') as textfile:
        data = textfile.read()

    entries = {
        'berlin': [],
        'hamburg': [],
        'munchen': []
    }

    for textentry in data.split('\n\n')[0:-1]:
        entry = parse_entry(textentry, datasets)
        entries[entry['dataset']].append(entry)

    result = {
        'berlin': dataset_stats(datasets['berlin'], entries['berlin']),
        'hamburg': dataset_stats(datasets['hamburg'], entries['hamburg']),
        'munchen': dataset_stats(datasets['munchen'], entries['munchen'])
    }

    print('berlin:', result['berlin']['k_mean'])

    with open('data/multiconfres_knums.json', 'w+') as outfile:
        json.dump(result, outfile)


if __name__ == "__main__":
    main()
