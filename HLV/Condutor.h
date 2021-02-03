#ifndef CONDUTOR_H
#define CONDUTOR_H

#include "TransformarDados.h"
#include "CNH.h"
#include "Pessoa.h"

namespace TP2 {

class Condutor : public TransformarDados
{
private:
    long long int CPF;
    //long int dataDeNascimento;
    CNH cnh;
    Pessoa pessoa;
public:
    Condutor();
    Condutor(long long int CPF, long int dataDeNascimento, CNH cnh, Pessoa pessoa);

    void setCPF(long long int CPF){this->CPF=CPF;}
    void setCnh(CNH  cnh){
        this->cnh=cnh;
    }

    long long int getCPF()const{return this->CPF;}
    CNH getCnh()const{return this->cnh;}

    void montarObjeto(QString & str);
    QString desmontarObjeto()const;

    //-----------------------------------
    void setPessoa (Pessoa pessoa){
        this->pessoa = pessoa;
    }

    Pessoa getPessoa () const{
        return pessoa;
    }
};
}

#endif // Condutor_H
