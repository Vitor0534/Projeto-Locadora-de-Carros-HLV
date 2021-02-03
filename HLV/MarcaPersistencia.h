#ifndef MARCAPERSISTENCIA_H
#define MARCAPERSISTENCIA_H
#include "CRUD.h"
#include "Marca.h"
#include "Modelo.h"

namespace TP2 {

class MarcaPersistencia: public CRUD<Marca>
{
private:
    QString arquivoMarca;
    QString arquivoModelo;
public:
    MarcaPersistencia ();
    MarcaPersistencia(QString arquivoMarca);
    MarcaPersistencia(QString arquivoMarca, QString arquivoModelo);

    void incluir(Marca &) const;
    void excluir(QString &) const;
    std::list<Marca>* listar() const;
    void alterar (Marca & );
};
}
#endif // MARCAPERSISTENCIA_H
