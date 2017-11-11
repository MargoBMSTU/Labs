#ifndef MULTIMAP_MULTIMAP_HPP
#define MULTIMAP_MULTIMAP_HPP
#define MIN(A,B) (A) < (B) ? (A) : (B)

#include <iostream>
#include <string>




template <class K, class V>
class Multimap;

template <class E>
class list{
public:
    template <class K, class V>
        friend class Multimap;
    template <class K, class V>
        friend std::ostream& operator << (std::ostream& os, Multimap<K,V> const& obj);
    list(): head(NULL){}
    ~list(){
        while (head != NULL){
            element* tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void free_list(){
        while (head != NULL){
            element* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    list(const list& other){
        head = NULL;
        element* p = other.head;
        try {
            if (p == NULL)
                throw 1;
            element *last = NULL;
            while (last != p) {
                while (p->next != last)
                    p = p->next;
                this->add(*(p->data));
                last = p;
                p = other.head;
            }
        } catch(int a){
            if (a == 1){
                head = NULL;
            }
        }
    }

    list& operator= (const list& other){
        while (head != NULL){
            element* tmp = head->next;
            delete head;
            head = tmp;
        }
        element* p = other.head;
        if (p==NULL)
            return *this;
        element* last = NULL;
        while (p != last){
            while (p->next != last)
                p = p->next;
            this->add(*(p->data));
            last = p;
            p = other.head;
        }
        return *this;
    }

    list& operator+=(const list& other){
        try {
            if (this->head == NULL)
                throw 1;
            auto p = other.head;
            while(p != NULL){
                auto p2 = this->head;
                while (p2 != NULL){
                    if (*(p2->data) == *(p->data)){
                        p = p->next;
                        break;
                    } else {
                        p2 = p2->next;
                    }
                }
                if (p2 == NULL)
                    this->add(*(p->data));
            }
        }
        catch(int a){
            if (a == 1){
                auto p = other.head;
                while(p != NULL){
                    this->add(*(p->data));
                    p = p->next;
                }
            }
        }
        return *this;
    }

    friend list operator+(list o1, const list& o2){
        return o1+=o2;
    }

    int list_size() const {
        int k = 0 ;
        auto p = this->head;
        while (p != NULL){
            ++k;
            p = p->next;
        }
        return k;
    }

    void add(const E& elem){
        element* tmp = new element(elem, head);
        head = tmp;
    }

    E* find(E elem) const {
        element* p = head;
        while(p != NULL){
            if (*(p->data) == elem)
                return p->data;
            else {p = p->next;}
        }
        return NULL;
    }

    void remove(const E& elem){
        element* p = head;
        if (p != NULL && *(p->data) == elem) {
            head = p->next;
            delete p;
            return;
        }
        while(p->next != NULL) {
            if (*(p->next->data) == elem){
                element* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            } else
                p = p->next;
        }
    }

    void show() const {
        element* tmp = head;
        while (tmp != 0){
            std::cout << *(tmp->data) << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }

    friend std::ostream& operator << (std::ostream& os, list const& obj){
        element* tmp = obj.head;
        while (tmp != 0){
            std::cout << *(tmp->data) << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
        return os;
    }

    E& operator[](const E& elem){
        try {
            E* f = this->find(elem);
            if (f != NULL)
                return *f;
            else
                throw 1;
        } catch (int a) {
            if (a == 1) {
                std::cerr << "no element: " << elem << " in list"<< std::endl;
                static E toreturn;
                return toreturn;
            }
        }
    }
    E operator[](const E& elem) const {
        try {
            E* f = this->find(elem);
            if (f != NULL)
                return *f;
            else
                throw 1;
        } catch (int a){
            if (a == 1){
                std::cerr << "no element: " << elem << " in list"<< std::endl;
                static E toreturn;
                return toreturn;
            }
        }
    }
private:
    class element{
    public:
        template <class K, class V>
            friend class Multimap;
        element() : data(NULL), next(NULL){}
        element(E elem, element* head) : data(new E(elem)) {
            next = head;
        }
        ~element(){
            delete data;
        }
        E* data;
        element* next;
    };
    element* head;
};






template <class K,class V>
class Multimap {
private: class element_multimap;
public:
    Multimap(){}
    Multimap(K key, V val){
        mas.add(element_multimap(key, val));
    }

    ~Multimap() {
    }

    Multimap& operator= (const Multimap& other){
        this->mas = other.mas;
        return *this;
    }

    void add(const K& key,const V& value){
        if (mas.head == NULL){
            mas.add(element_multimap(key, value));
            return;
        }
        auto p = mas.head;
        while (p != NULL){
            if ((p->data->key) == key) {
                p->data->val.add(value);
                return;
            }
            p = p->next;
        }
        mas.add(element_multimap(key, value));
    }

    void remove (const K key){
        auto p = mas.head;
        while (p != NULL){
            if (p->data->key == key){
                mas.remove(*(p->data));
            }
            p = p->next;
        }
    }

    element_multimap* find(const K& key) const {
        auto p = mas.head;
        try {
            while (p != NULL) {
                if (p->data->key == key) {
                    return p->data;
                }
                p = p->next;
            }
            throw 1;
        } catch(int a) {
            if (a == 1){
                std::cerr << "no such key in map: " << key << std::endl;
                return NULL;
            }

        }
    }

    void show() const {
        auto p = mas.head;
        while (p!=NULL) {
            std::cout << p->data->key << " :";
            p->data->val.show();
            p = p->next;
        }
    }

    template <class KK, class VV>
    friend std::ostream& operator <<(std::ostream& os, Multimap<KK, VV> const& obj){
        auto p = obj.mas.head;
        try {
            if (p == NULL)
                throw 1;
            while (p != NULL) {
                os << p->data->key << " :";
                p->data->val.show();
                p = p->next;
            }
            return os;
        } catch (int a){
            if (a == 1)
                return os;
        }
    }

    Multimap& operator+=(const Multimap& other){
        auto p = other.mas.head;
        try {
            if (mas.head == NULL)
                throw 1;
            if (p == NULL)
                throw 2;
            while (p != NULL) {
                auto thisp = mas.head;
                while(thisp != NULL) {
                    if (p->data->key == thisp->data->key) {
                        thisp->data->val += p->data->val;
                        break;
                    } else {
                        thisp = thisp->next;
                    }
                }
                if (thisp == NULL){
                    mas.add(element_multimap(p->data->key, p->data->val));
                }
                p = p->next;
            }
            return *this;

        } catch (int a){
            if (a == 1){
                this->mas = other.mas;
                return *this;
            }
            if (a == 2){
                return *this;
            }
        }
    }

    friend Multimap operator+(Multimap o1, const Multimap& o2){
        return o1 += o2;
    }

    Multimap& operator *= (const Multimap & other){
        auto p1 = this->mas.head;
        auto p2 = other.mas.head;
        Multimap tmp = *this;
        Multimap bigger = other;
        try {
            if (p1 == NULL)
                throw 1;
            if (p2 == NULL)
                throw 2;
            int min = MIN(this->mas.list_size(), other.mas.list_size());
            if ( this->mas.list_size() <= other.mas.list_size()){
                tmp = *this;
                bigger = other;
                p1 = tmp.mas.head;
            } else{
                tmp = other;
                bigger = *this;
                p1 = tmp.mas.head;
            }
            element_multimap* p;
            while (p1 != NULL){
                if ((p = bigger.find(p1->data->key)) != NULL){
                    auto pp = p1->data->val.head;
                    while (pp != NULL) {
                        if ( p->val.find(*(pp->data)) == NULL) {
                            auto t = pp->next;
                            p1->data->val.remove(*(pp->data));
                            pp = t;
                        } else {
                            pp = pp->next;
                        }
                    }
                    p1 = p1->next;
                } else {
                    auto t = p1->next;
                    tmp.remove(p1->data->key);
                    p1 = t;
                }
            }
            *this = tmp;
            return *this;
        } catch (int a){
            if (a == 1){
                return *this;
            }
            if (a == 2){
                this->mas.free_list();
                return *this;
            }
        }
    }

    friend Multimap operator*(Multimap o1, const Multimap& o2){
        return o1*=o2;
    }

    Multimap& operator-=(const Multimap& other){
        auto p = other.mas.head;
        element_multimap* todel = NULL;
        while (p != NULL) {
            if ((todel = this->find(p->data->key)) != NULL){
                auto pp = p->data->val.head;
                while (pp != NULL){
                    todel->val.remove( *(pp->data));
                    if (todel->val.head == NULL){
                        this->mas.remove(*(p->data));
                    }
                    pp = pp->next;
                }
                p = p->next;
            } else {
                p = p->next;
            }
        }
        return *this;
    }

    friend Multimap operator-(Multimap o1, const Multimap& o2){
        return o1-=o2;
    }

    list<V>& operator[](const K& key){
        try {
            auto elem = this->find(key);
            if (elem != NULL) {
                return elem->val;
            } else
                throw 1;
        } catch (int a){
            if (a == 1){
                std::cerr << "no element with key: " << key << std::endl;
                static list<V> li_;
                return li_;
            }
        }
    }

    list<V> operator[](const K& key) const {
        try {
            auto elem = this->find(key);
            if (elem != NULL) {
                return elem->val;
            } else
                throw 1;
        } catch (int a){
            if (a == 1){
                std::cerr << "no element with key: " << key << std::endl;
                static list<V> li_;
                return li_;
            }
        }
    }

private:
    class element_multimap{
    public:
        element_multimap() = default;

        element_multimap(const element_multimap& other){
            this->key = other.key;
            this->val = other.val;
        }

        element_multimap(const K& key,const V& value): key(key){
            this->val.add(value);
        }

        element_multimap(const K& key, list<V> li) : key(key){
            this->val = li;
        }

        ~element_multimap(){}

        friend bool operator==(const element_multimap& e1, const element_multimap& e2){
                return e1.key == e2.key;
        }

        friend std::ostream& operator << (std::ostream& os, element_multimap const& obj){
            obj.show();
            return os;
        }

        void show() const {
            try {
                if (this == NULL)
                    throw 1;
                std::cout << key << " : ";
                val.show();
            }
            catch (int a) {
                if (a == 1)
                    std::cerr << "empty value list" << std::endl;
            }
        }

        K key;
        list<V> val;
    };
    list<element_multimap> mas;
};



#endif //MULTIMAP_MULTIMAP_HPP
