# to use this wrapper with smacc run 
# python smacc --scenario scenario.txt

import logging
import sys
import subprocess

from fmax_aco_antcount import acorunner

if __name__ == '__main__':
    seed = sys.argv[5]
    x1 = sys.argv[7]
    x2 = sys.argv[9]
    x3 = sys.argv[11]
    x4 = sys.argv[13]
    paramlist = [x1,x2,x3,x4]
#    print(x1)
    #print(paramlist)
    res = acorunner(paramlist)
    print('Result for SMAC: SUCCESS, 0, 0, %f, %s' % (res, seed))
