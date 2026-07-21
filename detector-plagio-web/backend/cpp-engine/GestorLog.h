#ifndef GESTOR_LOG_H
#define GESTOR_LOG_H

#include <string>

// Clase responsable de registrar errores en el archivo log.txt.
class GestorLog {
public:
    static void registrarError(const std::string& mensaje,
                               const std::string& archivo = "log.txt");
};

#endif
