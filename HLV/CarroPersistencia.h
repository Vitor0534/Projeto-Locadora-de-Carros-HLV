#ifndef CARROPERSISTENCIA_H
#define CARROPERSISTENCIA_H
#include "Carro.h"
#include "CategoriaPersistencia.h"
#include "MarcaPersistencia.h"
#include "ModeloPersistencia.h"
#include "CRUD.h"
#include "PesquisaPersistencia.h"
namespace TP2{

class CarroPersistencia : public CRUD<Carro>, PesquisaPersistencia<Carro>
{
private:
    QString nomeDoArquivoDeCarros;
    QString nomeDoArquivoDeMarcas;
    QString nomedoArquivoDeCategorias;
    QString nomeDoArquivoDeModelos;
public:
    CarroPersistencia();
    CarroPersistencia(QString nomeDoArquivoDeCarros);

    CarroPersistencia(QString nomeDoArquivoDeCarros,
                      QString nomeDoArquivoDeMarcas,
                      QString nomedoArquivoDeCategorias,
                      QString nomeDoArquivoDeModelos);

    void incluir(Carro &carro) const;
    void excluir(QString &) const;
    std::list<Carro>* listar() const;
    void alterar (Carro & );

    Carro pesquisar(QString & key);
};

}

#endif // CARROPERSISTENCIA_H
