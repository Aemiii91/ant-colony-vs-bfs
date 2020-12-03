import io
from ast import literal_eval as make_tuple

def getScore(stdoutdata):
    staticConstraint = 30000
    stdoutio = io.StringIO(stdoutdata)
    lines = stdoutio.readlines()
    cost, score = make_tuple(lines[-2])
    score = calc_result(score, cost, staticConstraint)
    return score

def calc_result(score: int, cost: float, constraint: float):
    return score + (1 - cost / constraint)
