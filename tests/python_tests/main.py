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
	#poly(points)

	points2 = [[67,44],[68,44],[69,44],[70,44],[71,44],[72,44],[73,44],[74,44],[75,44],[76,44],[77,44],[78,44],[79,44],[80,44],[81,44],[82,44],[83,44],[84,44],[85,44],[86,44],[87,44],[88,44],[89,44],[90,44],[91,44],[92,44],[93,44],[94,44],[95,44],[96,44],[97,44],[98,44],[99,44],[100,44],[101,44],[102,44],[103,44],[104,44],[105,44],[106,44],[107,44],[108,44],[109,44],[110,44],[111,44],[112,44],[113,44],[114,44],[115,44],[116,44],[117,44],[118,44],[119,44],[120,44],[121,44],[122,44],[123,44],[124,44],[125,44],[126,44],[127,44],[128,44],[129,44],[130,44],[131,44],[132,44],[133,44],[134,44],[135,44],[136,44],[137,44],[138,44],[139,44],[140,44],[141,44],[142,44],[143,44],[144,44],[145,44],[146,44],[147,44],[148,44],[149,44],[150,44],[151,44],[152,44],[153,44],[154,44],[155,44],[156,44],[157,44],[158,44],[159,44],[160,44],[161,44],[162,44],[163,44],[164,44],[165,44],[166,44],[167,44],[168,44],[169,44],[170,44],[171,44],[172,44],[173,44],[174,44],[175,44],[176,44],[177,44],[178,44],[179,44],[180,44],[181,44],[182,44],[183,44],[184,44],[185,44],[186,44],[187,44],[188,44],[189,44],[190,44],[191,44],[192,44],[193,44],[194,44],[194,44],[193,44],[192,45],[191,45],[190,45],[189,46],[188,46],[187,46],[186,47],[185,47],[184,47],[183,48],[182,48],[181,48],[180,49],[179,49],[178,49],[177,50],[176,50],[175,50],[174,51],[173,51],[172,51],[171,52],[170,52],[169,52],[168,53],[167,53],[166,53],[165,54],[164,54],[163,54],[162,55],[161,55],[160,55],[159,56],[158,56],[157,56],[156,57],[155,57],[154,57],[153,58],[152,58],[151,58],[150,59],[149,59],[148,59],[147,60],[146,60],[145,60],[144,61],[143,61],[142,61],[141,62],[140,62],[139,62],[138,63],[137,63],[136,63],[135,64],[134,64],[133,64],[132,65],[131,65],[130,65],[129,66],[128,66],[127,66],[126,67],[125,67],[124,67],[123,68],[122,68],[121,68],[120,69],[119,69],[118,69],[117,70],[116,70],[115,70],[114,71],[113,71],[112,71],[111,72],[110,72],[109,72],[108,73],[107,73],[106,73],[105,74],[104,74],[103,74],[102,75],[101,75],[100,75],[99,76],[98,76],[97,76],[96,77],[95,77],[94,77],[93,78],[92,78],[91,78],[90,79],[89,79],[88,79],[87,80],[86,80],[85,80],[84,81],[83,81],[82,81],[81,82],[80,82],[79,82],[78,83],[77,83],[76,83],[75,84],[74,84],[73,84],[72,85],[71,85],[70,85],[69,86],[68,86],[67,86],[66,87],[65,87],[64,87],[63,88],[62,88],[61,88],[60,89],[59,89],[58,89],[57,90],[56,90],[55,90],[54,91],[53,91],[52,91],[51,92],[50,92],[49,92],[48,93],[47,93],[46,93],[45,94],[44,94],[43,94],[42,95],[41,95],[41,95],[42,96],[43,96],[44,97],[45,97],[46,98],[47,99],[48,99],[49,100],[50,101],[51,101],[52,102],[53,102],[54,103],[55,104],[56,104],[57,105],[58,105],[59,106],[60,107],[61,107],[62,108],[63,108],[64,109],[65,110],[66,110],[67,111],[68,112],[69,112],[70,113],[71,113],[72,114],[73,115],[74,115],[75,116],[76,116],[77,117],[78,118],[79,118],[80,119],[81,119],[82,120],[83,121],[84,121],[85,122],[86,123],[87,123],[88,124],[89,124],[90,125],[91,126],[92,126],[93,127],[94,127],[95,128],[96,129],[97,129],[98,130],[99,131],[100,131],[101,132],[102,132],[103,133],[104,134],[105,134],[106,135],[107,135],[108,136],[109,137],[110,137],[111,138],[112,138],[113,139],[114,140],[115,140],[116,141],[117,142],[118,142],[119,143],[120,143],[121,144],[122,145],[123,145],[124,146],[125,146],[126,147],[127,148],[128,148],[129,149],[130,150],[131,150],[132,151],[133,151],[134,152],[135,153],[136,153],[137,154],[138,154],[139,155],[140,156],[141,156],[142,157],[143,157],[144,158],[145,159],[146,159],[147,160],[148,161],[149,161],[150,162],[151,162],[152,163],[153,164],[154,164],[155,165],[156,165],[157,166],[158,167],[159,167],[160,168],[161,168],[162,169],[163,170],[164,170],[165,171],[166,172],[167,172],[168,173],[169,173],[170,174],[170,174],[169,173],[168,172],[168,171],[167,170],[166,169],[165,168],[164,167],[164,166],[163,165],[162,164],[161,163],[160,162],[160,161],[159,160],[158,159],[157,158],[157,157],[156,156],[155,155],[154,154],[153,153],[153,152],[152,151],[151,150],[150,149],[149,148],[149,147],[148,146],[147,145],[146,144],[145,143],[145,142],[144,141],[143,140],[142,139],[141,138],[141,137],[140,136],[139,135],[138,134],[138,133],[137,132],[136,131],[135,130],[134,129],[134,128],[133,127],[132,126],[131,125],[130,124],[130,123],[129,122],[128,121],[127,120],[126,119],[126,118],[125,117],[124,116],[123,115],[122,114],[122,113],[121,112],[120,111],[119,110],[118,109],[118,108],[117,107],[116,106],[115,105],[115,104],[114,103],[113,102],[112,101],[111,100],[111,99],[110,98],[109,97],[108,96],[107,95],[107,94],[106,93],[105,92],[104,91],[103,90],[103,89],[102,88],[101,87],[100,86],[99,85],[99,84],[98,83],[97,82],[96,81],[96,80],[95,79],[94,78],[93,77],[92,76],[92,75],[91,74],[90,73],[89,72],[88,71],[88,70],[87,69],[86,68],[85,67],[84,66],[84,65],[83,64],[82,63],[81,62],[80,61],[80,60],[79,59],[78,58],[77,57],[77,56],[76,55],[75,54],[74,53],[73,52],[73,51],[72,50],[71,49],[70,48],[69,47],[69,46],[68,45],[67,44]]
	
	for i in points2:
		pyxel.pset(i[0],i[1],10)
		




	
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