#include "ExcepcionPlagio.h"

ExcepcionPlagio::ExcepcionPlagio(const std::string& mensaje)
    : std::runtime_error(mensaje) {}
