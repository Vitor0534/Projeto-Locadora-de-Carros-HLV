#include "CNH.h"
namespace TP2 {

CNH::CNH():
    CPF(0),
    numeroCnh(0),
    dataDaPrimeiraCnh(0),
    dataDeVencimento(0),
    enumCnh(0)
{

}

CNH::CNH(long long CPF, long long numeroCnh, long dataDaPrimeiraCnh, long dataDeVencimento, unsigned int enumCnh):
    CPF(CPF),
    numeroCnh(numeroCnh),
    dataDaPrimeiraCnh(dataDaPrimeiraCnh),
    dataDeVencimento(dataDeVencimento),
    enumCnh(enumCnh)

{
}

void CNH::montarObjeto(QString &str)
{
    try {

        QStringList strList = str.split(';');
        if(strList.length()!=5)
            throw QString ("Erro falta informações na CNH");
        CPF=strList[0].toLongLong();
        numeroCnh = strList[1].toLong();
        dataDaPrimeiraCnh = strList[2].toLongLong();
        dataDeVencimento = strList[3].toLong();
        enumCnh = strList[4].toInt();

    } catch (QString &erro) {
        throw erro;
    }
}

QString CNH::desmontarObjeto() const
{
    try{

        QString saida="";
        saida += QString::number(CPF) + ";";
        saida += QString::number(numeroCnh) + ";";
        saida += QString::number(dataDaPrimeiraCnh) + ";";
        saida += QString::number(dataDeVencimento) + ";";
        saida += QString::number(enumCnh) + "\n";
        return saida;

    }catch (QString &erro){
        throw erro;

    }
}

QString CNH::defineCategoriaCnh(int enumCnh) const
{
    try {
        if(enumCnh<0||enumCnh>6)
           throw QString("categoria fora do intervalo valido!!!");

        if(enumCnh == A)
            return "A";
        if(enumCnh == B)
            return "B";
        if(enumCnh == C)
            return "C";
        if(enumCnh == D)
            return "D";
        if(enumCnh == E)
            return "E";
        if(enumCnh == AB)
            return "AB";
        if(enumCnh == ACC)
            return "ACC";

    } catch(QString & erro) {
        throw (erro);
    }
}

}
