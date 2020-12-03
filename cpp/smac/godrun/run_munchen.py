import subprocess


from getscore import getScore

def runmunchen(x, cmd):
    accumulatedScore = 0
    times = [1,10,30,60]
    city = ' --data "munchen.json" '
    dynamicAlpha = " --alpha " + str(x[0])
    dynamicBeta = " --beta " + str(x[1])
    dynamicEvaporation = " --evaporation " + str(x[2])
    dynamicAntCount = " --ants " + str(x[3])
    runcmd = cmd + city + dynamicAlpha + dynamicBeta + dynamicEvaporation + dynamicAntCount + ' --time '
    for x in times:
        stdoutdata = subprocess.getoutput(runcmd + str(x))
        accumulatedScore += getScore(stdoutdata)
    return accumulatedScore