#ifndef VENDA_H
#define VENDA_H

#include "TransformarDados.h"
#include "Carro.h"

namespace  TP2 {
class Venda : public TransformarDados
{
private:
    double valorCompra;
    double valorVenda;
    double lucro;
    QString placa;
    QString motivoVenda;
public:
    Venda(QString placa,QString motivoVenda ,double valorCompra, double valorVenda, double lucro);
    Venda();
    double getValorCompra() const;
    void setValorCompra(double valorCompra);
    double getValorVenda() const;
    void setValorVenda(double valorVenda);
    double getLucro() const;
    void setLucro(double lucro);
    QString getPlaca() const;
    void setPlaca(QString placa);

    QString getMotivoVenda() const;
    void setMotivoVenda(const QString);

    void montarObjeto(QString &);
    QString desmontarObjeto() const;
};

}
#endif // VENDA_H
