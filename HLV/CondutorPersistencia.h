#ifndef CONDUTOR_PERSISTENCIA_H
#define CONDUTOR_PERSISTENCIA_H
#include "CRUD.h"
#include "Condutor.h"
#include "PessoaPersistencia.h"
#include "PesquisaPersistencia.h"
namespace TP2 {

class CondutorPersistencia : public CRUD<Condutor>
{
private:
    QString arquivoCondutor;
    QString arquivoCNH;
    QString arquivoPessoa;
public:
    CondutorPersistencia();
    CondutorPersistencia(QString arquivoCondutor);
    CondutorPersistencia(QString arquivoCondutor, QString arquivoCNH,  QString arquivoPessoa);

    void incluir(Condutor &condutor) const;
    void excluir(QString &) const;
    std::list<Condutor>* listar() const;
    void alterar (Condutor & );
    bool verificar (QString &);
};


}
#endif // CondutorPersistencia_H
