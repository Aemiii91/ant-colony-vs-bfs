"""
Smac scripts for running aco, very minimal working example only varying one variable
"""
 
import logging
import subprocess
import os
 
from smac.facade.func_facade import fmin_smac
 
def acorunner(x):
    upperScore = 100
    staticparams = 'aco --data "matrix500.json" --colonies 8 --ants 20 --iterations 40 '
    dynamicAlpha = '--alpha ' + str(x[0])
    dynamicBeta  = '--beta ' + str(x[1])
    dynamicEvaporation = '--evaporation ' + str(x[2]) 
    dynamicPheromone = '--pheromone ' + str(x[3])
    dynamicParams = dynamicAlpha + dynamicBeta + dynamicEvaporation + dynamicPheromone
    cmd = "./routeplanner "
    stdoutdata = subprocess.getoutput(cmd + staticparams + dynamicParams)
    print('stdoutdata := ' + stdoutdata)
    return upperScore - int(stdoutdata)
 
 
# debug output
logging.basicConfig(level=20)
logger = logging.getLogger("Optimizer")  # Enable to show Debug outputs
 
# cost (time constraint) is set as a default in the program as 30k
# arguments in x in order: alpha, beta, evaporationRate, pheromone
x, cost, _ = fmin_smac(acorunner,
        x0=[1, 20, 0.4, 100], #default config
        bounds=[(0,20), (5,25), (0.01, 0.99), (50,100)], #limits
        maxfun=500, #max number of evaluations
        rng=3) #random seed
print("Best x: %s; with cost: %f" % (str(x), cost))

