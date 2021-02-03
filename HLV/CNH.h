#ifndef CNH_H
#define CNH_H

#include "TransformarDados.h"

namespace TP2 {

class CNH : public TransformarDados
{
public:
    enum CategoriaCnh{A,B,C,D,E,AB,ACC};
private:
    long long int CPF;
    long long int numeroCnh;
    long int dataDaPrimeiraCnh;
    long int dataDeVencimento;
    unsigned int enumCnh;
public:
    CNH();
    CNH(long long int CPF,long long int numeroCnh,long int dataDaPrimeiraCnh,long int dataDeVencimento,unsigned int enumCnh);

    void setCPF(long long int CPF){this->CPF=CPF;}
    void setNumeroCnh(long long int numeroCnh){this->numeroCnh=numeroCnh;}
    void setDataDaPrimeiraCnh(long int dataDaPrimeiraCnh){this->dataDaPrimeiraCnh=dataDaPrimeiraCnh;}
    void setDataDeVencimento(long int dataDeVencimento){this->dataDeVencimento=dataDeVencimento;}
    void setEnumCnh(unsigned int enumCnh){this->enumCnh=enumCnh;}

    long long int getCPF()const{ return this->CPF;}
    long long int  getNumeroCnh()const{return this->numeroCnh;}
    long int  getDataDaPrimeiraCnh()const{return this->dataDaPrimeiraCnh;}
    long int  getDataDeVencimento()const{return this->dataDeVencimento;}
    unsigned int getEnumCnh()const{return this->enumCnh;}

    void montarObjeto(QString & str);
    QString desmontarObjeto()const;
    QString defineCategoriaCnh(int enumCnh)const;

};

}
#endif // CNH_H
