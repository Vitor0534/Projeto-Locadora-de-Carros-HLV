#ifndef CLIENTE_H
#define CLIENTE_H
#include "TransformarDados.h"
#include "Pessoa.h"
#include "Telefone.h"
#include "Email.h"
#include "Endereco.h"
#include <vector>
namespace  TP2 {

class Cliente : public TransformarDados
{
private:
    long long int identidade;
    long long int numeroDoCartao;
    long long int CPF;
    Pessoa pessoa;
    std::vector<TP2::Telefone> * telefone;
    std::vector<TP2::Email> * email;
    std::vector<TP2::Endereco> * Endereco;

public:
    Cliente();
    Cliente(unsigned long long int identidade, unsigned long long int numeroDoCartao, Pessoa pessoa
    , std::vector<TP2::Telefone> * telefone, std::vector<TP2::Email> * email, std::vector<TP2::Endereco> * Endereco,
            long long int CPF);
    void setIdentidade(unsigned long long int identidade){this->identidade=identidade;}
    void setNumeroDoCartao(unsigned long long int numero){this->numeroDoCartao=numero;}
    unsigned long long int getIdentidade()const{return identidade;}
    unsigned long long int getNumeroDoCartao()const{return numeroDoCartao;}

    void montarObjeto(QString & str);
    QString desmontarObjeto()const;

    //----------------------
    long long getCPF() const;
    void setCPF(long long CPF);
    Pessoa getPessoa() const;
    void setPessoa(Pessoa);
    std::vector<TP2::Telefone> const * const getTelefone() const;
    void setTelefone(std::vector<TP2::Telefone> *);
    std::vector<TP2::Email> const * const getEmail() const;
    void setEmail(std::vector<TP2::Email> *);
    std::vector<TP2::Endereco> const * const getEndereco() const;
    void setEndereco(std::vector<TP2::Endereco> *);
};

}
#endif // CLIENTE_H
