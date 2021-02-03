#ifndef OCORRENCIA_H
#define OCORRENCIA_H
#include "TransformarDados.h"

namespace TP2 {

class Ocorrencia : public TransformarDados
{
private:
    unsigned int idLocacao;
    QString descricao;
public:

    Ocorrencia();
    Ocorrencia(unsigned int idLocacao, QString descricao);

    unsigned int getIdLocacao() const;
    void setIdLocacao(unsigned int idLocacao);

    QString getDescricao() const;
    void setDescricao(const QString &descricao);

    void montarObjeto (QString &);
    QString desmontarObjeto () const;
};

}

#endif // OCORRENCIA_H
