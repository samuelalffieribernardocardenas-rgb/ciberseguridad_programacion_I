#ifndef UTILIDADES_JSON_H
#define UTILIDADES_JSON_H

#include "Resultado.h"

#include <string>
#include <vector>

namespace UtilidadesJson {
    std::string escapar(const std::string& texto);
    std::string crearRespuesta(const std::vector<Resultado>& resultados,
                               const std::string& motor,
                               int kGram,
                               int ventana);
    std::string crearError(const std::string& mensaje);
}

#endif
