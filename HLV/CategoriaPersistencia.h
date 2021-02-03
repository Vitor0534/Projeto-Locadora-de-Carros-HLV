#ifndef CATEGORIAPERSISTENCIA_H
#define CATEGORIAPERSISTENCIA_H

#include "Categoria.h"
#include "CRUD.h"

namespace TP2{

class CategoriaPersistencia: public CRUD<Categoria>
{
private:
    QString nomeDoArquivoNoDisco;
public:
    CategoriaPersistencia();
    CategoriaPersistencia(QString nomeDoArquivoNoDisco);


    void incluir(Categoria &objeto) const;
    void excluir(QString &nome) const;
    std::list<Categoria> * listar() const;
    void alterar (Categoria & );

};
}


#endif // CATEGORIAPERSISTENCIA_H
