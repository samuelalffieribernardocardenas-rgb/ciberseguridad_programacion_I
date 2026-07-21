#ifndef DOCUMENTO_TEXTO_H
#define DOCUMENTO_TEXTO_H

#include "Documento.h"

// Clase derivada: hereda de Documento y sobrescribe sus métodos virtuales.
class DocumentoTexto : public Documento {
public:
    explicit DocumentoTexto(const std::string& rutaArchivo);

    std::string leerContenido() const override;
    std::string obtenerTipo() const override;
};

#endif
