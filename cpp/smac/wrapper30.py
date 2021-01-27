# to use this wrapper with smacc run 
# python smacc --scenario scenario.txt

import logging
import sys
import subprocess

from fmax_aco_t30 import acorunner

if __name__ == '__main__':
    seed = sys.argv[5]
    x1 = sys.argv[7]
    x2 = sys.argv[9]
    res = acorunner((x1, x2))
    print('Result for SMAC: SUCCESS, 0, 0, %f, %s' % (res, seed))