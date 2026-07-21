#include "UtilidadesJson.h"

#include <iomanip>
#include <sstream>

std::string UtilidadesJson::escapar(const std::string& texto) {
    std::string salida;
    for (char caracter : texto) {
        switch (caracter) {
            case '"': salida += "\\\""; break;
            case '\\': salida += "\\\\"; break;
            case '\n': salida += "\\n"; break;
            case '\r': salida += "\\r"; break;
            case '\t': salida += "\\t"; break;
            default: salida += caracter;
        }
    }
    return salida;
}

std::string UtilidadesJson::crearRespuesta(
    const std::vector<Resultado>& resultados,
    const std::string& motor,
    int kGram,
    int ventana) {
    const double general = resultados.empty() ? 0.0 : resultados.front().similitud;
    const std::string nivel = resultados.empty() ? "Bajo" : resultados.front().riesgo;

    std::ostringstream json;
    json << std::fixed << std::setprecision(2)
         << "{\"resultadoGeneral\":" << general
         << ",\"nivelRiesgo\":\"" << escapar(nivel)
         << "\",\"motor\":\"" << escapar(motor)
         << "\",\"parametros\":{\"kgram\":" << kGram
         << ",\"ventana\":" << ventana << "},\"comparaciones\":[";

    for (std::size_t i = 0; i < resultados.size(); ++i) {
        const auto& resultado = resultados[i];
        json << "{\"documento\":\"" << escapar(resultado.documento)
             << "\",\"similitud\":" << resultado.similitud
             << ",\"riesgo\":\"" << escapar(resultado.riesgo)
             << "\",\"coincidencias\":" << resultado.coincidencias << '}';
        if (i + 1 < resultados.size()) json << ',';
    }
    json << "]}";
    return json.str();
}

std::string UtilidadesJson::crearError(const std::string& mensaje) {
    return "{\"error\":\"" + escapar(mensaje) + "\"}";
}
