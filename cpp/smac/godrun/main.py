# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

from run_berlin import runberlin
from run_hamburg import runhamburg
from run_munchen import runmunchen


def run(x):
    upperScore: int = 2000
    cmd = "./routeplanner aco --iterations 50000"
    finalScore: float = upperScore - (runberlin(x, cmd) + runhamburg(x, cmd) + runmunchen(x, cmd))
    return finalScore
