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
    alphabeta = " --alpha 1.204 --beta 7.7788"
    dynamictime = " --time 10"
    staticparams1 = ' aco --data "munchen.json" --iterations 500000'
    dynamicAnts = ' --ants ' + str(x[0])
    dynamicParams = dynamicAnts + dynamictime + alphabeta
    cmd = './routeplanner aco --data "munchen.json" --iterations 500000'
    stdoutdata = subprocess.getoutput(cmd + dynamicParams)
    print(cmd + dynamicParams)
    stdoutio = io.StringIO(stdoutdata)
    lines = stdoutio.readlines()
    cost, score = make_tuple(lines[-2])
    result = calc_result(score, cost, staticConstraint) 
    return upperScore - result
 
def calc_result(score: int, cost: float, constraint: float):
    return score + (1 - cost / constraint)
