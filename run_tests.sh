#!/bin/bash

#================================
# Numero de ejercicio
numEjercicio=4
#================================

g++ -std=c++11 -o "ejercicio$numEjercicio.exe" "ejercicio$numEjercicio.cpp"

# Directorio donde se encuentra el ejecutable (si se esta parado en el dejar como ./)
exe_dir="./"

# Nombre del ejecutable. Modificar por el .exe a probar
exe_name="ejercicio$numEjercicio.exe"

# Directorio donde se encuentran los archivos de prueba (a partir del dir donde esta el exe)
test_dir="ejercicio$numEjercicio-tests/"

# Lista de archivos de entrada en el directorio de pruebas
input_files=$(ls "$test_dir"*.in.txt)

# Loop a través de los archivos de entrada
for input_file in $input_files; do
    # Obtener el nombre base del archivo de entrada (sin extensión)
    base_name=$(basename "$input_file" .in.txt)

    # Ejecutar el programa con redirección de entrada y salida
    "$exe_dir$exe_name" < "$input_file" > "$test_dir$base_name.myout.txt"

    # Comparar la salida generada con la salida esperada utilizando diff con --strip-trailing-cr
    diff --strip-trailing-cr "$test_dir$base_name.out.txt" "$test_dir$base_name.myout.txt" > "$test_dir$base_name.diff.txt"

    # Verificar si la comparación fue exitosa
    if [ -s "$test_dir$base_name.diff.txt" ]; then
        echo "Resultado para $base_name: ERROR"
    else
        echo "Resultado para $base_name: OK"
    fi
done
