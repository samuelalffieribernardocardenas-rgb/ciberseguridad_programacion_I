#include "Documento.h"

#include <utility>

Documento::Documento(std::string rutaArchivo) : ruta(std::move(rutaArchivo)) {}

const std::string& Documento::obtenerRuta() const {
    return ruta;
}
