#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.h"


template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada(){
        
        Elemento<T>*indice = this->_primeiro;
        Elemento<T>*anterior = nullptr;

        while(indice != nullptr){
            anterior = indice;
            indice = indice->proximo;
            delete anterior;
            this->_tamanho--;
        }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };
    
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const 
    {  
        return this->_tamanho == 0;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const 
    {
        Elemento<T>*indice = this->_primeiro;

        if(indice == nullptr){
            throw ExcecaoListaEncadeadaVazia();
        }
        
        int posicao = 0;
        while(indice != nullptr){
            if(indice->dado == dado){
                return posicao;
            }
            indice = indice->proximo;
            posicao++;
        }
        throw ExcecaoDadoInexistente();
    };
    
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        Elemento<T>*indice= this->_primeiro;
        
        while(indice != nullptr){
            if(indice->dado == dado){
                return true;
            }
            indice = indice->proximo;
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    public:
    virtual void inserirNoInicio(T dado) 
    {
        Elemento<T>*novoPtr = new Elemento<T>(dado);
        novoPtr->proximo = this->_primeiro;
        this->_primeiro = novoPtr;
        this->_tamanho++;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        if(posicao>this->_tamanho){
            throw ExcecaoPosicaoInvalida();
        }
        
        Elemento<T>*novoPtr = new Elemento<T>(dado);
        Elemento<T>*indice = this->_primeiro;
        Elemento<T>*anterior = nullptr;
        
        if(posicao == 0){
            novoPtr->proximo = this->_primeiro;
            this->_primeiro = novoPtr;
            this->_tamanho++;
        }
        else if(posicao == this->_tamanho-1){
            for(int i=0;i = posicao;i++){
                indice = indice->proximo;
            }
            indice->proximo = novoPtr;
            novoPtr->proximo = nullptr;
            this->_tamanho++;
        }
        else{
            for(int i = 0;i<posicao;i++){
                anterior = indice;
                indice = indice->proximo;
            }
            novoPtr->proximo = indice;
            anterior->proximo = novoPtr;
            this->_tamanho++;
        }
    };


    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        Elemento<T>*novoPtr = new Elemento<T>(dado);
        Elemento<T>*indice = this->_primeiro;

        if(indice == nullptr){
            this->_primeiro = novoPtr;
            novoPtr->proximo = nullptr;
        }
        else{
        while(indice->proximo != nullptr){
            indice = indice->proximo;
        }
            indice->proximo = novoPtr;
            novoPtr->proximo = nullptr;
        }
        this->_tamanho++;
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        Elemento<T>*indice = this->_primeiro;

        if(indice == nullptr){
            throw ExcecaoListaEncadeadaVazia();
        }
        this->_primeiro = indice->proximo;
        T valor = indice->dado;
        delete indice;
        this->_tamanho--;
        return valor;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        if(posicao>=this->_tamanho){
            throw ExcecaoPosicaoInvalida();
        }
        
        Elemento<T>*indice = this->_primeiro;
        Elemento<T>*anterior = nullptr;
        
        if(posicao == 0){
            this->_primeiro = indice->proximo;
            T valor = indice->dado;
            delete indice;
            this->_tamanho--;
            return valor;
        }
        else if(posicao == this->_tamanho){
            for(int i=0;i < posicao;i++){
                anterior = indice;
                indice = indice->proximo;
            }
            anterior->proximo = nullptr;
            T valor = indice->dado;
            delete indice;
            this->_tamanho--;
            return valor;
        }
        else{
            for(int i = 0;i<posicao;i++){
                anterior = indice;
                indice = indice->proximo;
            }
            anterior->proximo = indice->proximo;
            T valor = indice->dado;
            delete indice;
            this->_tamanho--;
            return valor;
        }
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        Elemento<T>*indice = this->_primeiro;
        Elemento<T>*anterior = nullptr;

        if(indice == nullptr){
            throw ExcecaoListaEncadeadaVazia();
            return 0;
        }
        else if(indice->proximo == nullptr){
            this->_primeiro = nullptr;
            T valor = indice->dado;
            delete indice;
            this->_tamanho--;
            return valor;
        }
        else{
        while(indice->proximo != nullptr){
            anterior = indice;
            indice = indice->proximo;
        }
            anterior->proximo = nullptr;
            T valor = indice->dado;
            delete indice;
            this->_tamanho--;
            return valor;
        }
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        Elemento<T>*indice = this->_primeiro;
        Elemento<T>*anterior = nullptr;

        if(this->_primeiro == nullptr){
            throw ExcecaoListaEncadeadaVazia();
        }
        if (indice->dado == dado) {
            this->_primeiro = indice->proximo;
            delete indice;
            this->_tamanho--;
            return;
        }

        while(indice != nullptr){
            if(indice->dado == dado){
                anterior->proximo=indice->proximo;
                delete indice;
                this->_tamanho--;
                return;
            }            
            anterior = indice;
            indice = indice->proximo;
        }
        throw ExcecaoDadoInexistente();  
    };
};

#endif
