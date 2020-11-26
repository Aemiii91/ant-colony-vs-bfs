#!/bin/bash

hamburgDataset=" --data "hamburg.json""
BINARY="./routeplanner"

STATICPARAM=" aco --iterations 500000 --ants 409 "
DEFAULTPARAM=" aco --iterations 500000 "
hamburgStartingpoint=" --start 32 "
hamburgres="hamburgres.txt"
echo -e 'Running Evaluation \n'

timer=" --time "

hamburgCall="$BINARY$STATICPARAM$hamburgDataset$hamburgStartingpoint$timer 1"
echo -e 'Executing Hamburg time = 1 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 1 stating point='$hamburgStartingpoint >> $hamburgres
hamburgparams=" --alpha 6.3757 --beta 5.57511 "
hamburgCall="$BINARY$STATICPARAM$hamburgDataset$hamburgStartingpoint$hamburgparams$timer 1"
$hamburgCall >> $hamburgres
echo -e 'Executing Hamburg time = 10 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 10 stating point='$hamburgStartingpoint >> $hamburgres
hamburgparams=" --alpha 0.6282 --beta 2.7992 "
hamburgCall="$BINARY$STATICPARAM$hamburgDataset$hamburgStartingpoint$hamburgparams$timer 10"
$hamburgCall >> $hamburgres

hamburgparams=" --alpha 0.5441 --beta 5.0464 "
echo -e 'Executing Hamburg time = 30 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 30 stating point='$hamburgStartingpoint >> $hamburgres
hamburgCall="$BINARY$STATICPARAM$hamburgDataset$hamburgStartingpoint$hamburgparams$timer 30"
$hamburgCall >> $hamburgres

hamburgparams=" --alpha 1.5538 --beta 7.1643 "
echo -e 'Executing Hamburg time = 60 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 60 stating point='$hamburgStartingpoint >> $hamburgres
hamburgCall="$BINARY$STATICPARAM$hamburgDataset$hamburgStartingpoint$hamburgparams$timer 60"
$hamburgCall >> $hamburgres

echo -e 'Default value time \n'

hamburgparams=" --alpha 17.9152	--beta 5.2609"
hamburgCall="$BINARY$DEFAULTPARAM$hamburgDataset$hamburgStartingpoint$timer 1"
echo -e 'Executing Hamburg time = 1 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 1 stating point='$hamburgStartingpoint >> $hamburgres
$hamburgCall >> $hamburgres

echo -e 'Executing Hamburg time = 10 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 10 stating point='$hamburgStartingpoint >> $hamburgres
hamburgparams=" --alpha 3.7478	--beta 4.6386"
hamburgCall="$BINARY$DEFAULTPARAM$hamburgDataset$hamburgStartingpoint$timer 10"
$hamburgCall >> $hamburgres

echo -e 'Executing Hamburg time = 30 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 30 stating point='$hamburgStartingpoint >> $hamburgres
hamburgparams=" --alpha 0.3817	--beta 6.8462"
hamburgCall="$BINARY$DEFAULTPARAM$hamburgDataset$hamburgStartingpoint$timer 30"
$hamburgCall >> $hamburgres

echo -e 'Executing Hamburg time = 60 stating point='$hamburgStartingpoint
echo -e 'Executing Hamburg time = 60 stating point='$hamburgStartingpoint >> $hamburgres
hamburgparams=" --alpha 10.4561	--beta 5.7974"
hamburgCall="$BINARY$DEFAULTPARAM$hamburgDataset$hamburgStartingpoint$timer 60"
$hamburgCall >> $hamburgres

