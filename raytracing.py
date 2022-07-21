IMAGE_WIDTH = 256
IMAGE_HEIGHT = 256

VIEWPORT_WIDTH = 1.0
VIEWPORT_HEIGHT = 1.0

# Camera coordinates in viewport space
CAM_X = 0.5
CAM_Y = 0.5
CAM_Z = -1.0

class Vec3:
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
	def length(self):
		return (self.x*self.x + self.y*self.y + self.z*self.z) ** .5
	def normalize(self):
		l = self.length()
		if abs(l) < .00001:
			return
		self.x /= l
		self.y /= l
		self.z /= l
	def dot(self, other):
		return self.x*other.x + self.y*other.y + self.z*other.z
	def __sub__(self, other):
		return Vec3(self.x - other.x, self.y - other.y, self.z - other.z)
	def __add__(self, other):
		return Vec3(self.x + other.x, self.y + other.y, self.z + other.z)
	def __mul__(self, other):
		if isinstance(other, float):
			return Vec3(self.x * other, self.y * other, self.z * other)
		raise NotImplementedError

def ray_sphere_intersection(ro, rd, sphere_center, sphere_radius):
	L = sphere_center - ro
	tca = L.dot(rd)
	if tca < 0: return None
	d = (L.dot(L) - tca*tca) ** .5
	if d < 0: return None
	if d > sphere_radius: return None # Ray over shoots sphere
	thc = (sphere_radius*sphere_radius - d*d) ** .5
	t0 = tca - thc
	#t1 = tca + thc
	return ro + rd * t0


ray_origin = Vec3(CAM_X, CAM_Y, CAM_Z)
with open("render.ppm", "w") as file:
	file.write("P3\n") # "P3" means this is a RGB color image in ASCII
	file.write(f"{IMAGE_WIDTH} {IMAGE_HEIGHT}\n")
	file.write("255\n") # Maximum value for each color channel
	for Y in range(IMAGE_HEIGHT):
		for X in range(IMAGE_WIDTH):
			pixel_position = Vec3((X / IMAGE_WIDTH) * VIEWPORT_WIDTH, (Y / IMAGE_HEIGHT) * VIEWPORT_HEIGHT, 0.0)
			ray_direction = pixel_position - ray_origin
			ray_direction.normalize()
			b = ray_sphere_intersection(ray_origin, ray_direction, Vec3(.5, .5, 10), 1)
			file.write(f"{255 if b else 0} 0 0\n")
