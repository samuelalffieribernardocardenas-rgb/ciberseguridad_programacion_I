#ifndef RESULTADO_H
#define RESULTADO_H

#include <string>

// Representa el resultado de comparar el documento analizado con un archivo base.
struct Resultado {
    std::string documento;
    double similitud{};
    std::string riesgo;
    int coincidencias{};
};

#endif
