#include "Ocorrencia.h"

namespace TP2 {

Ocorrencia::Ocorrencia():
    idLocacao(0),
    descricao("")
{

}

Ocorrencia::Ocorrencia(unsigned int idLocacao, QString descricao):
    idLocacao(idLocacao),
    descricao(descricao)
{

}


unsigned int Ocorrencia::getIdLocacao() const
{
    return idLocacao;
}

void Ocorrencia::setIdLocacao(unsigned int idLocacao)
{
    this->idLocacao = idLocacao;
}

QString Ocorrencia::getDescricao() const
{
    return descricao;
}

void Ocorrencia::setDescricao(const QString &descricao)
{
    this->descricao = descricao;
}

void Ocorrencia::montarObjeto(QString & str)
{    try {
        QStringList strList = str.split(";");
        if (strList.length()!=2)
            throw QString ("Erro, impossivel montar ocorrencia, faltam informaÃ§Ãµes");
        idLocacao = strList[0].toInt();
        descricao = strList[1];
    } catch (QString &erro) {
        throw erro;
    }
}

QString Ocorrencia::desmontarObjeto() const
{
    try {
        QString saida("");
        saida += QString::number(idLocacao);
        saida += ";";
        saida += descricao;
        saida += "\n";
        return saida;
    } catch (QString &erro) {
        throw erro;
    }
}
}
