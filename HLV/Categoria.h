#ifndef CATEGORIA_H
#define CATEGORIA_H
#include "TransformarDados.h"
namespace TP2{

class Categoria : public TransformarDados
{
private:
    int idCategoria;
    QString descricaoCat;
    QString tipoDeUso;
    double valorTipo;
    double valorSeguro;
public:

    Categoria();
    Categoria(int idCategoria, QString descricaoCat, QString tipoDeUso, double valorTipo, double valorSeguro);

    int getIdCategoria()const{return idCategoria;}
    QString getDescricaoCat()const{return descricaoCat;}

    void setIdCategoria(int idCategoria){this->idCategoria = idCategoria;}
    void setDescricaoCat(QString descricaoCat){this->descricaoCat = descricaoCat;}

    QString getTipoDeUso() const;
    void setTipoDeUso(const QString &);

    double getValorTipo() const;
    void setValorTipo(double );

    double getValorSeguro() const;
    void setValorSeguro(double);

    void montarObjeto(QString & str);
    QString desmontarObjeto()const;
};


}

#endif // CATEGORIA_H
