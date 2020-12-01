import subprocess
import os
import io
from ast import literal_eval as make_tuple
import re

class AcoMultEval:
    cmd = "./routeplanner "
    paramlist = []
    paramlist.append(" --alpha 3.7332 --beta 18.1784 ") #t1 
    paramlist.append(" --alpha 5.4488 --beta 28.0673 ") #t10
    paramlist.append(" --alpha 11.1573 --beta 16.1648 ") #t30
    paramlist.append(" --alpha 9.8187 --beta 20.7056 ") #t60
    paramlist.append(" --ants 409 --alpha 19.8319 --beta 16.7198 ") #t1
    paramlist.append(" --ants 409 --alpha 8.1972 --beta 8.409 ") #t10
    paramlist.append(" --ants 409 --alpha 0.3462 --beta 7.0424 ") #t30
    paramlist.append(" --ants 409 --alpha 18.7078 --beta 11.3746 ") #t60
    citylist = ['--data "munchen.json" --start 12']
    cmd = "./routeplanner aco --iterations 500000 "
    times = [" --time 1"," --time 10"," --time 30"," --time 60"]

    def AppendTofile(self,stdoutdata,city,params,times):
        stdoutio = io.StringIO(stdoutdata)
        lines = stdoutio.readlines()
        cost, points = make_tuple(lines[-2])
        score = self.CalculateScore(points, cost, 30000)
        paramset = self.SplitParameter(params)
        splitTimes = times.split()
        citysplit = city.split()
        csvRow = splitTimes[1] + "," + paramset[0] + "," + paramset[1] + "," + paramset[2] + "," + citysplit[1] + "," + citysplit[3] + "," + str(points) + "," + str(cost) + "," + "{:.4f}".format(score) + "\n"
        with open("redomunchen.csv","a") as myFile:
            myFile.write(csvRow)

    def EvaluateAll(self):
        print("Evaluation staring")
        for city in self.citylist:
            print("Evaluating city: " + city)
            for params in self.paramlist:
                print("using params" + params)
                for times in self.times:
                    print("Evaluating time " + times)
                    stdoutdata = subprocess.getoutput(self.cmd + str(city) + str(times) + str(params))
                    self.AppendTofile(stdoutdata,city,params,times)
        print("All done")

    def PrintCSVHeader(self):
        header = "Time,Alpha,Beta,Ants,City,StartingPoint,Points,TimeSpent,Score\n"
        with open("redomunchen.csv","a") as output:
            output.write(header)


    def CalculateScore(self, score: int, cost: float, constraint: float):
        return score + (1 - cost / constraint)

    def SplitParameter(self, paramset):
        split = paramset.split()
        if(split[0] == "--ants"):
            ants = split[1]
            alpha = split[3]
            beta = split[5]
        else:
            ants = "default"
            alpha = split[1]
            beta = split[3]
        return [alpha,beta,ants]

if __name__ == "__main__":
    print("Python script for evaluating our multiconf")
    evaluator = AcoMultEval()
    evaluator.PrintCSVHeader()
    evaluator.EvaluateAll()
    #stringtest = ' --data "berlin.json" --start 98 '
    #split = stringtest.split()
    #print(split)
