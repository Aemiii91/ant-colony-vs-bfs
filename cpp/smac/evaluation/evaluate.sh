#!/bin/bash

DUMMYDATASET=" --data "../matrix500.json""
BERLINDATASET=' --data "../berlin.json"'
MUNCHENDATASET=' --data "../munchen.json"'
HAMBURGDATASET=' --data "../hamburg.json"'
BINARY="./routeplanner"
RESFILE="evaluation.txt"
STATICPARAM=" aco --iterations 500000 --ants 409 "
DEFAULTPARAM=" aco "
echo -e 'Running Evaluation \n'

CALL="$BINARY$STATICPARAM$DUMMYDATASET"
echo $DUMMYDATASET >> $RESFILE
exec $CALL >> $RESFILE

#example of evaluation

