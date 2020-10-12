import requests
import json
import sys

# returns a dictionary containing all the jsonData
# reverse order of coordinates when sending to openrouteApi
# the coordinates parameter should either be a multidimensional array or list of the points wanted
def importMatrix(coordinates):
    url = "https://api.openrouteservice.org/v2/matrix/foot-walking"
    GeoCoordinates = {}
    GeoCoordinates["geoPoints"] = []
    locations = ""
    index = 1
    # 50 is magic number, aka the limit for openrouteApi
    for each in orderedData["points"][:50]:
      if(index == 1):
        locations += "[" + str(each["longtitude"]) + "," + str(each["latitude"]) + "]"
        GeoCoordinates["geoPoints"].append({'id': each["id"], 'longtitude': each["longtitude"], 'latitude': each['latitude']})
        index += 1
      else:
        locations += ",[" + str(each["longtitude"]) + "," + str(each["latitude"]) + "]" 
        GeoCoordinates["geoPoints"].append({'id': each["id"], 'longtitude': each["longtitude"], 'latitude': each['latitude']})
    
    payload = "{\"locations\":[" + locations + "]}"
    headers = {
      'Authorization': '5b3ce3597851110001cf624865c2d3b02c2c4f43b9d877849d66b13c',
      'Content-Type': 'application/json'
    }

    response = requests.request("POST", url, headers=headers, data = payload)
    jsonObj = json.loads(response.text.encode('utf8'))
    jsonObj["geoPoints"] = GeoCoordinates["geoPoints"]

    return jsonObj

def getCoordinates(inputFile):
    coordinateDict = {}
    coordinateDict["points"] = []
    parsedJson = json.load(inputFile)
    for each in parsedJson["results"]:
      if(each["premiumOnly"] == False):
        coordinateDict["points"].append({ 'id': each["id"],
                                         'latitude': each["postedCoordinates"]["latitude"],
                                         'longtitude': each["postedCoordinates"]["longitude"]})

    return coordinateDict

    
if __name__ == "__main__":
    with open(sys.argv[1]) as myFile:
      orderedData = getCoordinates(myFile)

    openRouteDistances = importMatrix(orderedData)
    with open('openroutedata.json', 'w') as outfile:
        json.dump(openRouteDistances, outfile)
    



