#include "GestorLog.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

void GestorLog::registrarError(const std::string& mensaje,
                               const std::string& archivo) {
    std::ofstream salida(archivo, std::ios::app);
    if (!salida.is_open()) {
        return; // Evita lanzar otra excepción mientras se procesa un error.
    }

    const auto ahora = std::chrono::system_clock::now();
    const std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);
    std::tm fecha{};
#ifdef _WIN32
    localtime_s(&fecha, &tiempo);
#else
    localtime_r(&tiempo, &fecha);
#endif

    salida << '[' << std::put_time(&fecha, "%Y-%m-%d %H:%M:%S") << "] ERROR: "
           << mensaje << '\n';
}
