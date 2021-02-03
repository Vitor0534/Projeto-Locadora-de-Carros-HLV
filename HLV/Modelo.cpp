#include "Modelo.h"

namespace TP2 {

Modelo::Modelo():
    id(0),
    idMarca(0),
    qtdPortas(0),
    motor(0),
    descricao(""),
    ano(0)

{

}

Modelo::Modelo(unsigned int id, unsigned int qtdPortas,
               double motor, QString descricao, unsigned int ano) :
    id(id),
    qtdPortas(qtdPortas),
    motor(motor),
    descricao(descricao),
    ano(ano)
{

}

unsigned int Modelo::getIdMarca() const
{
    return idMarca;
}

void Modelo::setIdMarca(unsigned int idMarca)
{
    this->idMarca = idMarca;
}

void Modelo::setId(const unsigned int id)
{
    this->id = id;
}

unsigned int Modelo::getId() const
{
    return id;
}

void Modelo::setQtdPortas(const unsigned int qtdPortas)
{
    this->qtdPortas = qtdPortas;
}

unsigned int Modelo::getQtdPortas() const
{
    return qtdPortas;
}

void Modelo::setMotor(const double motor)
{
    this->motor = motor;
}

double Modelo::getMotor() const
{
    return motor;
}

void Modelo::setDescricao(const QString descricao)
{
    this->descricao = descricao;
}

QString Modelo::getDescricao() const
{
    return descricao;
}

void Modelo::setAno(const unsigned int ano)
{
    this->ano = ano;
}

unsigned int Modelo::getAno() const
{
    return ano;
}

void Modelo::montarObjeto(QString & str)
{
    try {
        QStringList strList = str.split(";");
        if (strList.length() != 6)
        {
            throw QString ("Erro, faltam informações no modelo");
        }
        id = strList[0].toInt();
        idMarca = strList[1].toInt();
        descricao = strList[2];
        qtdPortas = strList[3].toInt();
        motor = strList[4].toInt();
        ano = strList[5].toInt();
    } catch (QString & erro) {
        throw erro;
    }
}

QString Modelo::desmontarObjeto() const
{
    QString saida("");
    saida += QString::number(id);
    saida += ";";
    saida += QString::number(idMarca);
    saida += ";";
    saida += descricao;
    saida += ";";
    saida += QString::number(qtdPortas);
    saida += ";";
    saida += QString::number(motor);
    saida += ";";
    saida += QString::number(ano);
    saida += "\n";
    return saida;
}
}

