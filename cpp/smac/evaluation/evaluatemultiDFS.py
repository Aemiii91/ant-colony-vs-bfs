import os
import subprocess
import io
import csv
from ast import literal_eval as make_tuple

def PrintCSVHeader():
    header = "time,city,cost,points,startingPoint,k\n"
    with open("kdfs.csv","a") as output:
        output.write(header)

if __name__ == "__main__":
    resultList = []
    time = " 1"
    startingPoint = " 12"
    PrintCSVHeader()
    print("Evaluating multi k for k-DFS thing")
    cmd = './dfsplanner '
    for k in range(30):
        print(cmd + " munchen.json " + str(k+1) + time + startingPoint)
        stdoutdata = subprocess.getoutput(cmd + " munchen.json " + str(k+1) + time + startingPoint)
        stdoutio = io.StringIO(stdoutdata)
        lines = stdoutio.readlines()
        cost, score = make_tuple(lines[-2])
        res = [time,"munchen",cost,score,startingPoint,str(k+1)]
        resultList.append(res)


    with open("kdfs.csv","a") as output:
        reswriter = csv.writer(output,delimiter=',')
        for row in resultList:
            reswriter.writerow(row)

