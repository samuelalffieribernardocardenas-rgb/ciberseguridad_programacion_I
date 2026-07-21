#ifndef DETECTOR_WINNOWING_H
#define DETECTOR_WINNOWING_H

#include "DetectorPlagio.h"

#include <unordered_set>
#include <vector>

// Implementación concreta del algoritmo Rabin-Karp + Winnowing.
class DetectorWinnowing : public DetectorPlagio {
private:
    int tamanoKGram;
    int tamanoVentana;
    static constexpr long long BASE = 256;
    static constexpr long long MODULO = 1000000007;

    std::string normalizar(const std::string& texto) const;
    std::vector<std::string> crearKGramas(const std::string& texto) const;
    long long calcularHash(const std::string& cadena) const;
    std::vector<long long> aplicarWinnowing(
        const std::vector<long long>& hashes) const;
    std::unordered_set<long long> crearHuella(const std::string& texto) const;
    double calcularJaccard(const std::unordered_set<long long>& a,
                           const std::unordered_set<long long>& b,
                           int& coincidencias) const;
    std::string clasificarRiesgo(double similitud) const;

public:
    DetectorWinnowing();
    DetectorWinnowing(int kGram, int ventana); // Sobrecarga de constructor.

    std::vector<Resultado> analizar(
        const Documento& documento,
        const std::string& directorioBase) const override;

    // Sobrecarga: permite analizar directamente mediante rutas.
    std::vector<Resultado> analizar(
        const std::string& rutaDocumento,
        const std::string& directorioBase) const;

    std::string obtenerNombreMotor() const override;
    int obtenerTamanoKGram() const;
    int obtenerTamanoVentana() const;
};

#endif
