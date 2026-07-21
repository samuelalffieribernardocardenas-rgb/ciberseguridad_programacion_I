#include "DetectorPlagio.h"
#include "DetectorWinnowing.h"
#include "Documento.h"
#include "DocumentoTexto.h"
#include "ExcepcionPlagio.h"
#include "GestorLog.h"
#include "UtilidadesJson.h"

#include <exception>
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            throw ExcepcionPlagio(
                "Uso incorrecto. Se requiere: plagio <documento> <directorio_base>");
        }

        // Polimorfismo: puntero de la clase base Documento apunta a DocumentoTexto.
        std::unique_ptr<Documento> documento =
            std::make_unique<DocumentoTexto>(argv[1]);

        // Polimorfismo: puntero de la interfaz base llama a la clase derivada.
        std::unique_ptr<DetectorPlagio> detector =
            std::make_unique<DetectorWinnowing>();

        const auto resultados = detector->analizar(*documento, argv[2]);

        // Se usa dynamic_cast solo para obtener los parámetros propios del detector concreto.
        const auto* winnowing = dynamic_cast<const DetectorWinnowing*>(detector.get());
        const int kGram = winnowing ? winnowing->obtenerTamanoKGram() : 0;
        const int ventana = winnowing ? winnowing->obtenerTamanoVentana() : 0;

        std::cout << UtilidadesJson::crearRespuesta(
            resultados, detector->obtenerNombreMotor(), kGram, ventana);
        return 0;

    } catch (const ExcepcionPlagio& error) {
        GestorLog::registrarError(error.what());
        std::cout << UtilidadesJson::crearError(error.what());
        return 1;
    } catch (const std::exception& error) {
        GestorLog::registrarError(std::string("Error inesperado: ") + error.what());
        std::cout << UtilidadesJson::crearError("Ocurrió un error interno en el motor C++");
        return 1;
    } catch (...) {
        GestorLog::registrarError("Error desconocido en el motor C++");
        std::cout << UtilidadesJson::crearError("Ocurrió un error desconocido");
        return 1;
    }
}
