#ifndef VENDAPERSISTENCIA_H
#define VENDAPERSISTENCIA_H

#include "CRUD.h"
#include "Venda.h"

namespace TP2 {

class VendaPersistencia : public CRUD<Venda>
{
private:
    QString arquivoVenda;
public:
    VendaPersistencia(QString arquivoVenda);
    VendaPersistencia();

    void incluir (Venda &) const;
    std::list<Venda> * listar () const;
    void excluir (QString &) const;
    void alterar (Venda & );
};
}

#endif // VENDAPERSISTENCIA_H
