#!/bin/bash

binary="./routeplanner "
berlindataset=" --data "berlin.json""
munchendataset=" --data "munchen.json""
hamburgdataset=" --data "hamburg.json""
resfile="multiconfres.txt"
paramset=" aco "
ants=" --ants 409"
iterations=" --iterations 500000"
time=" --time "
counter=1
paramsethighantcount1=" --alpha 10.7714 --beta 10.8111 "
paramsethighantcount10=" --alpha 1.4475 --beta 7.413 "
paramsethighantcount30=" --alpha 5.3434 --beta 8.5993 "
paramsethighantcount60=" --alpha 1.204 --beta 7.7799 "
paramsetdefaultantcount1=" --alpha 10.446 --beta 11.112 "
paramsetdefaultantcount10=" --alpha 4.4733 --beta 7.1462 "
paramsetdefaultantcount30=" --alpha 0.345 --beta 8.7237 "
paramsetdefaultantcount60=" --alpha 0.3257 --beta 9.6128 "
dataset=""

echo -e "Running multiconf \n"
while [ $counter -le "4" ]; do
    if [ $coutner -eq "1" ]
    then
       $dataset = $berlindataset 
       echo -e "configured for berlin"
    fi 
    if [ $coutner -eq "2" ]
    then
        $dataset = $munchendataset
        echo -e "configured for munchen"
    fi
    if [ $coutner -eq "3" ]
    then
        $dataset = $hamburgdataset
        echo -e "configured for hamburg"
    fi
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount1$time 1 "
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount10$time 10"
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount30$time 30"
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount60$time 60"
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount1$time 1 "
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount10$time 10"
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount30$time 30"
        $call >> $resfile
        call="$binary$dataset$paramset$ants$iterations$paramsethighantcount60$time 60"
        $call >> $resfile
        counter=$(($counter + 1 ))
done

echo -e "wrapping up, results can be found in" $resfile
