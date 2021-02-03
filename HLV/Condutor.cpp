#include "Condutor.h"
namespace TP2 {
Condutor::Condutor():
    CPF(0)
{

}

Condutor::Condutor(long long CPF, long int dataDeNascimento, CNH cnh, Pessoa pessoa):
    CPF(CPF),
    cnh(cnh),
    pessoa(pessoa)
{
}

void Condutor::montarObjeto(QString &str)
{
    try {

        QStringList strList = str.split(';');
        if(strList.length()!=1)
            throw QString ("Erro, falta informaÃ§Ãµes do Condutor");
        CPF = strList[0].toLongLong();
    } catch (QString &erro) {
        throw erro;
    }
}

QString Condutor::desmontarObjeto() const
{
    try{
        QString saida = QString::number(CPF);
        saida += "\n";
        return saida;
     }catch (...){
        throw QString("Erro no metodo desmontar pessoa!");
    }
}

}
