#ifndef DETECTOR_PLAGIO_H
#define DETECTOR_PLAGIO_H

#include "Documento.h"
#include "Resultado.h"

#include <string>
#include <vector>

// Interfaz abstracta para cualquier algoritmo detector de plagio.
class DetectorPlagio {
public:
    virtual ~DetectorPlagio() = default;

    virtual std::vector<Resultado> analizar(
        const Documento& documento,
        const std::string& directorioBase) const = 0;

    virtual std::string obtenerNombreMotor() const = 0;
};

#endif
