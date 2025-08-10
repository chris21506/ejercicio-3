Procedimiento EjemploHashTableChaining()
// Crear tabla hash con tamaño 4
miHashTableChaining = nuevo HashTableChaining(tamaño = 4)

// Agregar algunos valores
miHashTableChaining.Agregar(39)
miHashTableChaining.Agregar(252)
miHashTableChaining.Agregar(40)
miHashTableChaining.Agregar(0)
miHashTableChaining.Agregar(24)

// Imprimir contenido de la tabla
miHashTableChaining.Imprimir()

// Verificar si contiene 1234 y probar remover
Si no miHashTableChaining.Contiene(1234) Entonces
Imprimir "No contiene 1234, intentar borrar para probar que no da error"
// miHashTableChaining.Remover(1234)  (comentado para no fallar)
FinSi

// Verificar si contiene 40 y removerlo
Si miHashTableChaining.Contiene(40) Entonces
Imprimir "Contiene 40, lo vamos a borrar"
miHashTableChaining.Remover(40)
FinSi

// Imprimir contenido después de borrar
miHashTableChaining.Imprimir()

// Crear otra tabla hash con tamaño 100
hashTableChainingEjemplo = nuevo HashTableChaining(tamaño = 100)

// Insertar 100 números aleatorios (0 o 1)
Para i = 0 Hasta 99 Hacer
numeroAleatorio = número aleatorio entre 0 y 1
hashTableChainingEjemplo.Agregar(numeroAleatorio)
FinPara

// En promedio cada índice debería tener ~1 elemento (100/100)
hashTableChainingEjemplo.Imprimir()
FinProcedimiento
