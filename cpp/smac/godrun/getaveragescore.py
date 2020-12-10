import subprocess
import sys
from getscore import getScore

def AppendtoFile(string):
    resstring = str(string[0]) + "," + str(string[1]) + "\n"
    with open("averagegodrunres.txt","a") as out:
              out.write(resstring)

def calculateAverage(argv):
    args = argv
    if args:
        print("File parsed: " + str(args))
    else:
        print("Please specify a json file.")
        return
    
    cmd = './routeplanner aco --iterations 500000 --data "' + str(args) + '" --alpha 65 --beta 9 --ants 971 --evaporation 0.0353 --time '
    print(cmd)
    accumulatedAverage = 0
    calculatedAverage = 0
    iterations = 10
    times = [1,10,30,60]
    for x in times:
        for y in range(iterations):
            stdoutdata = subprocess.getoutput(cmd + str(x))
            score = getScore(stdoutdata)
            paramstring = [x,score]
            AppendtoFile(paramstring)
            accumulatedAverage += score
            print("Iteration: " + str(y) + " acumulatedAverage: " + str(accumulatedAverage))
                
        calculatedAverage = accumulatedAverage / iterations
        print("Time: " + str(x) + " Average score: " + str(calculatedAverage)) 
        accumulatedAverage = 0

if __name__ == '__main__':
    with open("averagegodrunres.txt","a") as out:
        out.write("time,score\n")
    calculateAverage(sys.argv[1])
    # write header
    
