# Compilación

En una terminal, desde el directorio `tp1`, correr el siguiente comando para compilar un ejecutable a partir de los archivos fuente

    g++ main-ej<1>.cpp red.cpp tp1.cpp red.h tp1.h actividades_PD.h actividades_PD.cpp

donde `<1>` debe ser reemplazado con el número de ejercicio a compilar.

Las etiquetas válidas son:

    ej1, ej2, ej34, ej35, ej36

Explícitamente:

    g++ main-ej1.cpp red.cpp tp1.cpp red.h tp1.h
    g++ main-ej2.cpp red.cpp tp1.cpp red.h tp1.h
    g++ main-ej34.cpp red.cpp tp1.cpp red.h tp1.h actividades_PD.h actividades_PD.cpp
    g++ main-ej35.cpp red.cpp tp1.cpp red.h tp1.h actividades_PD.h actividades_PD.cpp
    g++ main-ej36.cpp red.cpp tp1.cpp red.h tp1.h actividades_PD.h actividades_PD.cpp

Y para utilizar el ejecutable generado con cada una de las líneas:

    ./a.out <ruta a archivo .clq>
