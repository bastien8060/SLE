import pyxel
import math
import time
import datetime 

now = datetime.datetime.now()
start = now + datetime.timedelta(minutes = 1)
nran = 0

def sort(p,handler=[]):
	max = len(p) - 1
	index = 1
	if handler:
		while not index > max:
			result = handler(p[index - 1], p[index])
			if result < 0 or result == 0 :
				index += 1
			else:
				p[index - 1], p[index] = p[index], p[index -1]
				index = 1
	else:
		while not index > max:
			if p[index - 1] < p[index] or p[index - 1] == p[index] :
				index + 1
			else:
				p[index - 1], p[index] = p[index], p[index -1]
				index = 1
	return p

def reducer(handler,iter,initial=0):
		total = initial
		for i in iter:
			total = handler(total, i)
		return total

def _ROUND(a):
  return int(a + 0.5)

def line(x1,y1,x2,y2):
	x,y = x1,y1
	length = (x2-x1) if (x2-x1) > (y2-y1) else (y2-y1)
	dx = (x2-x1)/float(length)
	dy = (y2-y1)/float(length)
	pyxel.pset(_ROUND(x),_ROUND(y),10)
	triggered = False
	for i in range(length):
		x += dx
		y += dy
		triggered = True
		pyxel.pset(_ROUND(x),_ROUND(y),10)
	if not triggered:
		#print("No line #printed")
		linehoriz(x1,y1,x2,y2)
	#print('lines:',x1,y1," -> ",x2,y2)

def _fpart(x):
	return x - int(x)
 
def _rfpart(x):
	return 1 - _fpart(x)

def linehoriz(x1,y1,x2,y2, color=(255, 255, 0)):
	"""Draws an anti-aliased line in img from p1 to p2 with the given color."""
	p1 = x1, y1 
	p2 = x2, y2
	dx, dy = x2-x1, y2-y1
	steep = abs(dx) < abs(dy)
	p = lambda px, py: ((px,py), (py,px))[steep]
 
	if steep:
		x1, y1, x2, y2, dx, dy = y1, x1, y2, x2, dy, dx
	if x2 < x1:
		x1, x2, y1, y2 = x2, x1, y2, y1
 
	grad = dy/dx
	intery = y1 + _rfpart(x1) * grad
	def draw_endpoint(pt):
		x, y = pt
		xend = round(x)
		yend = y + grad * (xend - x)
		xgap = _rfpart(x + 0.5)
		px, py = int(xend), int(yend)
		pyxel.pset(px, py, 10)# color, _rfpart(yend) * xgap)
		pyxel.pset(px, py+1, 10)#, _fpart(yend) * xgap)
		return px
 
	xstart = draw_endpoint(p(*p1)) + 1
	xend = draw_endpoint(p(*p2))
	triggered = False
	for x in range(xstart, xend):
		triggered = True
		y = int(intery)
		pyxel.pset(x, y, 10)#, _rfpart(intery))
		pyxel.pset(x, y+1, 10)#, _fpart(intery))
		intery += grad
	if not triggered:
		#print("Still not working")
		linehoriz2(x1,y1,x2,y2)
 

def linehoriz2(x1,y1,x2,y2): 

	m_new = 2 * (y2 - y1) 
	slope_error_new = m_new - (x2 - x1)
	points = [] 

	y=y1 
	for x in range(x1,x2+1): 
		points.append((x,y))

		# Add slope to increment angle formed 
		slope_error_new = slope_error_new + m_new 
		# Slope error reached limit, time to 
		# increment y and update slope error. 
		if (slope_error_new >= 0): 
			y += 1
			slope_error_new = slope_error_new - 2 * (x2 - x1) 
	trigger = False
	for i in points:
		pyxel.pset(i[0],i[1],10)
		trigger = True
	if not trigger:
		#print("Didn't work")
		line(x1,y1,x2,y2)
	else:
		#print('lines:',x1,y1," -> ",x2,y2)
		pass




def circle(radius, midpoint=(0,0)):
	"Bresenham complete circle algorithm in Python"
	# init vars
	offset=[]
	offset.append(midpoint[0] * 2)
	offset.append(midpoint[1] * 2)
	switch = 3 - (2 * radius)
	points = set()
	x = 0
	y = radius
	# first quarter/octant starts clockwise at 12 o'clock
	while x <= y:
		# first quarter first octant
		points.add((x+offset[0],-y+offset[1]))
		# first quarter 2nd octant
		points.add((y+offset[0],-x+offset[1]))
		# second quarter 3rd octant
		points.add((y+offset[0],x+offset[1]))
		# second quarter 4.octant
		points.add((x+offset[0],y+offset[1]))
		# third quarter 5.octant
		points.add((-x+offset[0],y+offset[1]))		
		# third quarter 6.octant
		points.add((-y+offset[0],x+offset[1]))
		# fourth quarter 7.octant
		points.add((-y+offset[0],-x+offset[1]))
		# fourth quarter 8.octant
		points.add((-x+offset[0],-y+offset[1]))
		if switch < 0:
			switch = switch + (4 * x) + 6
		else:
			switch = switch + (4 * (x - y)) + 10
			y = y - 1
		x = x + 1
		for i in points:
			pyxel.pset(i[0]/2,i[1]/2, 10) 

def poly(points):

	def squarePolar(point,centre):
		return [math.atan2(point[1]-centre[1],point[0]-centre[0]), (point[0]-centre[0])**2 + (point[1]-centre[1])**2]

	def polySort(points): #main algorithm
		# Get "centre of mass"
		centre = [reducer(lambda sum, p : sum+p[0],points)/len(points),reducer(lambda sum, p : sum+p[1],points)/len(points)] #get center of mass
		# Sort by polar angle and distance, centered at this centre of mass.
		for point in points:
			for x in squarePolar(point,centre):
				point.append(x)

		points = sort(points,handler=lambda a,b : a[2] - b[2] or a[3] - b[3])
		#  Throw away the temporary polar coordinates
		for point in points:
			point = point[:len(point)-2]
		return points


	def draw(points):
		todraw = []
		if (not points):
			return
		for i in points:
			x, y = i[0], i[1]
			todraw.append((x,y))
		#it =  iter(points)
		#for i,i2 in zip(it,it):
		for index in range(len(points)):
			if i != len(points):
				indexlast = index
				i = points[index - 1]
				i2 = points[index]
				x1,y1 = i[0], i[1]
				x2,y2 = i2[0], i2[1]
				trace = line(x1, y1, x2, y2)
				

		#print("custom one:")
		i = points[indexlast]
		i2 = points[0]
		x1,y1 = i[0], i[1]
		x2,y2 = i2[0], i2[1]
		trace = line(x1, y1, x2, y2)
		#print('lines:',x1,y1," -> ",x2,y2)
			
		return todraw

	#print("\n\n")
	for i in draw(polySort(points)):
	#for i in draw(points):
		#print("\n",i)
		pyxel.pset(i[0],i[1],10)



	i = """		// Main algorithm:
				function polySort(points) {
					// Get "centre of mass"
					let centre = [points.reduce((sum, p) => sum + p[0], 0) / points.length,
								  points.reduce((sum, p) => sum + p[1], 0) / points.length];
			
					// Sort by polar angle and distance, centered at this centre of mass.
					for (let point of points) point.push(...squaredPolar(point, centre));
					points.sort((a,b) => a[2] - b[2] || a[3] - b[3]);
					// Throw away the temporary polar coordinates
					for (let point of points) point.length -= 2; 
				}
			
				let points = [];
			
				// I/O management
			
				let canvas = document.querySelector("canvas");
				let ctx = canvas.getContext("2d");
			
				function draw(points) {
					ctx.clearRect(0, 0, canvas.width, canvas.height);
					if (!points.length) return;
					for (let [x, y] of points) {
						ctx.beginPath();
						ctx.arc(x, y, 3, 0, 2 * Math.PI, true);
						ctx.fill();
					}
					ctx.beginPath();
					ctx.moveTo(...points[0]);
					for (let [x, y] of points.slice(1)) ctx.lineTo(x, y);
					ctx.closePath();
					ctx.stroke();
				}
			
				canvas.onclick = function (e) {
					let x = e.clientX - this.offsetLeft;
					let y = e.clientY - this.offsetTop;
					let match = points.findIndex(([x0, y0]) => Math.abs(x0-x) + Math.abs(y0-y) <= 6);
					if (match < 0) points.push([x, y]);
					else points.splice(match, 1); // delete point when user clicks near it.
					polySort(points);
					draw(points);
				};"""
	
	#pyxel.pset(i[0]/2,i[1]/2, 10)



def render():
	global time, now, nran
	if nran == 0:
		print("now")
	nran += 1
	#print(f"ran: {nran}")

	circle(radius=40,midpoint=(125,125))
	circle(radius=72,midpoint=(62.5,62.5))
	circle(radius=10,midpoint=(187.5,62.5))
	circle(radius=90,midpoint=(187.5,187.5))
	circle(radius=30,midpoint=(62.5,187.5))
	points = [[67, 44], [194, 44], [41, 95], [170, 174]]
	poly(points)


	

		




	
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
except:
	print(f"ran: {nran}")







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