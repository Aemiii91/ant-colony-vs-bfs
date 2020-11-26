#!/bin/bash

echo -e 'Running experiments in order of execution \n To find results see relevant logfile'

# first run
echo -e 'Running first experiment' 
python smacc --scenario scenario.txt &> scenario1log.txt
echo -e 'Running second experiment'

