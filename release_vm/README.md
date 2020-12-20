# Virtual box
A virtual machine was created were both the binaries and datasets used can be found.
This virtual machine serves as a sandbox created for the sole purpose of trying and playing with our project.
The virtual machine is running Manjaro 20.2 Nibia with no desktop environment, just the tty

`username: p5`

`passwd: 123`

The root password is the same as the user password

The virtual machine requires the following specifications as a bare minimum:
- 2gb ram
- 8gb of free storage
- 1 cpu core

If you want to increase performance you may tweak these settings to your liking.
The ACO algortihm definitely benefits from more CPU power.

Download link for the virtual box image: https://drive.google.com/drive/folders/1Mf3fvDLdG0YHtieQB9HlOMBaN7409Kvg?usp=sharing

To use our algorithms please go to ~/projectbinaries

Here you will find a binary and three datasets.
The three datasets are the same datasets as those used in the project report.
The binary can invoke both our ACO algorithm and our K-DFS algorithm.

The full source for both of these algorithms can be found in ~/Documents/P5-Kode

ACO can be invoked by the following command

`./routeplanner aco --data "berlin.json"`

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
- --best_ants
- --noreturn
- --progress
- --start (starting point)

The default configuration for ACO is as follows:
- Alpha: 1
- Beta: 20
- Evaporation: 0.04
- PheromoneConstant: 100
- antCount: 50
- iterations 80
- bestAntLimit 1

All experiments and findings in the report have been done with bestAntLimit = 1, but keep in mind that changing the bestAntLimit may change the ACO implementation to something other than ant system.


Our K-DFS algorithm can be invoked with the following command

`./routeplanner --data "berlin.json" -k 2 --cost 500`

Here berlin.json is interchangeable with whichever dataset you may want to use.
This algorithm does not take as many parameters as our aco algortihm, but the ordering is like follows, however you may tune the k-limit and time constraint to your liking.
Both of these are given as integers and the time constraint is given in seconds.
