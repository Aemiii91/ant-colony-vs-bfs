import argparse
import json
import opencaching
import openroute
import dataset_cleaner


def strip_cache(cache: dict):
    cache.pop('longitude')
    cache.pop('latitude')
    return cache


def main():
    parser = argparse.ArgumentParser(description='Dataset Builder')
    parser.add_argument('--lat', default=52.518848, type=float)
    parser.add_argument('--lon', default=13.399411, type=float)
    parser.add_argument('--radius', default=50000, type=float)
    parser.add_argument('--limit', default=10, type=int)
    parser.add_argument('--save', default=None, type=str)
    args = parser.parse_args()

    openroute.api.go_offline()
    local_ready = openroute.check_status()

    if not local_ready:
        openroute.api.go_online()

    host = 'azure' if openroute.api.is_online() else 'localhost'
    print(f"Using '{host}'...")

    caches = opencaching.parse_results(
        opencaching.search(args.lat, args.lon, count=args.limit, radius=args.radius))
    locations_lonlat = [[cache['longitude'], cache['latitude']] for cache in caches]
    geocaches = [strip_cache(cache.copy()) for cache in caches]

    print(f'Found {len(caches)} caches. Building cost matrix...')

    matrix_data = openroute.matrix_builder_dir(locations_lonlat, nocache=True)

    if not matrix_data or 'error' in matrix_data:
        print('Error building matrix')
        print(matrix_data)
        return

    matrix_data['geocaches'] = geocaches

    query = matrix_data['metadata']['query']
    query['search_params'] = {
        "center": f"{args.lat}|{args.lon}",
        "radius": args.radius/1000,
        "type": "-Multi|Quiz|Moving",
        "status": "Available",
        "limit": args.limit
    }
    matrix_data['metadata']['query'] = query

    dataset_cleaner.clean_matrix_data(matrix_data)

    if (args.save):
        with open(args.save, 'w+') as outfile:
            json.dump(matrix_data, outfile)
        print(f"Saved to '{args.save}'.")


if __name__ == "__main__":
    main()
