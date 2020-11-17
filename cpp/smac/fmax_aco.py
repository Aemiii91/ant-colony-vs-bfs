"""
Smac scripts for running aco, very minimal working example only varying one variable
"""
 
import logging
import subprocess
import os
 
from smac.facade.func_facade import fmin_smac
 
def acorunner(x):
    #print(x)
    upperScore = 100
    staticparams = 'aco --data "matrix500.json" --colonies 3 --smac_mode '
    dynamicEvaporation = '--evaporation ' + str(x[0]) 
    dynamicAntCount = '--ants ' + str(x[1])
    dynamicIterations = '--iterations ' + str(x[2])
    dynamicParams = dynamicEvaporation + dynamicAntCount + dynamicIterations
    cmd = "./routeplanner "
    stdoutdata = subprocess.getoutput(cmd + staticparams + dynamicParams)
    #print('stdoutdata := ' + stdoutdata)
    #print('params := '+ dynamicParams)
    return upperScore - int(stdoutdata)
 
 
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
