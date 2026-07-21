#include "DocumentoTexto.h"

#include "ExcepcionPlagio.h"

#include <fstream>
#include <sstream>

DocumentoTexto::DocumentoTexto(const std::string& rutaArchivo)
    : Documento(rutaArchivo) {}

std::string DocumentoTexto::leerContenido() const {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        throw ExcepcionPlagio("No se pudo abrir el archivo: " + ruta);
    }

    std::ostringstream contenido;
    contenido << archivo.rdbuf();

    if (contenido.str().empty()) {
        throw ExcepcionPlagio("El archivo está vacío: " + ruta);
    }

    return contenido.str();
}

std::string DocumentoTexto::obtenerTipo() const {
    return "Documento de texto";
}
