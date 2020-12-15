import logging
import sys
import subprocess

from run_berlin import runBerlin
from run_munchen import runMunchen
from run_hamburg import runHamburg

if __name__ == '__main__':
    ultraupper = 2000
    seed = sys.argv[5]
    x1 = sys.argv[7]
    x2 = sys.argv[9]
    x3 = sys.argv[11]
    x4 = sys.argv[13]
    x5 = sys.argv[15]
    paramlist = [x1,x2,x3,x4,x5]
    resBerlin = runBerlin(paramlist)
    resMunchen = runMunchen(paramlist)
    resHamburg = runHamburg(paramlist)
    res = ultraupper - (resBerlin + resMunchen + resHamburg)
    print('Result for SMAC: SUCCESS, 0, 0, %f, %s' % (res, seed))
