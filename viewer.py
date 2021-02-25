import pyxel
import math
import time
import datetime 
import time
import socket
from time import sleep

ran = 0

def render():
	global ran;
	ran=ran+1;
	#print(ran)
	sleep(0.003)
	client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	client_socket.settimeout(1.0)
	message = b"@[polygon]{c:67,44|194,44|170,174|41,91;}\n@@@"
	#message = b"@[circle]{r:50;c:50,60;}\n@@@"
	
	addr = ("127.0.0.1", 6770)

	start = time.time()
	client_socket.sendto(message, addr)
	try:
		text = "";
		fulltext = "";
		i=1
		while "@@@" not in text:
			data, server = client_socket.recvfrom(1024)
			#print(text)
			
			text = data.decode();
			if "@@@" not in text:
				#print("\nReceived Part "+str(i)+"\n");
				fulltext += text;
			else:
				pass
				#print("\nReceived end Signal\n")
			end = time.time()
			elapsed = end - start
			i += 1
		i = 0
			#print(f'{data}')
		for kv in fulltext.split(","):
			pair = kv.strip("[").strip("]").split("&")
			
			try:
				x = int(pair[0])
				y = int(pair[1])
			except:
				pass
			pyxel.pset(x,y,10)
		

	except socket.timeout:
		print('REQUEST TIMED OUT')
	#points2 = [[10,56],[11,56],[12,56],[13,57],[14,57],[15,57],[16,57],[17,57],[18,57],[19,58],[20,58],[21,58],[22,58],[23,58],[24,58],[25,59],[26,59],[27,59],[28,59],[29,59],[30,59],[31,60],[32,60],[33,60],[34,60],[35,60],[36,61],[37,61],[38,61],[39,61],[40,61],[41,61],[42,62],[43,62],[44,62],[45,62],[46,62],[47,62],[48,63],[49,63],[50,63],[50,63],[49,64],[49,65],[48,66],[47,67],[47,68],[46,69],[45,70],[45,71],[44,72],[43,73],[43,74],[42,75],[41,76],[41,77],[40,78],[39,79],[39,80],[38,81],[37,82],[37,83],[36,84],[35,85],[35,86],[34,87],[33,88],[33,89],[32,90],[32,90],[31,89],[31,88],[30,87],[29,86],[29,85],[28,84],[27,83],[27,82],[26,81],[26,80],[25,79],[24,78],[24,77],[23,76],[22,75],[22,74],[21,73],[20,72],[20,71],[19,70],[18,69],[18,68],[17,67],[16,66],[16,65],[15,64],[15,63],[14,62],[13,61],[13,60],[12,59],[11,58],[11,57],[10,56],[10,56],[11,56],[12,56],[13,57],[14,57],[15,57],[16,57],[17,57],[18,57],[19,58],[20,58],[21,58],[22,58],[23,58],[24,58],[25,59],[26,59],[27,59],[28,59],[29,59],[30,59],[31,60],[32,60],[33,60],[34,60],[35,60],[36,61],[37,61],[38,61],[39,61],[40,61],[41,61],[42,62],[43,62],[44,62],[45,62],[46,62],[47,62],[48,63],[49,63],[50,63],[50,63],[49,64],[49,65],[48,66],[47,67],[47,68],[46,69],[45,70],[45,71],[44,72],[43,73],[43,74],[42,75],[41,76],[41,77],[40,78],[39,79],[39,80],[38,81],[37,82],[37,83],[36,84],[35,85],[35,86],[34,87],[33,88],[33,89],[32,90],[32,90],[31,89],[31,88],[30,87],[29,86],[29,85],[28,84],[27,83],[27,82],[26,81],[26,80],[25,79],[24,78],[24,77],[23,76],[22,75],[22,74],[21,73],[20,72],[20,71],[19,70],[18,69],[18,68],[17,67],[16,66],[16,65],[15,64],[15,63],[14,62],[13,61],[13,60],[12,59],[11,58],[11,57],[10,56]]
	
	#for i in points2:
	#	pyxel.pset(i[0],i[1],10)
		


	
def update():

	"""This function just maps the Q key to `pyxel.quit`,
	which works just like `sys.exit`."""

	if pyxel.btnp(pyxel.KEY_Q): pyxel.quit()

def draw():

	"""This function clears the screen and draws a single
	pixel, whenever the buffer needs updating. Note that
	colors are specified as palette indexes (0-15)."""

	pyxel.cls(0)			# clear screen (color)


	render()
	pyxel.mouse(True)


try:
	pyxel.init(250, 250, caption='Render Receiver')		# initilize gui (width, height)
	pyxel.run(update, draw) 

finally:
    print(f"Ran {ran} times!\n\n\n")





"""

from tkinter import*

root = Tk()

class GUI(Canvas):
	'''inherits Canvas class (all Canvas methodes, attributes will be accessible)
	   You can add your customized methods here.
	'''
	def __init__(self,master,*args,**kwargs):
		Canvas.__init__(self, master=master, *args, **kwargs)
		self.master.title("Receiver")

polygon = GUI(root)

#polygon.create_polygon([arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8],	 outline='red', 
#			fill='gray', width=2)


polygon.pack()
root.mainloop()
"""