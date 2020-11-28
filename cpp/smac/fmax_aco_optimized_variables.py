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
    staticparams1 = 'aco --data "munchen.json" --colonies 1 --ants 409 --iterations 50000000 --time 1 '
    dynamicAlpha = ' --alpha ' + str(x[0])
    dynamicBeta = ' --beta ' + str(x[1])
    dynamicParams = dynamicAlpha + dynamicBeta 
    cmd = "./routeplanner "

    stdoutdata1 = subprocess.getoutput(cmd + staticparams1 + dynamicParams)
    stdoutio1 = io.StringIO(stdoutdata1)
    lines1 = stdoutio1.readlines()
    cost1, score1 = make_tuple(lines1[-2])
    result = calc_result(score1, cost1, staticConstraint) 
    return upperScore - result
 
def calc_result(score: int, cost: float, constraint: float):
    return score + (1 - cost / constraint)

