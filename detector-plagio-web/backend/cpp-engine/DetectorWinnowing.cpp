#include "DetectorWinnowing.h"

#include "DocumentoTexto.h"
#include "ExcepcionPlagio.h"

#include <algorithm>
#include <cctype>
#include <filesystem>

namespace fs = std::filesystem;

DetectorWinnowing::DetectorWinnowing() : tamanoKGram(7), tamanoVentana(5) {}

DetectorWinnowing::DetectorWinnowing(int kGram, int ventana)
    : tamanoKGram(kGram), tamanoVentana(ventana) {
    if (kGram <= 0 || ventana <= 0) {
        throw ExcepcionPlagio("Los parámetros k-gram y ventana deben ser positivos");
    }
}

std::string DetectorWinnowing::normalizar(const std::string& texto) const {
    std::string limpio;
    bool espacioAnterior = false;

    for (unsigned char caracter : texto) {
        if (std::isalnum(caracter)) {
            limpio += static_cast<char>(std::tolower(caracter));
            espacioAnterior = false;
        } else if (std::isspace(caracter) && !espacioAnterior) {
            limpio += ' ';
            espacioAnterior = true;
        }
    }

    if (!limpio.empty() && limpio.front() == ' ') limpio.erase(limpio.begin());
    if (!limpio.empty() && limpio.back() == ' ') limpio.pop_back();
    return limpio;
}

std::vector<std::string> DetectorWinnowing::crearKGramas(const std::string& texto) const {
    std::vector<std::string> kGramas;
    if (static_cast<int>(texto.size()) < tamanoKGram) return kGramas;

    for (std::size_t i = 0; i + tamanoKGram <= texto.size(); ++i) {
        kGramas.push_back(texto.substr(i, tamanoKGram));
    }
    return kGramas;
}

long long DetectorWinnowing::calcularHash(const std::string& cadena) const {
    long long hash = 0;
    for (unsigned char caracter : cadena) {
        hash = (hash * BASE + caracter) % MODULO;
    }
    return hash;
}

std::vector<long long> DetectorWinnowing::aplicarWinnowing(
    const std::vector<long long>& hashes) const {
    std::vector<long long> huella;
    if (hashes.empty()) return huella;

    if (static_cast<int>(hashes.size()) < tamanoVentana) {
        huella.push_back(*std::min_element(hashes.begin(), hashes.end()));
        return huella;
    }

    long long ultimoMinimo = -1;
    for (std::size_t i = 0; i + tamanoVentana <= hashes.size(); ++i) {
        long long minimo = hashes[i];
        for (std::size_t j = i; j < i + tamanoVentana; ++j) {
            if (hashes[j] <= minimo) minimo = hashes[j];
        }
        if (minimo != ultimoMinimo) {
            huella.push_back(minimo);
            ultimoMinimo = minimo;
        }
    }
    return huella;
}

std::unordered_set<long long> DetectorWinnowing::crearHuella(
    const std::string& texto) const {
    const std::string normalizado = normalizar(texto);
    const auto kGramas = crearKGramas(normalizado);

    std::vector<long long> hashes;
    hashes.reserve(kGramas.size());
    for (const auto& kGrama : kGramas) hashes.push_back(calcularHash(kGrama));

    const auto seleccionados = aplicarWinnowing(hashes);
    return {seleccionados.begin(), seleccionados.end()};
}

double DetectorWinnowing::calcularJaccard(
    const std::unordered_set<long long>& a,
    const std::unordered_set<long long>& b,
    int& coincidencias) const {
    int interseccion = 0;
    for (long long hash : a) {
        if (b.find(hash) != b.end()) ++interseccion;
    }

    const int unionTotal = static_cast<int>(a.size() + b.size()) - interseccion;
    coincidencias = interseccion;
    return unionTotal > 0 ? (static_cast<double>(interseccion) / unionTotal) * 100.0 : 0.0;
}

std::string DetectorWinnowing::clasificarRiesgo(double similitud) const {
    if (similitud <= 20.0) return "Bajo";
    if (similitud <= 50.0) return "Moderado";
    if (similitud <= 75.0) return "Alto";
    return "Crítico";
}

std::vector<Resultado> DetectorWinnowing::analizar(
    const Documento& documento,
    const std::string& directorioBase) const {
    if (!fs::exists(directorioBase) || !fs::is_directory(directorioBase)) {
        throw ExcepcionPlagio("El directorio base no existe: " + directorioBase);
    }

    const auto huellaDocumento = crearHuella(documento.leerContenido());
    std::vector<Resultado> resultados;

    for (const auto& entrada : fs::directory_iterator(directorioBase)) {
        if (!entrada.is_regular_file() || entrada.path().extension() != ".txt") continue;

        try {
            DocumentoTexto documentoBase(entrada.path().string());
            const auto huellaBase = crearHuella(documentoBase.leerContenido());
            int coincidencias = 0;
            const double similitud = calcularJaccard(
                huellaDocumento, huellaBase, coincidencias);

            resultados.push_back({
                entrada.path().filename().string(),
                similitud,
                clasificarRiesgo(similitud),
                coincidencias
            });
        } catch (const ExcepcionPlagio&) {
            // Un archivo base inválido se omite; el error principal se gestiona arriba.
        }
    }

    std::sort(resultados.begin(), resultados.end(),
              [](const Resultado& a, const Resultado& b) {
                  return a.similitud > b.similitud;
              });
    return resultados;
}

std::vector<Resultado> DetectorWinnowing::analizar(
    const std::string& rutaDocumento,
    const std::string& directorioBase) const {
    DocumentoTexto documento(rutaDocumento);
    return analizar(documento, directorioBase);
}

std::string DetectorWinnowing::obtenerNombreMotor() const {
    return "C++ Rabin-Karp + Winnowing";
}

int DetectorWinnowing::obtenerTamanoKGram() const { return tamanoKGram; }
int DetectorWinnowing::obtenerTamanoVentana() const { return tamanoVentana; }
