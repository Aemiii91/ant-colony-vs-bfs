import subprocess
import sys
from getscore import getScore

def calculateAverage(argv):
    args = argv
    if args:
        print("File parsed: " + str(args))
    else:
        print("Please specify a json file.")
        return
    
    cmd = './routeplanner aco --iterations 500000 --data "' + str(args) + '" --time '
    print(cmd)
    accumulatedAverage = 0
    calculatedAverage = 0
    iterations = 10
    times = [1,10,30,60]
    for x in times:
        for y in range(iterations):
            stdoutdata = subprocess.getoutput(cmd + str(x))
            accumulatedAverage += getScore(stdoutdata)
            print("Iteration: " + str(y) + " acumulatedAverage: " + str(accumulatedAverage))
                
        calculatedAverage = accumulatedAverage / iterations
        print("Time: " + str(x) + " Average score: " + str(calculatedAverage)) 
        accumulatedAverage = 0

if __name__ == '__main__':
    calculateAverage(sys.argv[1])
