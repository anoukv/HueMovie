import os
import urllib2, json
from time import sleep

# convert RGB to XY
def convertToXY(red, green, blue):
	
	# Gamma correction
	if red > 0.04045:
		red = ((red + 0.055) / (1.0 + 0.055)) ** 2.4
	else:
		red = red / 12.92

	if green > 0.04045:
		green = ((green + 0.055) / (1.0 + 0.055))** 2.4
	else: 
		green = green / 12.92

	if blue > 0.04045:
		blue = ((blue + 0.055) / (1.0 + 0.055)) **  2.4 
	else: 
		blue = blue / 12.92

	# Wide RGB D65 conversion
	X = red * 0.649926 + green * 0.103455 + blue * 0.197109
	Y = red * 0.234327 + green * 0.743075 + blue * 0.022598
	Z = green * 0.053077 + blue * 1.035763;

	# Calculate the xy values from the XYZ values
	x = X / (X + Y + Z); 
	y = Y / (X + Y + Z);
	
	# Use the Y value of XYZ as brightness The Y value indicates the brightness of the converted color.
	return x, y, Y

if __name__ == "__main__":
	
	# get IP address of the bridge
	opener = urllib2.build_opener(urllib2.HTTPHandler)
	request = urllib2.Request('	https://www.meethue.com/api/nupnp')
	url = opener.open(request)
	response = json.loads(url.read())
	ip = response[0]['internalipaddress']
	
	# set the username and the light to be adjusted
	# TODO generalize for other users
	username = 'anoukvisser'
	
	# set the light and the brightness
	light = '2'
	bri = '255'

	# create the url for request
	urlForRequest = 'http://' + ip + '/api/' + username + '/lights/' + light + '/state' 

	while True:
		# take a screenshot
		# -x is to make it silent
		os.system("screencapture -x screen.png")

		# call the c++ main to write RGB to output.txt
		os.system("./main screen.png > output.txt")

		# remove the screenshot
		os.system("rm screen.png")

		# open the output.txt file
		f = open("output.txt", 'r')

		# take out the \n, split on spaces and convert to float (and normalize, i.e. divide by 255)
		colors = map(lambda x: float(x) / float(255), f.readline().replace("\n", "").split(" "))
		
		# if the color is almost black
		if colors[2] < 0.02 and colors[1] < 0.02 and colors[0] < 0.02:
			# turn the light off.
			data = '{"bri":1}'
		else:
			# convert the colors
			x, y, Y = convertToXY(colors[2], colors[1], colors[0])
			# set the data
			data = '{"on":true, "bri":'+bri+', "xy":'+str([x, y])+', "transitiontime":3}'
		
		# create the PUT request
		request = urllib2.Request(urlForRequest, data=data)
		request.get_method = lambda: 'PUT'

		# open the request
		url = opener.open(request)
