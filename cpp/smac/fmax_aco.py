"""
Smac scripts for running aco, very minimal working example only varying one variable
"""

import logging
import subprocess
import os

from smac.facade.func_facade import fmin_smac

def acorunner(x):
    upperScore = 100
    staticparams = 'aco --data "matrix500.json" --colonies 5 --ants 50 --iterations 100 --alpha '
    dynamicAlpha = x[0]
    cmd = "./routeplanner "
    stdoutdata = subprocess.getoutput(cmd + staticparams + str(dynamicAlpha))
    print("dakke dak dakkity dakk: " + stdoutdata)
    return upperScore - int(stdoutdata)


# debug output
logging.basicConfig(level=20)
logger = logging.getLogger("Optimizer")  # Enable to show Debug outputs



x, cost, _ = fmin_smac(acorunner,
        x0=[1], #default config
        bounds=[(0,50)], #limits
        maxfun=30, #max number of evaluations
        rng=3) #random seed
print("Best x: %s; with cost: %f" % (str(x), cost))
