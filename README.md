+ Para descargar las instancias de la cátedra y dejarlas lista para uso del parser se puede utilizar el script de bash "0_descargar_instancias_de_prueba.sh". Si ya se tiene descargadas las instancias y se desea utilizarlas en la ejecución del resto del código provisto, crear una carpeta "download_data" en la raíz del proyecto y comentar la línea 9 del bash ($python3 ./scripts/descargar_instancias.py)

+ Para obtener las instancias de la cátedra en el formato aceptado por el código del TP, colocar las instancias a convertir en la carpeta "download_data" en la raíz o ejecutar el bash "0_descargar_instancias_de_prueba.sh" y luego ejecutar el bash "1_parsear_instancias.sh".

+ El bash script "2_parsear_instancias_euclidianas_propias.sh" sólo funciona correctamente si es ejecutado desde la carpeta ./notebooks, ya que fue creado para ser utilizado desde las jupyter notebooks incluidas con el código. El código del TP lo llama para el generador de instancias euclideas.

+ Se incluye un Makefile en "./src" con el que compilar el código del TP. Ejecutarlo con "./ejec" sin más parámetros devuelve la ayuda del código.

+ Se incluyen con el código varios generadores de instancias aleatorias con distintas características. Una vez compilado el TP, "./ejec Random" sin más parámetros devuelve la ayuda de los generadores de instancias.