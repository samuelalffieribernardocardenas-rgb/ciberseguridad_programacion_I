# Guía breve de la parte C++

## Compilación manual

Desde `backend/cpp-engine`:

```bash
g++ -std=c++17 *.cpp -o plagio
```

Ejecución:

```bash
./plagio ruta_documento.txt ruta_carpeta_base
```

## Requisitos demostrados

- **Modularidad:** cada clase posee archivos `.h` y `.cpp` independientes.
- **Herencia:** `DocumentoTexto` hereda de la clase abstracta `Documento`.
- **Sobrescritura:** `DocumentoTexto` redefine `leerContenido()` y `obtenerTipo()`; `DetectorWinnowing` redefine los métodos de `DetectorPlagio`.
- **Sobrecarga:** `DetectorWinnowing` tiene dos constructores y dos versiones del método `analizar()`.
- **Polimorfismo:** `principal.cpp` utiliza `unique_ptr<Documento>` y `unique_ptr<DetectorPlagio>` para ejecutar métodos de clases derivadas.
- **Abstracción/interfaz:** `Documento` y `DetectorPlagio` contienen métodos virtuales puros.
- **Excepciones:** se usa la excepción personalizada `ExcepcionPlagio` y bloques `try-catch`.
- **Registro:** los errores capturados se agregan automáticamente a `log.txt`.
- **Comentarios:** las clases, métodos importantes y conceptos evaluables están comentados.

## Archivos principales

- `principal.cpp`: punto de entrada, polimorfismo y `try-catch`.
- `Documento.*`: clase abstracta base.
- `DocumentoTexto.*`: clase derivada.
- `DetectorPlagio.h`: interfaz abstracta.
- `DetectorWinnowing.*`: algoritmo y sobrecarga/sobrescritura.
- `GestorLog.*`: escritura en `log.txt`.
- `ExcepcionPlagio.*`: excepción personalizada.
- `UtilidadesJson.*`: conserva la salida JSON usada por la aplicación web.
- `Resultado.h`: estructura de los resultados.
