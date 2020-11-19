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
    staticparams1 = 'aco --data "munchen.json" --colonies 1 --ants 409 --iterations 90'
    staticparams2 = 'aco --data "berlin.json" --colonies 1 --ants 409 --iterations 90'
    staticparams3 = 'aco --data "hamburg.json" --colonies 1 --ants 409 --iterations 90'
    dynamicAlpha = ' --alpha ' + str(x[0])
    dynamicBeta = ' --beta ' + str(x[1])
    dynamicParams = dynamicAlpha + dynamicBeta 
    cmd = "./routeplanner "

    stdoutdata1 = subprocess.getoutput(cmd + staticparams1 + dynamicParams)
    stdoutdata2 = subprocess.getoutput(cmd + staticparams2 + dynamicParams)
    stdoutdata3 = subprocess.getoutput(cmd + staticparams3 + dynamicParams)
    stdoutio1 = io.StringIO(stdoutdata1)
    stdoutio2 = io.StringIO(stdoutdata2)
    stdoutio3 = io.StringIO(stdoutdata3)
    lines1 = stdoutio1.readlines()
    lines2 = stdoutio2.readlines()
    lines3 = stdoutio3.readlines()
    cost1, score1 = make_tuple(lines1[-2])
    cost2, score2 = make_tuple(lines2[-2])
    cost3, score3 = make_tuple(lines3[-2])
    result = calc_result(score1, cost1, staticConstraint) + calc_result(score2, cost2, staticConstraint) + calc_result(score3, cost3, staticConstraint)
    return upperScore - result
 
def calc_result(score: int, cost: float, constraint: float):
    return score + (1 - cost / constraint)

