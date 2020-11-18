import argparse
import json
import opencaching
import openroute


# berlin: 52.518848, 13.399411
# hamburg: 53.584721, 10.032828
# frankfurt: 50.155562, 8.700463


def main():
    parser = argparse.ArgumentParser(description='Dataset Builder')
    parser.add_argument('--lat', default=52.518848, type=float)
    parser.add_argument('--lon', default=13.399411, type=float)
    parser.add_argument('--count', default=10, type=int)
    parser.add_argument('--save', default=None, type=str)
    args = parser.parse_args()

    caches = opencaching.parse_results(
        opencaching.search(args.lat, args.lon, count=args.count))
    locations_lonlat = [[cache['longitude'], cache['latitude']] for cache in caches]
    cachecodes = [cache['code'] for cache in caches]

    matrix_data = openroute.matrix_builder_dir(locations_lonlat)

    if not matrix_data:
        return

    matrix_data['metadata']['cachecodes'] = cachecodes

    if (args.save):
        with open(args.save, 'w+') as outfile:
            json.dump(matrix_data, outfile)
        print(f"Saved to '{args.save}'.")


if __name__ == "__main__":
    main()
