import datetime


def k_complexity(k, n=20):
    return min(k, n) * k_complexity(k, n-1) if n > 1 else 1


def main():
    n = 31
    k = 3

    print(f'n={n}')

    last_comp = k_complexity(2, n)
    present_comp = k_complexity(k, n)

    print('k=2 complexity:', last_comp)
    print('k=3 complexity:', present_comp)

    growth = (present_comp - last_comp) / last_comp

    print('Growth rate:', growth)

    last_time = 1377
    present_time = last_time * growth

    print(f'Seconds (k=2):', last_time)
    print(f'Seconds (k={k}):', present_time)
    
    s = present_time
    years = int(s / (365 * 24 * 3600))
    s = s % (365 * 24 * 3600)
    days = int(s / (24 * 3600))
    s = s % (24 * 3600)
    hours = int(s / 3600)
    s = s % 3600
    minutes = int(s / 60)
    s = s % 60
    seconds = int(s)

    print(f"{years} years, {days} days, {hours} hours, {minutes} minutes, {seconds} seconds")



if __name__ == "__main__":
    main()
