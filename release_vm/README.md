# Virtual box
A virtual machine was created were both the binaries and datasets used can be found.
This virtual machine serves as a sandbox created for the sole purpose of trying and playing with our project.
The virtual machine is running Manjaro 20.2 Nibia with no desktop environment, just the tty

```username: p5```
```passwd: 123```
The root password is the same as the user password

To use our algorithms please go to ~/projectbinaries

Here you will find two binaries and three datasets.
The three datasets are the same datasets as those used in the project report.
The two binaries each contain one of our two algorithms.

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
