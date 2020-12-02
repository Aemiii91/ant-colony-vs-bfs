import os
import subprocess


if __name__ == "__main__":
    print("Evaluating multi k for k-DFS thing")
    cmd = './dfsplanner '
    for k in range(5):
        stdoutdata = subprocess.getoutput(cmd + " munchen.json " + str(k+1) + " 10" + " 12")
        print("Evaluating for k = " + str(k))
        print(stdoutdata)
        print("\n")

