#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <iostream>
#include <string>

template <typename T>
class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
    List kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        std::string start    = "<< ";
        std::string zwischen = ", ";
        std::string ende     = " >>\n";
    } list_form;
    Node<T>* m_head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
                     // -> prev der letzte Knoten
    int  m_list_size;  // Länge der Kette
    bool m_temp; // normalerweise false; ist true, wenn es sich um eine temor�re
               // Liste handelt die innerhalb der überladenen Operatoren
               // angelegt wird
public:
    List();
    List(const List<T>& _List); // Kopie Konstruktor
    ~List();
    void insertFront(T value);     // Einfügen eines Knotens am Anfang
    void insertFront(List<T>& _List); // Einfügen einer vorhandenen Liste am Anfang
    void insertBack(T value);      // Einfügen eines Knotesn am Ende
    void insertBack(List<T>& _List);  // Einfügen einer vorhandenen Liste am Ende
    bool getFront(T& value);       // Entnehmen eines Knoten am Anfang
    bool getBack(T& value);        // Entnehmen eines Knoten am Ende
    bool del(T value);             // löschen eines Knotens [key]
    bool search(T value);          // Suchen eines Knoten
    bool swap(T value1, T value2); // Knoten in der Liste vertauschen
    int  size(void);               // Größe der Lise (Anzahl der Knoten)
    bool test(void);               // Überprüfen der Zeigerstruktur der Liste
    void format(const std::string& start,
                const std::string& zwischen,
                const std::string& ende);
    // Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
    // start: stirng vor der Ausgabe der Liste
    // zwischen: string zwischen Listenknoten
    // ende: string am Ende der Liste
    List<T>& operator=(const List<T>& _List); // Zuweisungsoperator definieren
    List<T>&
    operator+(const List<T>& List_Append); // Listen zusammenführen zu einer Liste
    template <typename Tf>
    friend std::ostream & operator << (std::ostream & stream, const List<Tf> & Liste); // Ausgabeoperator überladen
    friend Node<T>* get_anker(List<T>& l);
    friend int   get_AnzahlNodes(List<T>& l);
};
#endif

template <typename T>
List<T>::List()
{
/* 
    Konstruktor für eine leere Liste 
*/
    m_head_tail       = new Node<T>;
    m_list_size       = 0;
    m_temp            = false;
    m_head_tail->next = m_head_tail;
    m_head_tail->prev = m_head_tail;
}


template <typename T>
List<T>::List(const List<T>& _List)
{
/*  
    Konstruktor mit Übergabe einer Liste, die dann kopiert wird. 
    in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    sollen.
*/
    list_form       = _List.list_form;
    m_head_tail       = new Node<T>;
    m_list_size       = 0;
    m_temp            = _List.m_temp;
    m_head_tail->next = m_head_tail;        
    m_head_tail->prev = m_head_tail;
    Node<T>* tmp_node;
    tmp_node = _List.m_head_tail->next;
    while (tmp_node != _List.m_head_tail)
    {
        m_head_tail->prev =
            new Node<T>(tmp_node->value, m_head_tail->prev->next, m_head_tail->prev);
        m_head_tail->prev->prev->next = m_head_tail->prev;
        m_list_size++;
        tmp_node = tmp_node->next;
    }
/*  
    Ist die übergebene Liste eine m_temporäre Liste? -> aus Operator +
*/
    if (_List.m_temp)
        delete &_List; 
}

template <typename T>
List<T>::~List()
{
    //ToDo
/*
    Dekonstruktor
    Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
*/
    if(m_head_tail == nullptr) return;

    if(m_head_tail->prev != m_head_tail) {
        Node<T>* tmp = m_head_tail->next;
        Node<T>* prev = nullptr;
        while (tmp != m_head_tail) {
            prev = tmp;
            tmp = tmp->next;
            delete prev;
        }
    }
    
    delete m_head_tail;
}

template <typename T>
void List<T>::insertFront(T value)
{
    //ToDo
/*
    Einfuegen eines neuen Knotens am Anfang der Liste
	Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
*/
    Node<T>* new_node = new Node<T>(value, m_head_tail->next, m_head_tail);
    m_head_tail->next->prev = new_node;
    m_head_tail->next = new_node;
    m_list_size++;
}

template <typename T>
void List<T>::insertFront(List<T>& _List)
{
    //ToDo
/*	
    Einfuegen der Liste _List am Anfang an einer vorhandenen Liste
	Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
	Die einzufuegende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
*/
/*
    gleiches Objekt -> keine Aktion
*/ 
	if (m_head_tail == _List.m_head_tail) return;
    if(_List.m_head_tail->prev == _List.m_head_tail) return;
    
    this->m_head_tail->next->prev = _List.m_head_tail->prev;
    _List.m_head_tail->prev->next = this->m_head_tail->next;

    this->m_head_tail->next = _List.m_head_tail->next;
    _List.m_head_tail->next->prev = this->m_head_tail;

    this->m_list_size += _List.m_list_size;
    _List.m_list_size = 0;
    delete _List.m_head_tail;
    _List.m_head_tail = nullptr;

/*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
	Die Liste _List ist danach leer, aber vorhanden.
*/
    
}

template <typename T>
void List<T>::insertBack(T value)
{
    //ToDo
/*
	Einfuegen eines neuen Knotens am Ende der Liste
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
*/
    Node<T>* new_node = new Node<T>(value, m_head_tail, m_head_tail->prev);
    m_head_tail->prev->next = new_node;
    m_head_tail->prev = new_node;
    m_list_size++;
}

template <typename T>
void List<T>::insertBack(List<T>& _List)
{
    //ToDo
/*
    Einfuegen der Liste _List am Ende einer vorhandenen Liste
	Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
	Die einzufuegende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
*/
/*
    gleiches Objekt -> keine Aktion
*/
	if (m_head_tail == _List.m_head_tail) return;
    if(_List.m_head_tail->prev == _List.m_head_tail) return;
    
    this->m_head_tail->prev->next = _List.m_head_tail->next;
    _List.m_head_tail->next->prev = this->m_head_tail->prev;

    this->m_head_tail->prev = _List.m_head_tail->prev;
    _List.m_head_tail->prev->next = this->m_head_tail;

    this->m_list_size += _List.m_list_size;
    _List.m_list_size = 0;
    delete _List.m_head_tail;
    _List.m_head_tail = nullptr;

/*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
	Die Liste _List ist danach leer, aber vorhanden.
*/
    
}

template <typename T>
bool List<T>::getFront(T& value)
{
    //ToDo
/*  
    entnehmen des Knotens am Anfang der Liste
	der Wert wird als Parameter zurueckgegeben
	der Knoten wird entnommen
	im Fehlerfall wird false zurückgegeben
*/
/*
    gleiches Objekt -> keine Aktion
*/
	if (!m_list_size) return false;	

    value = m_head_tail->next->value;
    Node<T>* tmp = m_head_tail->next;

    m_head_tail->next = tmp->next;
    tmp->next->prev = m_head_tail;

    delete tmp;
    m_list_size--;
    return true;

/*
	Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
	Die Methode del(value) darf nicht zum löschen benutzt werden.
*/
    
}

template <typename T>
bool List<T>::getBack(T& value)
{ 
    //ToDo
/*  
    entnehmen des Knotens am Ende der Liste
	der Wert wird als Parameter zurueckgegeben
	der Knoten wird entnommen
	im Fehlerfall wird false zurückgegeben
*/
/*
    gleiches Objekt -> keine Aktion
*/
	if (!m_list_size) return false;

    value = m_head_tail->prev->value;
    Node<T>* tmp = m_head_tail->prev;

    m_head_tail->prev = tmp->prev;
    tmp->prev->next = m_head_tail;

    delete tmp;
    m_list_size--;
    return true;

/*
	Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
	Die Methode del(value) darf nicht zum löschen benutzt werden.
*/
    
}

template <typename T>
bool List<T>::del(T value)
{
    //ToDo
/*  
    Loeschen eines gegebenen Knotens
	im Fehlerfall wird false zurückgegeben
*/
/*
    gleiches Objekt -> keine Aktion
*/
	if (!m_list_size) return false;

    Node<T>* tmp = m_head_tail->next;
    while(tmp != m_head_tail){
        if(tmp->value == value){
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp;
            m_list_size--;
            return true;
        }
        tmp = tmp->next;

    }

    return false;

/*
	Löschen des Knotens mit dem Wert value 
*/
    
}

template <typename T>
bool List<T>::search(T value)
{
    //ToDo
/*
    suchen eines Knotens
	nicht gefunden -> Rueckgabe: false
*/
/*
    leere Liste -> keine Aktion
*/
	if (!m_list_size) return false;

    Node<T>* tmp = m_head_tail->next;
    while(tmp != m_head_tail){
        if(tmp->value == value){
            return true;
        }
        tmp = tmp->next;
    }

    return false;


/*
	suchen ob ein Knoten mit dem Wert value existiert.
*/
    
}

template <typename T>
bool List<T>::swap(T value1, T value2)
{
    //ToDo
/*  
    Vertauschen von zwei Knoten
	Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
	im Fehlerfall wird false zurueckgegeben
*/
/*  
    Wenn Liste Leer oder weniger als 2 Knoten besitzt -> Keine Aktion
*/
	if (m_list_size < 2) return false; 

    Node<T> *val1 = nullptr; 
    Node<T> *val2 = nullptr;

    Node<T>* tmp = m_head_tail->next;
    while(tmp != m_head_tail){
        if(tmp->value == value1 && val1 == nullptr){
            val1 = tmp;
        }
        if(tmp->value == value2 && val2 == nullptr) {
            val2 = tmp;
        }

        tmp = tmp->next;
    }


    if(val1 == nullptr || val2 == nullptr) { return false; }
    if(val1->next == val2) {
        val1->prev->next = val2;
        val2->next->prev = val1;
        val1->next = val2->next;
        val2->prev = val1->prev;
        val2->next = val1;
        val1->prev = val2;
    }
    else if(val2->next == val1) {
        val2->prev->next = val1;
        val1->next->prev = val2;
        val2->next = val1->next;
        val1->prev = val2->prev;
        val1->next = val2;
        val2->prev = val1;
    }
    else {
        Node<T>* tmp = new Node<T>(0, val1->next, val1->prev);

        val1->prev = val2->prev;
        val2->prev->next = val1;
        val1->next = val2->next;
        val2->next->prev = val1;

        val2->prev = tmp->prev;
        tmp->prev->next = val2;
        val2->next = tmp->next;
        tmp->next->prev = val2;
        
        delete tmp;
    }

/*
	Vertauschen von zwei Knoten mit dem Wert value1 und dem Wert value2.
	Es duerfen nicht nur einfach die Werte in den Knoten getauscht werden!
	Die Knoten sind in der Kette umzuhaengen.
*/
    return true;
}

template <typename T>
int List<T>::size(void)
{
    //ToDo
/*  
    Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
    d.h. die Liste darf NICHT traversiert werden um die Größe zu bestimmen.

	Anzahl der Knoten in der Liste zurückgeben.
    Hier richtiges Ergebnis zurückgeben
*/
	return m_list_size;
}

template <typename T>
bool List<T>::test(void)
{
    // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
    // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
    // der Knoten überein liefert die Methode true
    Node<T>* tmp = m_head_tail->next;
    int   i_next = 0, i_prev = 0;
    while (tmp != m_head_tail)
    {
        tmp = tmp->next;
        if (i_next > m_list_size)
            return false;
        i_next++;
    }
    if (i_next != m_list_size)
        return false;
    tmp = m_head_tail->prev;
    while (tmp != m_head_tail)
    {
        tmp = tmp->prev;
        if (i_prev > m_list_size)
            return false;
        i_prev++;
    }
    return i_prev == i_next;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node<T>* tmp_node;
    if (m_list_size)
    {
        Node<T>* tmp_del;
        tmp_node = m_head_tail->next;
        while (tmp_node !=
               m_head_tail) // Alle eventuell vorhandenen Knoten in this löschen
        {
            tmp_del  = tmp_node;
            tmp_node = tmp_node->next;
            delete tmp_del;
        }
        m_list_size       = 0;
        m_head_tail->next = m_head_tail;
        m_head_tail->prev = m_head_tail;
    }
    tmp_node = _List.m_head_tail->next; // Die Listen-Knotenwerte werden kopiert
    while (tmp_node != _List.m_head_tail)
    {
        insertBack(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    if (_List.m_temp)
        delete &_List; // ist die übergebene Liste eine m_temporäre Liste? -> aus
                       // Operator +
    return *this;
}

template <typename T>
List<T>& List<T>::operator+(const List<T>& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node<T>* tmp_node;
    List<T>* tmp;
    if (m_temp)
    { // this ist eine m_temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List<T>(*this); // this ist keine m_temporäre Liste -> Kopie erzeugen
        tmp->m_temp = true;    // Merker setzten, dass es sich um eine m_temporäre
                             // Liste handelt
    }
    if (List_Append.m_list_size)
    { // anhängen der übergebenen Liste an tmp
        tmp_node = List_Append.m_head_tail->next;
        while (tmp_node != List_Append.m_head_tail)
        {
            tmp->insertBack(tmp_node->value);
            tmp_node = tmp_node->next;
        }
    }
    if (List_Append.m_temp)
        delete &List_Append; // wurde eine m_temporäre Liste übergeben, dann wird
                             // diese gelöscht
    return *tmp;
}

template <typename T>
void List<T>::format(const std::string& start,
                  const std::string& zwischen,
                  const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start    = start;
    list_form.zwischen = zwischen;
    list_form.ende     = ende;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, List<T> const& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node<T>* tmp = Liste.m_head_tail->next; tmp != Liste.m_head_tail;
         tmp       = tmp->next)
        stream << tmp->value
               << (tmp->next == Liste.m_head_tail ? Liste.list_form.ende :
                                                  Liste.list_form.zwischen);
    if (Liste.m_temp)
        delete &Liste; // wurde eine m_temporäre Liste übergeben, dann wird diese
                       // gelöscht
    return stream;
}