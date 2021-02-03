#ifndef VALIDACOES_H
#define VALIDACOES_H
#include <ctime>
#include<QString>
#include <QStringList>
namespace TP2 {
class Validacoes
{
public:
    bool ValidaTelefone(long long int telefone){
        try {
            if(telefone<20000000||telefone>999999999)
                return true;
            return false;
        } catch (...) {
            throw QString("Erro na Funcao ValidaTelefone!");
        }
    }


    long int converterData (QString str){
        QStringList strList = str.split("/");
        long int data;
        data = strList[0].toInt() * 1000000
                + strList[1].toInt()*10000 + strList[2].toInt();
        return data;
    }

    bool ValidaCPF(long long int cpf){
        try{
            if (cpf<10000000000 || cpf>99999999999)
                return false;


            int d1, d2, d3,d4,d5, d6,d7,d8,d9,d10,d11,dv1,dv2;

            d1 =       (cpf / 10000000000);
            d2 =       (cpf % 10000000000)/ 1000000000;
            d3 =      ((cpf % 10000000000)% 1000000000)/ 100000000;
            d4 =     (((cpf % 10000000000)% 1000000000)% 100000000)/10000000;
            d5 =    ((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)/1000000;
            d6 =   (((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)%1000000)/100000;
            d7 =  ((((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)%1000000)%100000)/10000;
            d8 = (((((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)%1000000)%100000)%10000)/1000;
            d9 =((((((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)%1000000)%100000)%10000)%1000)/100;
            d10=(((((((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)%1000000)%100000)%10000)%1000)%100)/10;
            d11=(((((((((cpf % 10000000000)% 1000000000)% 100000000)%10000000)%1000000)%100000)%10000)%1000)%100)%10;
            dv1 = (((d1*10)+(d2*9)+(d3*8)+(d4*7)+(d5*6)+(d6*5)+(d7*4)+(d8*3)+(d9*2))*10)%11;
            dv2 = (((d1*11)+(d2*10)+(d3*9)+(d4*8)+(d5*7)+(d6*6)+(d7*5)+(d8*4)+(d9*3)+(dv1*2))*10)%11;


            if((dv1==d10)&&((dv2%10)==d11))
                return true;
            else
            {
                return false;
            }
        }catch(...){
            throw QString("Erro na Funcao ValidaCPF!");
        }
    }

    bool ValidaCNH(long long int cnh){
        try {
            if(cnh<10000000000 || cnh > 99999999999)
                return true;
            else
                return false;
        } catch (...) {
            throw QString("Erro na Funcao ValidaCNH!");
        }
    }

    bool ValidaCategoriaCNH(QString categoria){
        try {
            if(categoria=="A"||categoria=="AB"||categoria=="C"||categoria=="D"||categoria=="E")
                return true;
            return false;
        } catch (...) {
            throw QString("Erro na Funcao ValidaIdadeCarro!");
        }
    }
    //@Override
    typedef struct {
        int dia;
        int mes;
        int ano;
    } Data;
    /* guarda o numero de dias em cada mes para anos normais e bissextos */
    int dias_mes[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                           {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    /*
     * Retorna 1 caso 'ano' seja bissexto, 0 caso contrário
     */
    unsigned int bissexto(int ano) {
        return (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
    }

    /*
     * Retorna a distancia entre inicio e fim em dias.
     * Assume que inicio nao vem depois de fim.
     */
    unsigned long dist_dias (Data inicio, Data fim) {
        unsigned long idias, fdias;	/* guarda qtos dias tem da data */
        /* ate o comeco do ano */
        unsigned long def_anos = 0;	/* guarda diferenca entre anos das */
        /* datas inicio e fim medida em dias */
        register int i;
        int dbissexto;

        idias = inicio.dia;
        dbissexto = bissexto (inicio.ano);
        for (i = inicio.mes - 1; i > 0; --i)
            idias += dias_mes[dbissexto][i];

        fdias = fim.dia;
        dbissexto = bissexto (fim.ano);
        for (i = fim.mes - 1; i > 0; --i)
            fdias += dias_mes[dbissexto][i];

        while (inicio.ano < fim.ano)
            def_anos += 365 + bissexto(inicio.ano++);

        return def_anos - idias + fdias;
    }
    //fala qual data é maior
    bool maiorData(int d1,int d2){

        int dia1,mes1,ano1;
        int dia2,mes2,ano2;

        int soma1,soma2;

        dia1=d1/1000000;
        mes1=((d1/10000))%100;
        ano1=d1%10000;

        dia2=d2/1000000;
        mes2=((d2/10000)%100);
        ano2=d2%10000;

        soma1=dia1*mes1*ano1;
        soma2=dia2*mes2*ano2;

        if(soma1>=soma2) //retorna 0 se d1 é maior que d2
            return true;
        else{
            return false;
        }

    }
    int diferencaDatas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);

};
}

#endif // VALIDACOES_H
