import subprocess
import os
import io
from ast import literal_eval as make_tuple
import re

class AcoMultEval:
    cmd = "./routeplanner "
    paramlist = []
    paramlist.append(" --alpha 10.446 --beta 11.112 ") #t1 
    paramlist.append(" --alpha 4.4733 --beta 7.1462 ") #t10
    paramlist.append(" --alpha 0.345 --beta 8.7237 ") #t30
    paramlist.append(" --alpha 0.3257 --beta 9.6128 ") #t60
    paramlist.append(" --ants 409 --alpha 10.7714 --beta 10.8111 ") #t1
    paramlist.append(" --ants 409 --alpha 1.4475 --beta 7.4313 ") #t10
    paramlist.append(" --ants 409 --alpha 5.3434 --beta 8.5993 ") #t30
    paramlist.append(" --ants 409 --alpha 1.2404 --beta 7.7788 ") #t60
    citylist = [' --data "berlin.json" --start 98',' --data "hamburg.json" --start 65',' --data "munchen.json" --start 12']
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
        with open("multiconfres.txt","a") as myFile:
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
        with open("multiconfres.txt","a") as output:
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
