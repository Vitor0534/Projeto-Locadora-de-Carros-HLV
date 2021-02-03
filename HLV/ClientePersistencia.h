#ifndef CLIENTEPERSISTENCIA_H
#define CLIENTEPERSISTENCIA_H

#include "CRUD.h"
#include "Cliente.h"
#include "PessoaPersistencia.h"

namespace TP2 {

class ClientePersistencia : public CRUD<Cliente>
{
private:
    QString arquivoCliente;
    QString arquivoPessoa;
    QString arquivoEmail;
    QString arquivoTelefone;
    QString arquivoEndereco;
public:
    ClientePersistencia();
    ClientePersistencia(QString arquivoCliente);
    ClientePersistencia(QString arquivoCliente,
                        QString arquivoPessoa,
                        QString arquivoTelefone,
                        QString arquivoEndereco,
                        QString arquivoEmail);

    void incluir (Cliente &) const;
    std::list<Cliente> * listar () const;
    void alterar (Cliente &);
    void excluir (QString &) const;
    bool verificar (QString &);

};


}
#endif // CLIENTEPERSISTENCIA_H
