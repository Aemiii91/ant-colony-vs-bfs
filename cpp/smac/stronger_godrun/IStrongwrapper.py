from strongwrapper import StrongWrapper

def IAcoWrapper(cmd, x,wallClockLimit=5.0):
    strong = StrongWrapper(cmd,x,wallClockLimit)
    strong.run()
    return strong.bestScore
