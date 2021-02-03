#include "Categoria.h"

namespace TP2 {

Categoria::Categoria(int idCategoria, QString descricaoCat, QString tipoDeUso, double valorTipo, double valorSeguro):
    idCategoria(idCategoria),
    descricaoCat(descricaoCat),
    tipoDeUso(tipoDeUso),
    valorTipo(valorTipo),
    valorSeguro(valorSeguro)
{
}


Categoria::Categoria():
    idCategoria(0),
    descricaoCat(""),
    tipoDeUso(""),
    valorTipo(0),
    valorSeguro(0)
{
}

QString Categoria::getTipoDeUso() const
{
    return tipoDeUso;
}

void Categoria::setTipoDeUso(const QString &tipoDeUso)
{
    this->tipoDeUso = tipoDeUso;
}

double Categoria::getValorTipo() const
{
    return valorTipo;
}

void Categoria::setValorTipo(double valorTipo)
{
    this->valorTipo = valorTipo;
}

double Categoria::getValorSeguro() const
{
    return valorSeguro;
}

void Categoria::setValorSeguro(double valorSeguro)
{
    this->valorSeguro = valorSeguro;
}

void Categoria::montarObjeto(QString &str){
    try {
        QStringList strList = str.split(';');
        if(strList.length()!=5)
            throw QString("Erro no metodo montar Categoria!");
        idCategoria = strList[0].toInt();
        descricaoCat = strList[1];
        tipoDeUso = strList[2];
        valorTipo = strList[3].toDouble();
        valorSeguro = strList[4].toDouble();
    } catch (QString &erro) {
        throw erro;
    }
}

QString Categoria::desmontarObjeto()const{
    try{
        QString saida = QString::number(idCategoria);
        saida += ";";
        saida += descricaoCat;
        saida += ";";
        saida += tipoDeUso;
        saida += ";";
        saida += QString::number(valorTipo);
        saida += ";";
        saida += QString::number(valorSeguro);
        saida += "\n";
        return saida;
    }catch (...){
        throw QString("Erro no metodo desmontar categoria!");

    }
}

}
