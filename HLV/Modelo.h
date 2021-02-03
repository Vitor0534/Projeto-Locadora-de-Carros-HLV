#ifndef MODELO_H
#define MODELO_H
#include "TransformarDados.h"

namespace TP2 {
class Modelo : public TransformarDados
{
private:
    unsigned int id;
    unsigned int idMarca;
    unsigned int qtdPortas;
    double motor;
    QString descricao;
    unsigned int ano;
public:
    Modelo();
    Modelo(unsigned int id, unsigned int qtdPortas, double motor,
           QString descricao, unsigned int ano);

    void setId (unsigned int const);
    unsigned int getId () const;

    void setQtdPortas (unsigned int const);
    unsigned int getQtdPortas () const;

    void setMotor (const double);
    double getMotor () const;

    void setDescricao (QString const);
    QString getDescricao () const;

    void setAno (unsigned int const);
    unsigned int getAno () const;

    unsigned int getIdMarca() const;
    void setIdMarca(unsigned int);

    void montarObjeto (QString &);
    QString desmontarObjeto () const;
};
}


#endif // MODELO_H
