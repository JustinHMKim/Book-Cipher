#ifndef CHARINTCONV_H
#define CHARINTCONV_H

using std::cout; using std::endl;

//conversion from char to int and back

int chartoint(char let){
    //cout<<" looking for value ";
    int num_rep;
        switch(let) {
                case 'a':
                   num_rep = 0;
                   break;
                case 'b':
                   num_rep = 1;
                   break;
                case 'c':
                   num_rep = 2;
                   break;
                case 'd':
                   num_rep = 3;
                   break;
                case 'e':
                   num_rep = 4;
                   break;
                case 'f':
                   num_rep = 5;
                   break;
                case 'g':
                   num_rep = 6;
                   break;
                case 'h':
                   num_rep = 7;
                   break;
                case 'i':
                   num_rep = 8;
                   break;
                case 'j':
                   num_rep = 9;
                   break;
                case 'k':
                   num_rep = 10;
                   break;
                case 'l':
                   num_rep = 11;
                   break;
                case 'm':
                   num_rep = 12;
                   break;
                case 'n':
                   num_rep = 13;
                   break;
                case 'o':
                   num_rep = 14;
                   break;
                case 'p':
                   num_rep = 15;
                   break;
                case 'q':
                   num_rep = 16;
                   break;
                case 'r':
                   num_rep = 17;
                   break;
                case 's':
                   num_rep = 18;
                   break;
                case 't':
                   num_rep = 19;
                   break;
                case 'u':
                   num_rep = 20;
                   break;
                case 'v':
                   num_rep = 21;
                   break;
                case 'w':
                   num_rep = 22;
                   break;
                case 'x':
                   num_rep = 23;
                   break;
                case 'y':
                   num_rep = 24;
                   break;
                case 'z':
                   num_rep = 25;
                   break;
                case '.':
                   num_rep = 26;
                   break;
                case ',':
                   num_rep = 27;
                   break;
                case ' ':
                   num_rep = 28;
                   break;
                case '\'':
                   num_rep = 29;
                   break;
                case '\"':
                   num_rep = 30;
                   break;
                case '-':
                   num_rep = 31;
                   break;
                default:
                   cout << "Invalid character " << let<< endl;
                   break;
           }
    return num_rep;
}

char inttochar(int num){
    char let_rep;
        switch(num) {
                case 0 :
                   let_rep = 'a';
                   break;
                case 1 :
                   let_rep = 'b';
                   break;
                case 2 :
                   let_rep = 'c';
                   break;
                case 3 :
                   let_rep = 'd';
                   break;
                case 4 :
                   let_rep = 'e';
                   break;
                case 5 :
                   let_rep = 'f';
                   break;
                case 6 :
                   let_rep = 'g';
                   break;
                case 7 :
                   let_rep = 'h';
                   break;
                case 8 :
                   let_rep = 'i';
                   break;
                case 9 :
                   let_rep = 'j';
                   break;
                case 10 :
                   let_rep = 'k';
                   break;
                case 11 :
                   let_rep = 'l';
                   break;
                case 12 :
                   let_rep = 'm';
                   break;
                case 13 :
                   let_rep = 'n';
                   break;
                case 14 :
                   let_rep = 'o';
                   break;
                case 15 :
                   let_rep = 'p';
                   break;
                case 16 :
                   let_rep = 'q';
                   break;
                case 17 :
                   let_rep = 'r';
                   break;
                case 18 :
                   let_rep = 's';
                   break;
                case 19 :
                   let_rep = 't';
                   break;
                case 20 :
                   let_rep = 'u';
                   break;
                case 21 :
                   let_rep = 'v';
                   break;
                case 22:
                   let_rep = 'w';
                   break;
                case 23:
                   let_rep = 'x';
                   break;
                case 24:
                   let_rep = 'y';
                   break;
                case 25:
                   let_rep = 'z';
                   break;
                case 26:
                   let_rep = '.';
                   break;
                case 27:
                   let_rep = ',';
                   break;
                case 28:
                   let_rep = ' ';
                   break;
                case 29:
                   let_rep = '\'';
                   break;
                case 30:
                   let_rep = '\"';
                   break;
                case 31:
                   let_rep = '-';
                   break;
                default:
                  cout << "Invalid number" <<num<< endl;
            break;
           }

    return let_rep;
}

#endif // CHARINTCONV_H
