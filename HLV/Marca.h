#ifndef MARCA_H
#define MARCA_H

#include "TransformarDados.h"
#include "Modelo.h"
namespace TP2{

class Marca : public TransformarDados
{
private:
    int idMarca;
    QString descricaoMarca;
    std::list<Modelo> * modelos;
public:

    Marca();
    Marca(int idMarca, QString descricaoMarca, std::list<Modelo> * modelos);

    int getIdMarca()const{return idMarca;}
    QString getDescricaoMarca()const{return descricaoMarca;}

    void setIdMarca(int idMarca){this->idMarca = idMarca;}
    void setDescricaoMarca(QString descricaoMarca){this->descricaoMarca = descricaoMarca;}

    std::list<Modelo> const * const getModelos() const;
    void setModelos(std::list<Modelo> *);

    void montarObjeto(QString & str);
    QString desmontarObjeto()const;
};

}

#endif // MARCA_H
