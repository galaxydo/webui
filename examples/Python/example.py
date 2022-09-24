# WebUI Library 2.0.0
#
# http://webui.me
# https://github.com/alifcommunity/webui
#
# Licensed under GNU General Public License v3.0.
# Copyright (C)2022 Hassan DRAGA <https://github.com/hassandraga>.

# [!] IMPORTANT
# Please build a dynamic version of WebUI library using
# your favorite C compiler, then copy file 'webui-2-x64'
# into this folder.

import webui # Importing 'webui.py' file

# HTML
my_html = """
<!DOCTYPE html>
<html>
	<head>
		<title>WebUI 2.0 Example</title>
		<style>
			body{
				color: white;
				background: #0F2027;
				background: -webkit-linear-gradient(to right, #2C5364, #203A43, #0F2027);
				background: linear-gradient(to right, #2C5364, #203A43, #0F2027);
				text-align:center;
				font-size: 18px;
				font-family: sans-serif;
			}
		</style>
	</head>
	<body>
		<h1>WebUI 2.0 Example</h1>
		<br>
		<input type="password" id="MyInput">
		<br><br>
		<button id="MyButton1">Check Password</button> - <button id="MyButton2">Exit</button>
	</body>
</html>
"""

# a sample function to be called
# when a specific button has clicked
def check_the_password(e : webui.event):
	print('Element_id: ' + str(e.element_id))
	print('Window_id: ' + str(e.window_id))
	print('Element_name: ' + e.element_name.decode('utf-8'))
	print('[!] The next coming version will include running JavaScript from Python.')

def close_the_application(e : webui.event):
	webui.exit()

# Create a window object
MyWindow = webui.window()

# Bind am HTML element ID with a python function
MyWindow.bind('MyButton1', check_the_password)
MyWindow.bind('MyButton2', close_the_application)

# Show the window
MyWindow.show(my_html)

# Wait until all windows are closed
webui.loop()

print('Bye.')