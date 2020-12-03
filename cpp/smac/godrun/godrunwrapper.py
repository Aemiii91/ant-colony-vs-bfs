# parameters to run
# alpha
# beta
# evaporation
# ant count
# iterations should not be optimized but merely set to a high enough count to spend all the time

import sys

from main import run

if __name__ == '__main__':
    seed = sys.argv[5]
    # alpha = sys.argv[7] first argument is at index 7, then it increments by 2
    alpha = sys.argv[7]
    beta = sys.argv[9]
    evaporation = sys.argv[11]
    antcount = sys.argv[13]
    res = run((alpha, beta, evaporation, antcount))
    print('Result for SMAC: SUCCESS, 0, 0, %f, %s' % (res, seed))
