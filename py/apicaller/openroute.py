import requests
import json
import sys
import pprint
import argparse


class OpenrouteApi:
    """ 
    A wrapper for the openrouteservice.org api.
    Uses dataset from elsewhere to find distances between each location.
    Returns a matrix in the format of "one-to-many"
    """
    def importMatrix(self, orderedData):
        """
        returns a dictionary containing all the jsonData
        reverse order of coordinates when sending to openrouteApi
        Furthermore, the returned distance matrix has metrics km for distance, and works as a one to many,
        with the source parameter being incremented after each iteration
        """
        url = "https://api.openrouteservice.org/v2/matrix/foot-walking"
        res = []
        GeoCoordinates = {}
        GeoCoordinates["geoPoints"] = []

        locations = ""
        index = 1
        # 50 is magic number, aka the limit for openrouteApi
        for each in orderedData["points"][:30]:
          if(index == 1):
            locations += "[" + str(each["longtitude"]) + "," + str(each["latitude"]) + "]"
            GeoCoordinates["geoPoints"].append({'id': each["id"], 'longtitude': each["longtitude"], 'latitude': each['latitude']})
            index += 1
          else:
            locations += ",[" + str(each["longtitude"]) + "," + str(each["latitude"]) + "]" 
            GeoCoordinates["geoPoints"].append({'id': each["id"], 'longtitude': each["longtitude"], 'latitude': each['latitude']})
        
        headers = {
        'Authorization': '5b3ce3597851110001cf624865c2d3b02c2c4f43b9d877849d66b13c',
        'Content-Type': 'application/json'
        }

        for count, each in enumerate(GeoCoordinates["geoPoints"]):
            payload = "{\"locations\":[" + locations + "],\"metrics\":[\"distance\"],\"sources\":["+ str(count) + "],\"units\":\"km\"}"
            response = requests.request("POST", url, headers=headers, data = payload)
            if(response.status_code != 200):
                print(response.status_code, response.reason)
                print(response.text)
                break
            jsonObj = json.loads(response.text.encode('utf8'))
            jsonObj["geoPoints"] = each
            res.append(jsonObj)
            print("progress: " + str(count+1) + " of: " + str(len(GeoCoordinates["geoPoints"])))
        
        return res

    def getCoordinates(self, inputFile):
        """
        Essentially a Json parser to remove all unwanted data and return only coordinates and id.
        """
        coordinateDict = {}
        coordinateDict["points"] = []
        parsedJson = json.load(inputFile)
        for each in parsedJson["results"]:
          if(each["premiumOnly"] == False):
            coordinateDict["points"].append({ 'id': each["id"],
                                             'latitude': each["postedCoordinates"]["latitude"],
                                             'longtitude': each["postedCoordinates"]["longitude"]})

        return coordinateDict

def __main__(args):
    parser = argparse.ArgumentParser(description="Usage openroute [options] filepath")
    parser.add_argument('-o', '--outfile', default='openroute.json',
                        help="specify the name of the outputfile. The format of the output file will be Json, thus it is smart to add that file extension")
    parser.add_argument('inputfile')
    args = parser.parse_args(args)
    openroute = OpenrouteApi()

    with open(args.inputfile) as myFile:
      orderedData = openroute.getCoordinates(myFile)

    openRouteDistances = openroute.importMatrix(orderedData)
    print("Call to api finished, exporting to " + args.outfile)
    with open(args.outfile, 'w') as outfile:
        json.dump(openRouteDistances, outfile)

if __name__ == "__main__":
    import sys
    __main__(sys.argv[1:])
