#!/bin/sh
if [ -z "$1" ]; then
	echo "Dame imagen"
else
	echo "Analizando imagen."
	python3 py/imageToJson.py $1
	echo "Imagen analizada."
	echo "Comenzando calculo de hilos:"
	./c/c_hilos
	echo "Done."
	rm out.json
fi
