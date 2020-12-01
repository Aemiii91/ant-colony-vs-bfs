# to use this wrapper with smacc run 
# python smacc --scenario scenario.txt

import logging
import sys
import subprocess

from fmax_aco_antcount import acorunner

if __name__ == '__main__':
    seed = sys.argv[5]
    x1 = sys.argv[7]
#    print(x1)
    res = acorunner((x1))
    print('Result for SMAC: SUCCESS, 0, 0, %f, %s' % (res, seed))
