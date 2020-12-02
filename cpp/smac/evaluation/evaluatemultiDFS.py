import os
import subprocess


if __name__ == "__main__":
    print("Evaluating multi k for k-DFS thing")
    cmd = './routeplanner '
    for k in range(20):
        stdoutdata = subprocess.getoutput(cmd + " munchen.json " + str(k+1) + " 10")
        print("Evaluating for k = " + str(k))
        print(stdoutdata)
        print("\n")

