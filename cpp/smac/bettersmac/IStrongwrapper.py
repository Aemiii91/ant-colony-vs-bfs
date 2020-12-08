from strongwrapper import StrongWrapper

def IAcoWrapper(cmd, x):
    strong = StrongWrapper(cmd,x)
    strong.run()
    return strong.bestScore
