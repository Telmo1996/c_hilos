import json
from json import JSONEncoder
import sys
from PIL import Image
import numpy
from numpy import asarray


class NumpyArrayEncoder(JSONEncoder):
    def default(self, obj):
        if isinstance(obj, numpy.ndarray):
            return obj.tolist()
        return JSONEncoder.default(self, obj)


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

	#for i in range(0, height):
	#	for j in range(0, width):
	#		print(data[i][j])

	miJson = {"info": {"width": width, "height": height},
			"data": data}
	encodedMiJson = json.dumps(miJson, cls=NumpyArrayEncoder)
	with open("out.json", 'w') as outfile:
		json.dump(encodedMiJson, outfile)

