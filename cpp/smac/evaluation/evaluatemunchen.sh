#!/bin/bash

munchenDataset=" --data "munchen.json""
BINARY="./routeplanner"

STATICPARAM=" aco --iterations 500000 --ants 409 "
DEFAULTPARAM=" aco --iterations 500000 "
munchenStartingpoint=" --start 45 "
munchenres="munchenres.txt"
echo -e 'Running Evaluation \n'

timer=" --time "

munchenCall="$BINARY$DEFAULTPARAM$munchenDataset$munchenStartingpoint$timer 1"
echo -e 'Executing Munchen time = 1 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 1 stating point='$munchenStartingpoint >> $munchenres
munchenparams=" --alpha 3.7332 --beta 18.1784 "
munchenCall="$BINARY$STATICPARAM$munchenDataset$munchenStartingpoint$munchenparams$timer 1"
$munchenCall >> $munchenres
echo -e 'Executing Munchen time = 10 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 10 stating point='$munchenStartingpoint >> $munchenres
munchenparams=" --alpha 5.4488 --beta 28.0673 "
munchenCall="$BINARY$STATICPARAM$munchenDataset$munchenStartingpoint$munchenparams$timer 10"
$munchenCall >> $munchenres

munchenparams=" --alpha 11.1563 --beta 16.1648 "
echo -e 'Executing Munchen time = 30 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 30 stating point='$munchenStartingpoint >> $munchenres
munchenCall="$BINARY$STATICPARAM$munchenDataset$munchenStartingpoint$munchenparams$timer 30"
$munchenCall >> $munchenres

munchenparams=" --alpha 9.8187 --beta 20.7056 "
echo -e 'Executing Munchen time = 60 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 60 stating point='$munchenStartingpoint >> $munchenres
munchenCall="$BINARY$STATICPARAM$munchenDataset$munchenStartingpoint$munchenparams$timer 60"
$munchenCall >> $munchenres

echo -e 'ants = 409 time \n'

munchenparams=" --alpha 19.8319 --beta 16.7198"
munchenCall="$BINARY$STATICPARAM$munchenDataset$munchenStartingpoint$timer 1"
echo -e 'Executing Munchen time = 1 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 1 stating point='$munchenStartingpoint >> $munchenres
$munchenCall >> $munchenres

echo -e 'Executing Munchen time = 10 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 10 stating point='$munchenStartingpoint >> $munchenres
munchenparams=" --alpha 8.1972	--beta 8.787"
munchenCall="$BINARY$DEFAULTPARAM$munchenDataset$munchenStartingpoint$timer 10"
$munchenCall >> $munchenres

echo -e 'Executing Munchen time = 30 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 30 stating point='$munchenStartingpoint >> $munchenres
munchenparams=" --alpha 0.3462	--beta 7.0424"
munchenCall="$BINARY$DEFAULTPARAM$munchenDataset$munchenStartingpoint$timer 30"
$munchenCall >> $munchenres

echo -e 'Executing Munchen time = 60 stating point='$munchenStartingpoint
echo -e 'Executing Munchen time = 60 stating point='$munchenStartingpoint >> $munchenres
munchenparams=" --alpha 18.7078	--beta 11.3746"
munchenCall="$BINARY$DEFAULTPARAM$munchenDataset$munchenStartingpoint$timer 60"
$munchenCall >> $munchenres

