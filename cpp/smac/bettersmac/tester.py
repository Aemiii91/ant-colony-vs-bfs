from IStrongwrapper import IAcoWrapper as acow

if __name__ == '__main__':
    cmd = './routeplanner aco --data "berlin.json" --iterations 50000 --progress2 --time 10 '
    x = [1,29,0.05,100]
    print(acow(cmd,x,10))
