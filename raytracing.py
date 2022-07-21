WIDTH = 256
HEIGHT = 256

with open("render.ppm", "w") as file:
	file.write("P3\n") # "P3" means this is a RGB color image in ASCII
	file.write(f"{WIDTH} {HEIGHT}\n")
	file.write("255\n") # Maximum value for each color channel
	for j in range(HEIGHT):
		for i in range(WIDTH):
			file.write(f"{int((j/WIDTH) * 255)} 0 0\n")
