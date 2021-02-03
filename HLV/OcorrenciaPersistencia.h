#ifndef OCORRENCIAPERSISTENCIA_H
#define OCORRENCIAPERSISTENCIA_H

#include "CRUD.h"
#include "Ocorrencia.h"

namespace TP2 {

class OcorrenciaPersistencia : public CRUD<Ocorrencia>
{
private:
    QString arquivoOcorrencia;
public:
    OcorrenciaPersistencia();
    OcorrenciaPersistencia(QString arquivoOcorrencia);

    void incluir (Ocorrencia &) const;
    std::list<Ocorrencia> *listar () const;
    void excluir (QString &) const;
    void alterar (Ocorrencia &);
};
}
#endif // OCORRENCIAPERSISTENCIA_H
