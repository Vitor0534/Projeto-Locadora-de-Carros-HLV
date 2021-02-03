#ifndef MODELOPERSISTENCIA_H
#define MODELOPERSISTENCIA_H
#include "CRUD.h"
#include "Modelo.h"

namespace TP2 {
class ModeloPersistencia : public CRUD<Modelo>
{
private:
    QString arquivoModelo;
public:
    ModeloPersistencia();
    ModeloPersistencia(QString arquivoModelo);
    void incluir (Modelo &) const;
    std::list<TP2::Modelo> * listar () const;
    void alterar (Modelo & );
    void excluir (QString &) const;
};
}


#endif // MODELOPERSISTENCIA_H
