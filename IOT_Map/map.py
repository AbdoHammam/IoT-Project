import socket
import webbrowser

buffer_size = 1024

ip, port_number = "192.168.8.7", 5050
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((ip, port_number))
s.listen(1)

lstOfLocations = {}
while 1:
    conn, addr = s.accept()
    print ('Connection address:', addr)
    while 1:
        data = conn.recv(buffer_size)
        print ("received data:", data)
        a, b, c = parseJson(data)
        lstOfLocations[a]=(b,c)

#print(lstOfLocations)
centerLng = 31.2100348
centerLat=30.0307949

f = open('map.html','w')

message = """
<html>
<head>
<script src="https://developers.google.com/maps/documentation/javascript/examples/markerclusterer/markerclusterer.js">
</script>

<script type="text/javascript">
var locations = [
    {}
]
      
function initMap() {{
        var map = new google.maps.Map(document.getElementById('map'), {{
          zoom: 18,
          center: {}
        }});

        var labels = "{}";

        var markers = locations.map(function(location, i) {{
          return new google.maps.Marker({{
            position: location,
            label: labels[i % labels.length]
          }});
        }});

        var markerCluster = new MarkerClusterer(map, markers,
            {{imagePath: 'https://developers.google.com/maps/documentation/javascript/examples/markerclusterer/m' }});
 
 }}

</script>
<style>
      /* Always set the map height explicitly to define the size of the div
       * element that contains the map. */
      #map {{
        height: 100%;
      }}
      /* Optional: Makes the sample page fill the window. */
      html, body {{
        height: 100%;
        margin: 0;
        padding: 0;
      }}
</style>

</head>
<body>
<div id="map"></div>

<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCAzpwk6zkm2iJobeGM7XfPbLyuPha5T3c&callback=initMap"  async defer></script>

</body>
</html>
"""

locationsToDraw = ""
oneLocation = "{{lat:{}, lng: {}}}"
x=0
while(x<len(lstOfLocations)):
    if(x == len(lstOfLocations)-1):
        locationsToDraw = locationsToDraw+oneLocation
    else:
        locationsToDraw = locationsToDraw+oneLocation+","
    x+=1

#print(locationsToDraw)
labels = ""
lst = []
for i,j in lstOfLocations.items():
    lst += [j[0]] + [j[1]]
    labels += i
locationsToDraw = locationsToDraw.format(*lst)
centerLocation="{{lat:{}, lng: {}}}"
centerLocation = centerLocation.format(centerLat,centerLng)

message = message.format(locationsToDraw,centerLocation,labels)
f.write(message)
f.close()

webbrowser.open_new_tab('map.html')

def parseJson(json):
    json = str(json).split('\n')
    json = json[0]
    x, y, z = str(json).split(',')
    x = int(x[x.find(':')+1:])
    y = float(y[y.find(':')+1:])
    z = float(z[z.find(':')+1:-2])
    return  x, y, z


