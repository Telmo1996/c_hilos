import json
import sys
from PIL import Image
from numpy import asarray


if __name__ == '__main__':
	if len(sys.argv) != 2:
		print("Argumentos incorrectos")
		exit()
	
	imageName = sys.argv[1]
	print(imageName)

	image = Image.open(imageName)
	width, height = image.size
	img = asarray(image)
	data = img.copy()

	for i in range(0, height):
		for j in range(0, width):
			print(data[i][j])
