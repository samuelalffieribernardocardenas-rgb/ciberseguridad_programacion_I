#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <string>

// Clase abstracta base. Demuestra abstracción y permite usar polimorfismo.
class Documento {
protected:
    std::string ruta;

public:
    explicit Documento(std::string rutaArchivo);
    virtual ~Documento() = default;

    const std::string& obtenerRuta() const;
    virtual std::string leerContenido() const = 0;
    virtual std::string obtenerTipo() const = 0;
};

#endif
