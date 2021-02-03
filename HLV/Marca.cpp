#include "Marca.h"

namespace TP2 {

Marca::Marca():
    idMarca(0),
    descricaoMarca(""),
    modelos(0)
{
    modelos = new std::list<Modelo>();
}

Marca::Marca(int idMarca, QString descricaoMarca, std::list<Modelo> *modelos):
    idMarca(idMarca),
    descricaoMarca(descricaoMarca),
    modelos(modelos)
{
}

std::list<Modelo> const * const Marca::getModelos() const
{
    return modelos;
}

void Marca::setModelos(std::list<Modelo> *modelos)
{
    if(this->modelos)
        delete this->modelos;
    this->modelos = modelos;
}

void Marca::montarObjeto(QString &str){
    try {
        QStringList strList = str.split(';');
        if(strList.length()!=2)
            throw QString ("Erro, faltam informações n marca");
        idMarca = strList[0].toInt();
        descricaoMarca = strList[1];

    } catch (QString &erro) {
        throw erro;
    }
}

QString Marca::desmontarObjeto()const{
    try{
        QString saida = QString::number(idMarca);
        saida += ";";
        saida += descricaoMarca+"\n";
        return saida;
    }catch (...){
        throw QString("Erro no metodo desmontar Marca!");

    }
}

}
