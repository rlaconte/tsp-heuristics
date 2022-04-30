#!/bin/bash
#===========================================================#
# Resultado: parsea todos los archivos de in_dir y          #
# guarda el resultado en un archivos con los mismos nombres #
# en out_dir.                                               #
#===========================================================#

shopt -s extglob
mkdir data
# Parseo todos los .tsp de este directorio
in_dir="../download_data/temp/"
# Los mando a este directorio
out_dir="../data/dataGenerada/euc/"

for file in ${in_dir}*.tsp;
do
	#echo $file
	name=$(basename "${file}")
	#echo ${out_dir}${name} 
	# Cambiar por con_espejadas_unos si se quiere tanto arista (i,j) como (j,i)
	python3 ../scripts/parser_instancias_sin_espejadas_ceros.py ${file} > ${out_dir}${name} 
done
