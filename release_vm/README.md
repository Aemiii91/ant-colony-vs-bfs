# Virtual box
A virtual machine was created were both the binaries and datasets used can be found.
This virtual machine serves as a sandbox created for the sole purpose of trying and playing with our project.
The virtual machine is running Manjaro 20.2 Nibia with no desktop environment, just the tty

```username: p5```

```passwd: 123```

The root password is the same as the user password

The virtual machine requires the following specifications as a bare minimum:
- 2gb ram
- 8gb of free storage
- 1 cpu core

If you want to increase performance you may tweak these settings to your liking.
The ACO algortihm definitely benefits from more CPU power.

Download link for the virtual box image: https://drive.google.com/drive/folders/1Mf3fvDLdG0YHtieQB9HlOMBaN7409Kvg?usp=sharing

To use our algorithms please go to ~/projectbinaries

Here you will find two binaries and three datasets.
The three datasets are the same datasets as those used in the project report.
The two binaries each contain one of our two algorithms.

The full source for both of these algortihms can be found in ~/Documents/P5-Kode

## acoplanner
acoplanner contains our ACO algorithm and can be invoked by the following command

```./acoplanner aco --data "berlin.json"```

berlin.json in the above example can be swapped out with whichever dataset you may want to try.
The following flags are available for our ACO:
- --iterations
- --time
- --ants
- --alpha
- --beta
- --evaporation
- --pheromone
- --cost
- --colonies
- --nothreading
- --noreturn
- --progress
- --progress2 (mode used internally for SMAC)
- --smac_mode (depricated mode used for SMAC, but still useful)
- --start (starting point)

## Branch limited DFS
The kdfsplanner contains our implementation of our Branch limited DFS algortihm
This algortihm can be invoked with the following command

`./dfsplanner berlin.json 5 100 0`

Here berlin.json is interchangeable with whichever dataset you may want to use.
This binary does not take as many parameters as our aco algortihm, but the ordering is like follows:

`./dfsplanner dataset k-limit time-limit starting-point`

Where the timelimit is given in seconds
