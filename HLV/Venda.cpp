#include "Venda.h"
namespace TP2 {
QString Venda::getMotivoVenda() const
{
    return motivoVenda;
}

void Venda::setMotivoVenda(const QString motivoVenda)
{
    this->motivoVenda = motivoVenda;
}

Venda::Venda(QString placa, QString motivoVenda ,double valorCompra, double valorVenda, double lucro):
    valorCompra(valorCompra),
    valorVenda(valorVenda),
    lucro(lucro),
    placa(placa),
    motivoVenda(motivoVenda)
{

}

Venda::Venda():
    valorCompra(0),
    valorVenda(0),
    lucro(0),
    placa(""),
    motivoVenda("")
{

}

QString Venda::getPlaca() const
{
    return placa;
}

void Venda::setPlaca(QString placa)
{
    this->placa = placa;
}

double Venda::getValorCompra() const
{
    return valorCompra;
}

void Venda::setValorCompra(double valorCompra)
{
    this->valorCompra = valorCompra;
}

double Venda::getValorVenda() const
{
    return valorVenda;
}

void Venda::setValorVenda(double valorVenda)
{
    this->valorVenda = valorVenda;
}

double Venda::getLucro() const
{
    return lucro;
}

void Venda::setLucro(double lucro)
{
    this->lucro = lucro;
}

void Venda::montarObjeto(QString &str)
{
    try {
        QStringList strList = str.split(";");
        if(strList.length() != 5)
            throw QString ("Erro, faltam informações na venda");
        placa = strList[0];
        valorCompra = strList[1].toDouble();
        valorVenda = strList[2].toDouble();
        lucro = strList[3].toDouble();
        motivoVenda = strList[4];
    } catch (QString &erro) {
        throw erro;
    }
}

QString Venda::desmontarObjeto() const
{
    QString saida("");
    saida += placa;
    saida += ";";
    saida += QString::number(valorCompra);
    saida += ";";
    saida += QString::number(valorVenda);
    saida += ";";
    saida += QString::number(lucro);
    saida += ";";
    saida += motivoVenda;
    saida += "\n";
    return saida;
}

}
