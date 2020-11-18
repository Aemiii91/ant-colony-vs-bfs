import argparse
import time
from datetime import datetime

import openroute


def main():
    parser = argparse.ArgumentParser(description='Ping ORS')
    parser.add_argument('--online', help='Ping online endpoint', action='store_true')
    args = parser.parse_args()
    
    openroute.api.go_online()
    openroute.api.toggle_online(args.online)
    is_ready = False

    host = 'azure' if openroute.api.is_online() else 'localhost'

    print(f"Pinging '{host}' every 10s...")

    while not is_ready:
        is_ready = openroute.check_status()
        now = datetime.now()
        clock = now.strftime("%H:%M:%S")

        if is_ready:
            print(f'{clock} - Ready    ')
        else:
            print(f'{clock} - Not ready', end='\r')

        time.sleep(10)


if __name__ == "__main__":
    main()