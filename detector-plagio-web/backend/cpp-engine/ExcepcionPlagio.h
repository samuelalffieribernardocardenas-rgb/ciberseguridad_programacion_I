#ifndef EXCEPCION_PLAGIO_H
#define EXCEPCION_PLAGIO_H

#include <stdexcept>
#include <string>

// Excepción propia del motor para distinguir errores controlados del sistema.
class ExcepcionPlagio : public std::runtime_error {
public:
    explicit ExcepcionPlagio(const std::string& mensaje);
};

#endif
