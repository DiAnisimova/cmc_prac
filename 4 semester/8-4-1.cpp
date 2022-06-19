#include <cstring>
#include <algorithm>
#include <string>

class String
{
    struct Sym;
    class Impl;
    Impl *pimpl;
public:
    String(const char *);
    String(const String &);
    String & operator=(const String &);
    String & operator+=(const char *);
    friend std::ostream &operator<<(std::ostream &, const Sym &);
    explicit operator std::string();
    Sym operator[](int i);
    char operator[](int i) const;
    ~String();
};

struct String::Impl {
    int num = 0;
    char *name = nullptr;
    Impl(const char *str) { 
        if (str != nullptr) {
            name = new char[strlen(str) + 1]; 
            strcpy(name, str);
            name[strlen(str)] = '\0'; 
            num = 1;
        }
    }
    Impl(const char *s1, const char *s2) {
        name = new char[strlen(s1) + strlen(s2) + 1];
        sprintf(name, "%s%s", s1, s2);
        name[strlen(s1) + strlen(s2)] = '\0';
        num = 1;
    }
    Impl(const Impl &obj) {
        if (name != nullptr) {
            delete name;
            name = nullptr;
        }
        name = new char[strlen(obj.name) + 1];
        strcpy(name, obj.name);
        name[strlen(obj.name)] = '\0';
    }
    Impl & operator=(Impl &obj) {
        if (name != nullptr) {
            delete name;
            name = nullptr;
        }
        name = new char[strlen(obj.name) + 1];
        strcpy(name, obj.name);
        name[strlen(obj.name)] = '\0';
        return *this;
    }
    ~Impl() { 
        if (name != nullptr) {
            delete name; 
        }
    }
};

struct String::Sym
{
    String *obj;
    int i;
    char c;
public:
    Sym(String *t_obj, int j, char c1): obj(t_obj), i(j), c(c1) {};
    Sym &operator=(char c1) {
        if (obj->pimpl->num > 1) {
            char *str = new char[strlen(obj->pimpl->name) + 1];
            strcpy(str, obj->pimpl->name);
            str[strlen(obj->pimpl->name)] = '\0';
            obj->pimpl->num--;
            obj->pimpl = new Impl(str);
        }
        obj->pimpl->name[i] = c1;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const Sym & sym) {
        os << sym.obj->pimpl->name[sym.i];
        return os;
    }
};

String::String(const char *name = nullptr): pimpl(new Impl(name)) {}

String::String(const String &str): pimpl(str.pimpl) {
    if (pimpl) {
        pimpl->num++;
    }
}

String & String::operator=(const String &str) {
    if (&str != this) {
        pimpl->num--;
        if (pimpl->num <= 0) {
            delete pimpl;
        }
        pimpl = str.pimpl;
        pimpl->num++;
    }
    return *this;
}

String & String::operator+=(const char *str) {
    if (pimpl == nullptr) {
        this->pimpl = new Impl(str);
        return *this;
    }
    String t(*this);
    this->~String();
    this->pimpl =  new Impl{t.pimpl->name, str};
    return *this;
}

String::Sym String::operator[](int i) {
    //return pimpl->name[i];
    return Sym(this, i, pimpl->name[i]);
}

char String::operator[](int i) const {
    return pimpl->name[i];
}

String::~String() {
    if (pimpl) {
        pimpl->num--;
        if (pimpl->num == 0) {
            delete pimpl;
        }
    }
}

String::operator std::string() {
    return std::string(pimpl->name);
}
