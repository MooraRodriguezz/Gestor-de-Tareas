# CLI Task Manager en C 

Un gestor de tareas pendientes para terminal desarrollado en **C**, enfocado en el manejo eficiente de memoria dinámica y persistencia de datos.

Este proyecto fue creado para repasar conceptos fundamentales de bajo nivel y estructuras de datos clásicas.

##  Características Principales
- **Estructura de Datos:** Implementación de una **Lista Enlazada Simple** para una gestión dinámica de los nodos.
- **Gestión de Memoria:** Control total de asignación y liberación de memoria (`malloc`, `free`) para evitar *memory leaks*.
- **Persistencia:** Guardado y carga de datos mediante archivos binarios (`.dat`).
- **Seguridad:** Manejo de buffers para evitar *stack overflows* y limpieza de flujo de entrada.

##  Conceptos de C Aplicados
* Punteros dobles (`**`) para modificación de estructuras desde funciones.
* Uso de `static` para generadores de IDs únicos.
* Manejo de archivos con `stdio.h` (`fopen`, `fwrite`, `fread`).
* Manipulación de strings con `string.h`.

##  Instalación y Ejecución

Si tienes `gcc` y `make` instalados, solo clona el repo y ejecuta:

```bash
make
./task_manager
