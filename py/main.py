import openroute
from geocaching import geocaching

def __main__():
  print("This is main")
  results = geocaching.search(57.0,9.0)
  print(results)
  openroute.importMatrix()

if __name__ == "__main__":
   __main__() 
