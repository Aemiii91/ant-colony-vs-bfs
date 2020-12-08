from strongwrapper import StrongWrapper

def IAcoWrapper(cmd, x):
    cmd = './routeplanner aco --data "berlin.json" --progress2 --iterations 500000 --time 30 '
    strong = StrongWrapper()
    strong.run(cmd,"")
    return strong.bestScore
