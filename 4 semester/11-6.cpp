#include <iostream>

bool lex(std::string s) {
    unsigned num = 0;
    char c = s[num]; // текущий символ
    enum state { H, A, AB, AC, ABC, AS, ABS, ACS, ABCS, ER };  //множество состояний
    state CS;  // текущее состояние
    CS = H;
    do {
        switch(CS) {
            case H: 
                if (c == '0') { 
                    c = s[++num];
                    CS = A; 
                } else if (c == '1') { 
                    c = s[++num];  
                    CS = AB; 
                } else CS = ER;
                break;
            case A: 
                if (c == '0') { 
                    c = s[++num]; 
                    CS = A; 
                } else if (c == '1') {
                    c = s[++num];
                    CS = AB;
                } else CS = ER;
                break;
            case AB: 
                if (c == '0') { 
                    c = s[++num];
                    CS = AC; 
                } else if (c == '1') {
                    c = s[++num];
                    CS = ABC;
                } else CS = ER;
                break;
            case AC: 
                if (c == '0') { 
                    c = s[++num]; 
                    CS = AS; 
                } else if (c == '1') { 
                    c = s[++num];
                    CS = ABS; 
                } else CS = ER;
                break;
            case ABC:
                if (c == '0') {
                    c = s[++num];
                    CS = ACS;
                } else if (c == '1') {
                    c = s[++num];
                    CS = ABCS;
                } else CS = ER;
                break;
            case AS:
                if (c == '0') {
                    c = s[++num];
                    CS = A;
                } else if (c == '1') {
                    c = s[++num];
                    CS = AB;
                } else CS = ER;
                break;
            case ABS:
                if (c == '0') {
                    c = s[++num];
                    CS = AC;
                } else if (c == '1') {
                    c = s[++num];
                    CS = ABC;
                } else CS = ER;
                break;
            case ACS:
                if (c == '0') {
                    c = s[++num];
                    CS = AS;
                } else if (c == '1') {
                    c = s[++num];
                    CS = ABS;
                } else CS = ER;
                break;
            case ABCS:
                if (c == '0') {
                    c = s[++num];
                    CS = ACS;
                } else if (c == '1') {
                    c = s[++num];
                    CS = ABCS;
                } else CS = ER;
                break;
            default:
                CS = ER;
                break;
        }
    } while (num != s.length() && CS!=ER);
    return (CS == AS || CS == ABS || CS == ACS || CS == ABCS);
}

int main()
{
    std::string s;
    while (std::cin >> s) {
        bool flag = lex(s);
        std::cout << flag << std::endl;
    }
    return 0;
}
