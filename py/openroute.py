import requests


def importMatrix():
  url = "https://api.openrouteservice.org/v2/matrix/driving-car"

  payload = "{\"locations\":[[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281],[115.663757,38.106467]]}"
  headers = {
    'Authorization': '5b3ce3597851110001cf624865c2d3b02c2c4f43b9d877849d66b13c',
    'Content-Type': 'application/json'
  }

  response = requests.request("POST", url, headers=headers, data = payload)

  print(response.text.encode('utf8'))

