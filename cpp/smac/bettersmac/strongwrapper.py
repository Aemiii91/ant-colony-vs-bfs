import os
import subprocess
import signal
import threading
import time

class StrongWrapper:
    processAlive = True
    staticConstraint = 30000
    wallClockLimit = 3.0
    lowerboundScore = 53.0
    bestScore = 0.0

    def kill(self, pid):
        os.killpg(os.getpgid(pid), signal.SIGTERM)
        self.processAlive = False
        print("Terminated due to runclock limitations")

    def run(self, cmd, x):
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True, bufsize=1
                                , universal_newlines=True, preexec_fn=os.setsid)
        while True:
            t = threading.Timer(self.wallClockLimit, self.kill, [proc.pid])
            retcode = proc.poll()
            t.start()
            line = proc.stdout.readline()
            time.sleep(0.05)
            t.cancel()
            if self.processAlive:
                currentScore = self.getScore(line)
                if (currentScore <= self.lowerboundScore):
                    self.kill(proc.pid)
                    print("killed process early")
                    break
            else:
                break
            if retcode is not None:
                break
        self.bestScore = currentScore

    def getScore(self,line):
        combine = line.split(",")
        cost = float(combine[0])
        score = float(combine[1])
        return score + (1 - cost / self.staticConstraint)


