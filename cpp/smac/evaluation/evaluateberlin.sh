#!/bin/bash

DUMMYDATASET=" --data "../matrix500.json""
BERLINDATASET=" --data "berlin.json""
MUNCHENDATASET=' --data "../munchen.json"'
HAMBURGDATASET=' --data "../hamburg.json"'
BINARY="./routeplanner"
RESFILE="evaluation.txt"
STATICPARAM=" aco --iterations 500000 --ants 409 "
DEFAULTPARAM=" aco --iterations 500000"
echo -e 'Running Evaluation \n'

#berlin.json
berlinStartingPoint=" --start 99 "
berlinResFile="berlinres.txt"
berlinCall="$BINARY$STATICPARAM$BERLINDATASET$berlinStartingPoint"
berlinParams=" --alpha 19.1147 --beta 14.5498 --time 1"
echo -e 'Executing Berlin time = 1 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 1 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile
berlinParams=" --alpha 2.904 --beta 7.3131 --time 10"
echo -e 'Executing Berlin time = 10 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 10 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile
berlinParams=" --alpha 3.811 --beta 6.3181 --time 30"
echo -e 'Executing Berlin time = 30 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 30 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile
berlinParams=" --alpha 1.7969 --beta 3.3543 --time 60"
echo -e 'Executing Berlin time = 60 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 60 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile


berlinCall="$BINARY$DEFAULTPARAM$BERLINDATASET$berlinStartingPoint"

berlinParams=" --alpha 8.3969 --beta 9.4168 --time 1 "
echo -e 'Executing Berlin time = 1 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 1 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile
berlinParams=" --time 10 --alpha 0.6138 --beta 3.4614"
echo -e 'Executing Berlin time = 10 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 10 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile
berlinParams=" --time 30 --alpha 0.6775 --beta 4.6347"	
echo -e 'Executing Berlin time = 30 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 30 stating point='$berlinStartingPoint >> $berlinResFile
$berlinCall$berlinParams >> $berlinResFile
echo -e 'Executing Berlin time = 60 stating point='$berlinStartingPoint
echo -e 'Executing Berlin time = 60 stating point='$berlinStartingPoint >> $berlinResFile
berlinParams=" --time 60 --alpha 0.4627 --beta 9.1549"	
$berlinCall$berlinParams >> $berlinResFile
