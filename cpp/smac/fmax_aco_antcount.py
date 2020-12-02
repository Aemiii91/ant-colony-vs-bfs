import logging
import time
import subprocess
import os
import io
from ast import literal_eval as make_tuple
 
from smac.facade.func_facade import fmin_smac 
 
def acorunner(x):
    #print(x)
    staticConstraint = 30000
    upperScore = 500
    dynamictime = " --time 1"
    staticparams1 = ' aco --data "munchen.json" --iterations 500000'
    staticparams2 = ' aco --data "berlin.json" --iterations 500000'
    staticparams3 = ' aco --data "hamburg.json" --iterations 500000'
    print(x)
    dynamicAnts = ' --ants ' + str(x[3])
    dynamicAlpha = ' --alpha ' + str(x[0])
    dynamicBeta = ' --beta ' + str(x[1])
    dynamicEvap = ' --evaporation ' + str(x[2])
    dynamicParams = dynamicAlpha + dynamicBeta + dynamicEvap + dynamicAnts + dynamictime
    cmd = "./routeplanner"

    stdoutdata1 = subprocess.getoutput(cmd + staticparams1 + dynamicParams)
    stdoutdata2 = subprocess.getoutput(cmd + staticparams2 + dynamicParams)
    stdoutdata3 = subprocess.getoutput(cmd + staticparams3 + dynamicParams)

    stdoutio = io.StringIO(stdoutdata1)
    stdoutio1 = io.StringIO(stdoutdata2)
    stdoutio2 = io.StringIO(stdoutdata3)

    lines = stdoutio.readlines()
    lines1 = stdoutio1.readlines()
    lines2 = stdoutio2.readlines()

    cost, score = make_tuple(lines[-2])
    cost1, score1 = make_tuple(lines1[-2])
    cost2, score2 = make_tuple(lines2[-2])

    result = calc_result(score, cost, staticConstraint) + calc_result(score1, cost1, staticConstraint) + calc_result(score2, cost2, staticConstraint)
    return upperScore - result
 
def calc_result(score: int, cost: float, constraint: float):
    return score + (1 - cost / constraint)
