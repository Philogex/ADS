#include "List.h"
#include <iostream>
List::List()
{
/* 
    Konstruktor für eine leere Liste 
*/
    m_head_tail       = new Node;
    m_list_size       = 0;
    m_temp            = false;
    m_head_tail->next = m_head_tail;
    m_head_tail->prev = m_head_tail;
}

List::List(const List& _List)
{
/*  
    Konstruktor mit Übergabe einer Liste, die dann kopiert wird. 
    in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    sollen.
*/
    list_form       = _List.list_form;
    m_head_tail       = new Node;
    m_list_size       = 0;
    m_temp            = _List.m_temp;
    m_head_tail->next = m_head_tail;        
    m_head_tail->prev = m_head_tail;
    Node* tmp_node;
    tmp_node = _List.m_head_tail->next;
    while (tmp_node != _List.m_head_tail)
    {
        m_head_tail->prev =
            new Node(tmp_node->value, m_head_tail->prev->next, m_head_tail->prev);
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

List::~List()
{
    //ToDo
/*
    Dekonstruktor
    Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
*/
    if(m_head_tail == nullptr) return;

    if(m_head_tail->prev != m_head_tail) {
        Node* tmp = m_head_tail->next;
        Node* prev = nullptr;
        while (tmp != m_head_tail) {
            prev = tmp;
            tmp = tmp->next;
            delete prev;
        }
    }
    
    delete m_head_tail;
}

void List::insertFront(int value)
{
    //ToDo
/*
    Einfuegen eines neuen Knotens am Anfang der Liste
	Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
*/
    Node* new_node = new Node(value, m_head_tail->next, m_head_tail);
    m_head_tail->next->prev = new_node;
    m_head_tail->next = new_node;
    m_list_size++;
}

void List::insertFront(List& _List)
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

void List::insertBack(int value)
{
    //ToDo
/*
	Einfuegen eines neuen Knotens am Ende der Liste
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
*/
    Node* new_node = new Node(value, m_head_tail, m_head_tail->prev);
    m_head_tail->prev->next = new_node;
    m_head_tail->prev = new_node;
    m_list_size++;
}

void List::insertBack(List& _List)
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

bool List::getFront(int& value)
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
    Node* tmp = m_head_tail->next;

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

bool List::getBack(int& value)
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
    Node* tmp = m_head_tail->prev;

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

bool List::del(int value)
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

    Node* tmp = m_head_tail->next;
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

bool List::search(int value)
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

    Node* tmp = m_head_tail->next;
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

bool List::swap(int value1, int value2)
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

    Node *val1 = nullptr; 
    Node *val2 = nullptr;

    Node* tmp = m_head_tail->next;
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
        Node* tmp = new Node(0, val1->next, val1->prev);

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

int List::size(void)
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

bool List::test(void)
{
    // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
    // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
    // der Knoten überein liefert die Methode true
    Node* tmp    = m_head_tail->next;
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

List& List::operator=(const List& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node* tmp_node;
    if (m_list_size)
    {
        Node* tmp_del;
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

List& List::operator+(const List& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node* tmp_node;
    List* tmp;
    if (m_temp)
    { // this ist eine m_temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List(*this); // this ist keine m_temporäre Liste -> Kopie erzeugen
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

void List::format(const std::string& start,
                  const std::string& zwischen,
                  const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start    = start;
    list_form.zwischen = zwischen;
    list_form.ende     = ende;
}

std::ostream& operator<<(std::ostream& stream, List const& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node* tmp = Liste.m_head_tail->next; tmp != Liste.m_head_tail;
         tmp       = tmp->next)
        stream << tmp->value
               << (tmp->next == Liste.m_head_tail ? Liste.list_form.ende :
                                                  Liste.list_form.zwischen);
    if (Liste.m_temp)
        delete &Liste; // wurde eine m_temporäre Liste übergeben, dann wird diese
                       // gelöscht
    return stream;
}
