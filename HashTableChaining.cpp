// Procedimiento de ejemplo para probar la tabla hash con encadenamiento
Procedimiento EjemploHashTableChaining()

// 1. Crear tabla hash con tamaño inicial 4
miHashTableChaining = nuevo HashTableChaining(tamaño = 4)

// 2. Insertar varios valores para generar colisiones y probar encadenamiento
miHashTableChaining.Agregar(39)    // Se agrega en la posición calculada por la función hash
miHashTableChaining.Agregar(252)   // Puede colisionar con 39 dependiendo de hash
miHashTableChaining.Agregar(40)
miHashTableChaining.Agregar(0)
miHashTableChaining.Agregar(24)

// 3. Mostrar la tabla después de las inserciones
miHashTableChaining.Imprimir()

// 4. Verificar si el valor 1234 está presente en la tabla
//    Si no está, imprimir mensaje y (opcionalmente) intentar eliminarlo
Si no miHashTableChaining.Contiene(1234) Entonces
Imprimir "No contiene 1234, intentar borrar para probar que no da error"
// miHashTableChaining.Remover(1234)  // Línea comentada para no generar error
FinSi

// 5. Verificar si el valor 40 existe en la tabla
//    Si está, eliminarlo y mostrar mensaje
Si miHashTableChaining.Contiene(40) Entonces
Imprimir "Contiene 40, lo vamos a borrar"
miHashTableChaining.Remover(40)
FinSi

// 6. Imprimir contenido de la tabla después de eliminar el valor 40
miHashTableChaining.Imprimir()

// 7. Crear una nueva tabla hash más grande (tamaño 100) para hacer pruebas estadísticas
hashTableChainingEjemplo = nuevo HashTableChaining(tamaño = 100)

// 8. Insertar 100 valores aleatorios (0 o 1) para observar distribución
Para i = 0 Hasta 99 Hacer
numeroAleatorio = número aleatorio entre 0 y 1
hashTableChainingEjemplo.Agregar(numeroAleatorio)
FinPara

// 9. En promedio, cada índice debería tener alrededor de 1 elemento (100 elementos / 100 índices)
//    Imprimir la tabla resultante para ver distribución
hashTableChainingEjemplo.Imprimir()

FinProcedimiento
