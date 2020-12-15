from IStrongwrapper import IAcoWrapper as acow

def runHamburg(x):
    cmd1 = './routeplanner aco --data "hamburg.json" --iterations 500000 --progress2 --time 1 '
    cmd10 = './routeplanner aco --data "hamburg.json" --iterations 500000 --progress2 --time 10 '
    cmd30 = './routeplanner aco --data "hamburg.json" --iterations 500000 --progress2 --time 30 '
    cmd60 = './routeplanner aco --data "hamburg.json" --iterations 500000 --progress2 --time 60 '
    res1 = acow(cmd1,x,60)
    res10 = acow(cmd10,x,60)
    res30 = acow(cmd30,x,60)
    res60 = acow(cmd60,x,60)
    return (res1 + res10 + res30 + res60)
