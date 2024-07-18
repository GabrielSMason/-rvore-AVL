#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    void destrutorArvore(Nodo<T>*nodo){
        if(nodo != nullptr){
            destrutorArvore(nodo->filhoEsquerda);
            destrutorArvore(nodo->filhoDireita);
            delete nodo;
        }
    }
    virtual ~MinhaArvoreAVL(){
        destrutorArvore(this->raiz);
    };

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */

    
    virtual bool vazia() const
    {
        if(this->raiz == nullptr){
            return true;
        }
        return false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    int quantidadeRecursivo(Nodo<T>* nodo) const {
        if (nodo == nullptr) {
            return 0;
        }
        return quantidadeRecursivo(nodo->filhoEsquerda) + quantidadeRecursivo(nodo->filhoDireita) + 1;
    }
    virtual int quantidade() const
    {
        return quantidadeRecursivo(this->raiz);
    };

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    bool contemRecursivo(Nodo<T>*nodo, T chave) const {
        if(nodo != nullptr){
            if(chave == nodo->chave){
                return true;
            }
            if(chave<nodo->chave){
                return contemRecursivo(nodo->filhoEsquerda,chave);
            }
            if(chave > nodo->chave){
                return contemRecursivo(nodo->filhoDireita,chave);
            }
        }
        return false;
    }
    virtual bool contem(T chave) const
    {
        return contemRecursivo(this->raiz,chave);
    };

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    T calcularMaximo(T alturaEsquerda, T alturaDireita) const {
        if(alturaEsquerda > alturaDireita){
            return alturaEsquerda;
        }
        else{
            return alturaDireita;
        }
    }
    std::optional<int>alturaRecursiva(Nodo<T>*nodo, T chave) const {
        if (nodo == nullptr) {
            return std::nullopt;
        }
        if (nodo->chave == chave) {
            return calcularAltura(nodo);
        }   
    std::optional<int>alturaEsquerda = alturaRecursiva(nodo->filhoEsquerda, chave);
        if (alturaEsquerda) {
            return alturaEsquerda;
        }
        return alturaRecursiva(nodo->filhoDireita, chave);
    }

    int calcularAltura(Nodo<T>* nodo) const {
        if (nodo == nullptr) {
            return -1;
        }
        int alturaEsquerda = calcularAltura(nodo->filhoEsquerda);
        int alturaDireita = calcularAltura(nodo->filhoDireita);
        return 1 + calcularMaximo(alturaEsquerda, alturaDireita);
    }

    virtual std::optional<int>altura(T chave) const
    {
        return alturaRecursiva(this->raiz,chave);
    };

    /**
     * @brief Insere uma chave na arvore    
     * @param chave chave a ser inserida
     * 
     */

    Nodo<T>*rotacaoDiretaSimples(Nodo<T>*nodo) {
        Nodo<T>*novaNodo = nodo->filhoEsquerda;
        Nodo<T>*nodoAux = novaNodo->filhoDireita;

        novaNodo->filhoDireita = nodo;
        nodo->filhoEsquerda = nodoAux;

        novaNodo->altura = calcularMaximo(calcularAltura(novaNodo->filhoEsquerda), calcularAltura(novaNodo->filhoDireita)) + 1;
        nodo->altura = calcularMaximo(calcularAltura(nodo->filhoEsquerda), calcularAltura(nodo->filhoDireita)) + 1;

        return novaNodo;
    }
    Nodo<T>*rotacaoEsquerdaSimples(Nodo<T>*nodo){
        Nodo<T>*novoNodo = nodo->filhoDireita;
        Nodo<T>*nodoAux = novoNodo->filhoEsquerda;

        novoNodo->filhoEsquerda = nodo;
        nodo->filhoDireita = nodoAux;
        
        nodo->altura = calcularMaximo(calcularAltura(nodo->filhoEsquerda), calcularAltura(nodo->filhoDireita)) + 1;
        novoNodo->altura = calcularMaximo(calcularAltura(novoNodo->filhoEsquerda), calcularAltura(novoNodo->filhoDireita)) + 1;

        return novoNodo;
    }
    T calcularBalanceamento(Nodo<T>*nodo) const{
        if(nodo==nullptr){
            return 0;
        }
        return calcularAltura(nodo->filhoEsquerda) - calcularAltura(nodo->filhoDireita); 
    }

    Nodo<T>*balancearNodo(Nodo<T>*nodo) {
        int fatorBalanceamento = calcularBalanceamento(nodo);

        if (fatorBalanceamento > 1 && calcularBalanceamento(nodo->filhoEsquerda) >= 0) {
            return rotacaoDiretaSimples(nodo);
        }
        if (fatorBalanceamento < -1 && calcularBalanceamento(nodo->filhoDireita) <= 0) {
            return rotacaoEsquerdaSimples(nodo);
        }
        if (fatorBalanceamento > 1 && calcularBalanceamento(nodo->filhoEsquerda) < 0) {
            nodo->filhoEsquerda = rotacaoEsquerdaSimples(nodo->filhoEsquerda);
            return rotacaoDiretaSimples(nodo);
        }
        if (fatorBalanceamento < -1 && calcularBalanceamento(nodo->filhoDireita) > 0) {
            nodo->filhoDireita = rotacaoDiretaSimples(nodo->filhoDireita);
            return rotacaoEsquerdaSimples(nodo);
        }
        return nodo;
    }
    

    Nodo<T>*inserirRecursivo(Nodo<T>*nodo,T chave){
        if(nodo == nullptr){
            return new Nodo<T>{chave};
        }
        if(chave < nodo->chave){
            nodo->filhoEsquerda = inserirRecursivo(nodo->filhoEsquerda, chave);            
        }
        if(chave > nodo->chave){
            nodo->filhoDireita = inserirRecursivo(nodo->filhoDireita, chave);   
        }
        
        nodo->altura = calcularMaximo(calcularAltura(nodo->filhoEsquerda), calcularAltura(nodo->filhoDireita)) + 1;

        return balancearNodo(nodo);
    }
    virtual void inserir(T chave){
        this->raiz = inserirRecursivo(this->raiz,chave);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */

    Nodo<T>* nodoMinimo(Nodo<T>* nodo) {
        Nodo<T>*nodoAux = nodo;
        while (nodoAux->filhoEsquerda != nullptr) {
            nodoAux = nodoAux->filhoEsquerda;
        }
        return nodoAux;
    }

    Nodo<T>*removerRecursivo(Nodo<T>*nodo, T chave) {
        if (nodo == nullptr) {
            return nodo;
        }
        if (chave < nodo->chave) {
            nodo->filhoEsquerda = removerRecursivo(nodo->filhoEsquerda, chave);
        } else if (chave > nodo->chave) {
            nodo->filhoDireita = removerRecursivo(nodo->filhoDireita, chave);
        } else {
            if(nodo->filhoEsquerda == nullptr){
                Nodo<T>* noduAux = nodo->filhoDireita;
                delete nodo;
                return noduAux;
            }else if(nodo->filhoDireita == nullptr){
                Nodo<T>*noduAux = nodo->filhoEsquerda;
                delete nodo;
                return noduAux;
            }
            else {
                Nodo<T>*nodoAux = nodoMinimo(nodo->filhoDireita);
                nodo->chave = nodoAux->chave;
                nodo->filhoDireita = removerRecursivo(nodo->filhoDireita, nodo->chave);
            }
        }
        if (nodo == nullptr) {
            return nodo;
        }

        nodo->altura = calcularMaximo(calcularAltura(nodo->filhoEsquerda), calcularAltura(nodo->filhoDireita)) + 1;
        
        return balancearNodo(nodo);
    }

    virtual void remover(T chave){
        this->raiz = removerRecursivo(this->raiz, chave);
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<T>filhoEsquerdaDeRecursivo(Nodo<T>*nodo, T chave) const {
        if (nodo == nullptr) {
            return std::nullopt;
        }
        if (chave == nodo->chave) {
            if (nodo->filhoEsquerda != nullptr) {
                return nodo->filhoEsquerda->chave;
            } else {
                return std::nullopt;
            }
        } 
        if (chave < nodo->chave) {
            return filhoEsquerdaDeRecursivo(nodo->filhoEsquerda, chave);
        } else {
            return filhoEsquerdaDeRecursivo(nodo->filhoDireita, chave);
        }
    }
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        return filhoEsquerdaDeRecursivo(this->raiz,chave);
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     * 
     */
    
    std::optional<T>filhoDireitaDeRecursivo(Nodo<T>*nodo, T chave) const {
        if (nodo == nullptr) {
            return std::nullopt;
        }
        if (chave == nodo->chave) {
            if (nodo->filhoDireita != nullptr) {
                return nodo->filhoDireita->chave;
            } else {
                return std::nullopt; 
            }
        } 
        else if(chave< nodo->chave){
            return filhoDireitaDeRecursivo(nodo->filhoEsquerda,chave);
        }
        else{
            return filhoDireitaDeRecursivo(nodo->filhoDireita,chave);

        }
        return std::nullopt;
    }
    virtual std::optional<T>filhoDireitaDe(T chave) const
    {
        return filhoDireitaDeRecursivo(this->raiz,chave);
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    MinhaListaEncadeada<T>*emOrdemRecursivo(Nodo<T>*nodo,MinhaListaEncadeada<T>*listaEmOrdem) const {
        if(nodo!=nullptr){
            emOrdemRecursivo(nodo->filhoDireita,listaEmOrdem);
            listaEmOrdem->inserirNoInicio(nodo->chave);
            emOrdemRecursivo(nodo->filhoEsquerda,listaEmOrdem);
        }
        return listaEmOrdem;
    }

    virtual ListaEncadeadaAbstrata<T>*emOrdem() const
    {
        MinhaListaEncadeada<T>*listaEmOrdem = new MinhaListaEncadeada<T>();
        return emOrdemRecursivo(this->raiz,listaEmOrdem);
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    MinhaListaEncadeada<T>*preOrdemRecursivo(Nodo<T>*nodo,MinhaListaEncadeada<T>*listaPreOrdem) const {
        if(nodo!=nullptr){
            preOrdemRecursivo(nodo->filhoDireita,listaPreOrdem);
            preOrdemRecursivo(nodo->filhoEsquerda,listaPreOrdem);
            listaPreOrdem->inserirNoInicio(nodo->chave);
        }
        return listaPreOrdem;
    }
    virtual ListaEncadeadaAbstrata<T>*preOrdem() const
    {
        MinhaListaEncadeada<T>*listaPreOrdem = new MinhaListaEncadeada<T>();
        return preOrdemRecursivo(this->raiz,listaPreOrdem);
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    MinhaListaEncadeada<T>*posOrdemRecursivo(Nodo<T>*nodo,MinhaListaEncadeada<T>*listaPosOrdem) const {
        if(nodo!=nullptr){
            listaPosOrdem->inserirNoInicio(nodo->chave);
            posOrdemRecursivo(nodo->filhoDireita,listaPosOrdem);
            posOrdemRecursivo(nodo->filhoEsquerda,listaPosOrdem);
        }
        return listaPosOrdem;
    }
    virtual ListaEncadeadaAbstrata<T>*posOrdem() const
    {
        MinhaListaEncadeada<T>*listaPosOrdem = new MinhaListaEncadeada<T>();
        return posOrdemRecursivo(this->raiz,listaPosOrdem);        
    };
};

#endif