import os
import subprocess
import signal
import threading
import time

class StrongWrapper:
    processAlive = True
    staticConstraint = 30000
    wallClockLimit = 3.0
    lowerboundScore = 30
    bestScore = 0.0
    cmd = ""
    def __init__(self,cmd,x,wallClockLimit):
        self.wallClockLimit = wallClockLimit
        self.commandBuilder(cmd,x)

    def kill(self, pid):
        os.killpg(os.getpgid(pid), signal.SIGTERM)
        self.processAlive = False
        print("Terminated due to runclock limitations")

    def commandBuilder(self,cmd,x):
        self.cmd = cmd + " --alpha " + str(x[0]) + " --beta " + str(x[1]) + " --evaporation " + str(x[2]) + " --ants " + str(x[3])
        print(self.cmd)

    def run(self):
        currentScore = 0
        proc = subprocess.Popen(self.cmd, stdout=subprocess.PIPE, shell=True, bufsize=1
                                , universal_newlines=True, preexec_fn=os.setsid)
        while True:
            t = threading.Timer(self.wallClockLimit, self.kill, [proc.pid])
            retcode = proc.poll()
            t.start()
            line = proc.stdout.readline()
            print(line)
            time.sleep(0.05)
            t.cancel()
            if self.processAlive:
                currentScore = self.getScore(line)
                self.bestScore = currentScore
                if (currentScore <= self.lowerboundScore):
                    self.kill(proc.pid)
                    print("killed process early due to lowerbound")
                    break
            else:
                break
            if retcode is not None:
                print("finished naturally")
                break
        self.bestScore = currentScore

    def getScore(self,line):
        if(len(line) > 1):
            combine = line.split(",")
            cost = float(combine[0])
            score = float(combine[1])
            return score + (1 - cost / self.staticConstraint)
        else:
            return self.bestScore


