"""
Smac scripts for running aco, very minimal working example only varying one variable
"""
 
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
    staticparams = 'aco --data "munchen.json" --time 60 --colonies 1 '
    dynamicAlpha = ' --alpha ' + str(x[0])
    dynamicBeta = ' --beta ' + str(x[1])
    dynamicParams = dynamicAlpha + dynamicBeta 
    cmd = "./routeplanner "

    stdoutdata = subprocess.getoutput(cmd + staticparams + dynamicParams)
    stdoutio = io.StringIO(stdoutdata)
    lines = stdoutio.readlines()
    cost, score = make_tuple(lines[-2])
    result = upperScore - calc_result(score, cost, staticConstraint)
    return result
 
def calc_result(score: int, cost: float, constraint: float):
    return score + (1 - cost / constraint)

# debug output
#logging.basicConfig(level=20)
#logger = logging.getLogger("Optimizer")  # Enable to show Debug outputs
# 
## cost (time constraint) is set as a default in the program as 30k
## arguments in x in order: alpha, beta, evaporationRate, pheromone, best_ant
#x, cost, _ = fmin_smac(acorunner,
#        x0=[1, 20, 0.4, 100, 1], #default config
#        bounds=[(1,100), (0, 100), (0.01, 0.99), (1,1000), (1,10)], #limits
#        maxfun=2, #max number of evaluations
#        rng=3) #random seed
#print("Best x: %s; with cost: %f" % (str(x), cost))
#
