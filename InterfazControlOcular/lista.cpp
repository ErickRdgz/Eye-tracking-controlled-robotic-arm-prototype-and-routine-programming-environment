#include "lista.h"
#include <iostream>
#include <QDebug>
template<typename D>
Lista<D>::Lista()
{
    this->head=nullptr;
    this->size=0;
}

template<typename D>
void Lista<D>::clear()
{
    if(!this->empty()){
        Nodo<D>* actual=this->head->getNext();
        while (actual->getNext()) {
          Nodo<D>* anterior=actual;
          actual=actual->getNext();
          anterior->setNext(nullptr);
          delete anterior;
        }
        delete actual;
        this->head->setNext(nullptr);
        this->head=nullptr;
        this->size=0;
    }
}

template<typename D>
bool Lista<D>::empty()
{
    if(this->head==nullptr){
        return true;
    }else{
        return false;
    }
}

template<typename D>
int Lista<D>::getSize()
{
    return this->size;
}





template <typename D>
Nodo<D> *Lista<D>::getHead()
{
    return this->head;
}
template <typename D>
void Lista<D>::setHead(Nodo<D> *head)
{
    this->head=head;
}

template<typename D>
void Lista<D>::push_front(D dato)
{
    Nodo<D>* nuevoNodo= new Nodo<D>(dato,this->head);
    this->head=nuevoNodo;
    this->size++;
}

template<typename D>
bool Lista<D>::pop_front()
{
    if(!this->empty()){
        Nodo<D>* actual=this->head;
        this->head=this->head->getNext();
        actual->setNext(nullptr);
        delete actual;
        this->size--;
        return true;
    }
    return false;
}

template<typename D>
Nodo<D> *Lista<D>::point_at(int position)
{
    if(this->empty()) return nullptr;
    else{
        Nodo<D>* actual=this->head;
        for(int i=0;i<position;i++){
            actual=actual->getNext();
        }
        return  actual;
    }
}

template<typename D>
Nodo<D> *Lista<D>::getPointerBack()
{
    if(this->empty()) return nullptr;
    else{
        Nodo<D>* actual=this->head;
        while (actual->getNext()!=nullptr) {
            actual=actual->getNext();
        }
        return  actual;

    }
}


template<typename D>
bool Lista<D>::push_back(D data)
{
    Nodo<D>* nuevoNodo=nullptr;
    try {
         nuevoNodo= new Nodo<D>(data,nullptr);
    } catch (std::bad_alloc &e) {
        throw ListException(ExceptionCodes::ERROR_MEMORIA);
    } catch(...){
        throw ListException(ExceptionCodes::DESCONOCIDO);
    }

    if (this->empty()){
        this->head=nuevoNodo;
    }else{
        Nodo<D>* actual=getPointerBack();
        actual->setNext(nuevoNodo);
    }
    this->size++;
    return 1;
}

template<typename D>
bool Lista<D>::pop_back()
{
    if(!this->empty()){
        Nodo<D>* actual=this->head;
        Nodo<D>* anterior=nullptr;
        while (actual->getNext()) {
            anterior=actual;
            actual=actual->getNext();
        }
        if(actual==this->head){
            this->head=this->head->getNext();
            delete actual;
            this->size--;
        }else{
            anterior->setNext(nullptr);
            delete actual;
            this->size--;
        }
        return true;
    }
    return false;
}

template<typename D>
bool Lista<D>::insert(D data, int position)
{
    if(position<0||position>this->size)
        throw ListException(ExceptionCodes::POSICION_INVALIDA);

    if(position==0){
        try {
            push_front(data);
            return  true;
        } catch (ListException &e) {
            throw  e.what();
        }

    }
    if(position==this->size){
        try {
            push_back(data);
            return  true;
        } catch (ListException &e) {
            throw  e.what();
        }
    }

    Nodo<D>* anterior=this->point_at(position-1);
    Nodo<D>* nuevoNodo=nullptr;
    try {
        nuevoNodo= new Nodo<D>(data,anterior->getNext());
    } catch (std::bad_alloc &e) {
        throw ListException(ExceptionCodes::ERROR_MEMORIA);
    } catch(...){
        throw ListException(ExceptionCodes::DESCONOCIDO);
    }
    anterior->setNext(nuevoNodo);
    this->size++;
    return 1;
}

template<typename D>
bool Lista<D>::errase(int position)
{
    if(this->empty())
        throw ListException(ExceptionCodes::LISTA_VACIA);
    if(position<0||position>this->size)
        throw ListException(ExceptionCodes::POSICION_INVALIDA);

    if(position==0){
        this->pop_front();
        return 1;
    }
    if(position== this->size){
        this->pop_back();
        return 1;
    }

    Nodo<D>* anterior=this->point_at(position-1);
    Nodo<D>* actual=anterior->getNext();
    anterior->setNext(actual->getNext());
    actual->setNext(nullptr);
    delete actual;
    this->size--;
    return 1;
}

template<typename D>
bool Lista<D>::repleace(D newData, int position)
{
    if(this->empty())
        throw ListException(ExceptionCodes::LISTA_VACIA);
    if(position<0||position>this->size)
        throw ListException(ExceptionCodes::POSICION_INVALIDA);

    Nodo<D>* actual=this->point_at(position);
    actual->setDato(newData);
    return 1;
}

template<typename D>
D Lista<D>::front()
{
    if(!this->empty()){
        Nodo<D>* actual=this->head;
        return actual->getDato();
    }else{
        throw ListException(ExceptionCodes::LISTA_VACIA);
    }
}

template<typename D>
D Lista<D>::back()
{
    if(!this->empty()){
        Nodo<D>* actual=this->getPointerBack();
        return actual->getDato();
    }else{
        throw ListException(ExceptionCodes::LISTA_VACIA);
    }
}

template<typename D>
D Lista<D>::at(int position)
{
    if(this->empty())
        throw ListException(ExceptionCodes::LISTA_VACIA);
    if(position<0||position>=this->size)
        throw ListException(ExceptionCodes::POSICION_INVALIDA);

    if(position==0)
        return this->front();

    if(position== this->size-1)
       return this->getPointerBack()->getDato();

    return this->point_at(position)->getDato();
}

template<typename D>
D Lista<D>::getItem(QString data, bool (*Search)(D, QString ))
{
    if(this->empty())                                     //si la lista esta vacia, no busca
        throw ListException(ExceptionCodes::LISTA_VACIA);

    Nodo<D>* actual=this->head;
    for(int i=0;i<this->size;i++){
        if(Search(actual->getDato(),data))
            return actual->getDato();
        actual=actual->getNext();
    }
    throw ListException(ExceptionCodes::NO_EXISTE);// recorre todo el arreglo y no encuentra nada
}




template<typename D>
void Lista<D>::PrintList(QString(*imprimeElemento)(D))
{
    if(this->empty()){
        throw ListException(ExceptionCodes::LISTA_VACIA);
    }
    Nodo<D>* actual=this->head;
    for(int i=0;i<this->size;i++){
        qDebug()<<"  "<<i<<") "<<imprimeElemento(actual->getDato());
        actual=actual->getNext();
    }
}






template<typename D>
Nodo<D>::Nodo(D dato, Nodo<D> *next)
{
            this->dato= dato;
            this->next=next;
}


template class Lista<Command>;
template class Lista<Point>;

template  class Nodo<Command>;
template  class Nodo<Point>;
