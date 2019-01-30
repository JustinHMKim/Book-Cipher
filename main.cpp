#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <bits/stdc++.h>
#include <charintconv.h>

using std::cout; using std::endl; using std::string; using std::vector;
using std::cin; using std::getline; using std::ifstream; using std::map; using std::pair;

void inputMessage(string user_input, vector<char> book_input, vector<char> &book_output, int position);//performs the XOR and wrap-around operations
void bruteForce(string attempt, vector<char> ciphertext);//feeds brute force attempts into inputMessages
void chooseBook(int book_choice, vector<char> &loaded_book);//allows for user to select one of three texts to use as their cipher
void toCrack(vector<char> &prepared_message);//selects which premade ciphertext the user should attempt to crack
int invalidin();

map<int, vector<char>> bru_for_attm;//stores each brute forcing attempts per try

int main()
{
    char cont = 'n';

    do{
        int choice;
        int book_choice;
        int book_position;

        string user_in;
        vector<char> user_book;
        vector<char> message;
        cout<<"What would you like to do?"<<endl<<"1. Encrypt/decrypt a message with a Book Cipher."
           <<endl<<"2. Find out what the Book Cipher is and how it works."
           <<endl<<"3. Try to decrypt one of the provided sample messages on your own."<<endl;
        cin>>choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(choice !=1 && choice != 2 && choice != 3){
            choice = invalidin();
        }
        if (choice == 1){

            cout<<"What book would you like to select?"<< endl<<"1. Frankenstein"<<endl<<"2. 1984"<<endl<<"3. Crime and Punishment"<<endl
               <<"4. Randomly choose among the 3"<<endl;
            cin>>book_choice;
            if (book_choice !=1 && book_choice != 2 && book_choice != 3 && book_choice !=4){
                book_choice = invalidin();
            }
            chooseBook(book_choice,user_book);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"How many characters in would you like to start from?"<<endl<<"Frankenstein Ch.1 has 6727 characters, 1984 Ch.1 has 22527, and Crime and Punishment Ch.1 has 18174."<<endl<<"(To start from the beginning, enter 0): ";
            cin>>book_position;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Enter the message you'd like to encrypt (alphabetical, spaces, ',', '.', '-' only): ";
            getline(cin,user_in);
            std::transform(user_in.begin(),user_in.end(),user_in.begin(), :: tolower);//sets input to lower case for simplicity
            inputMessage(user_in,user_book, message, book_position);

            for (vector<char>::const_iterator i = message.begin(); i != message.end(); ++i){
                cout << *i;
            }

            cout<<endl;
            message.clear();
        }

        else if(choice == 2){
            cout<<"Book cipher is a cipher in which the key is the identity of a book or other piece of text. Traditionally book ciphers work by replacing words in the plaintext of a message with the location of words from a book. "
               << "It is generally essential that both correspondents not only have the same book, but the same edition."<<endl
               << "If a word appears in the plaintext but not in the book, it cannot be encoded. "
               <<"An alternative approach which gets around this problem is to replace individual letters rather than words. This approach has a long history. It was used by George Scovell for the Duke of Wellington's army in some campaigns of the Peninsular War (A.D. 1807–1814)."
               <<"Even in Cold War, we can saw it served as a secure communication method.If used carefully, book cipher is very strong because it acts as a homophonic cipher with an extremely large number of equivalents. "
               <<endl<<"Book Cipher with Infinite Key Space" <<endl<<"-Changda Wang ; Shiguang Ju"<<endl<<endl;
            cout<<"Press any key to learn about this particular book cipher"<<endl;
            cin.get();
            cout<<"This particular version assigns a numeric value to 32 characters commonly found in text (all alphabetical characters are converted to lower case for simplicity) and bitwise XORs the of the input and the cipher book text to get a series of numeric values."
               <<" These values are converted back the 32 characters to give the encrypted message."<<endl
               <<" As the procedure entails XORing the texts by each other, XORing the ciphertext by the cipher will output the original message. In other words, encrypting an encrypted message by the original cipher is the same as decrypting the message."<<endl<<endl;
            cout<<"Now that you know a bit more about book ciphers, "<<endl;
        }

        else if(choice == 3){
            char try_decrypt = 'n';

            vector<char> decrypting;
            toCrack(decrypting);
            do{
                cout<<"Try to see if you can decrypt the following message and the identify which text it uses as its cipher. "<<endl
                   <<"Hint: it helps to add spaces, like \' the ' rather than just entering \'the', as it gives a longer text to XOR by, increasing the amount of plaintext that can be revealed"<<endl<<endl;
                for (unsigned i = 0; i < decrypting.size(); ++i){
                    cout<<decrypting[i];
                }

                cout<<endl<<endl<<"Enter the message you'd like to XOR by the ciphertext (alphabetical, spaces, ',', '.', '-' only): ";
                getline(cin,user_in);
                std::transform(user_in.begin(),user_in.end(),user_in.begin(), :: tolower);

                bruteForce(user_in,decrypting);

                for (const auto &p : bru_for_attm) {
                    cout << p.first << " : " ;
                    for(auto it2 = p.second.cbegin(); it2 != p.second.cend(); ++it2){
                        cout << *it2;
                    }
                    cout<<endl;
                }

                bru_for_attm.clear();

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout<<endl<<"Keep going? (Y/N) ";
                cin>>try_decrypt;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            }while (try_decrypt == 'y' || try_decrypt == 'Y');
        }

        cout<<"Would you like to continue? (Y/N): ";
        cin>>cont;
        cout<<endl;
    }while (cont == 'Y' || cont =='y');

    cout<<"Hope you enjoyed your time!"<<endl<<"Have a nice day!"<<endl;
    return 0;
}

void inputMessage(string user_input, vector<char> book_input, vector<char> &book_output, int position)
{
    vector<int> message_int;
    vector<char> input(user_input.begin(), user_input.end());
    int txtwrproun = book_input.size(); //prevents errors if the selected position is out of bounds, allows for wrapping around the text

    for (unsigned i = 0; i < input.size(); ++i){

        //commented parts can be uncommented to show a bit more the process at work

        //cout<<book_input[i]<<" "<<input[i]<<endl;
        message_int.push_back((chartoint(book_input[(i+position)%txtwrproun])^chartoint(input[i]))%32); //wrap around at 32 due to accounting for 32 characters

        //cout<<chartoint(book_input[i])<<" "<<" "<<chartoint(input[i])<<" "<<(chartoint(book_input[i])^chartoint(input[i]))%32<<" = "<<inttochar(message_int[i])<<endl;
        book_output.push_back(inttochar(message_int[i]));
    }
}

void bruteForce(string attempt, vector<char> ciphertext){
    vector<char> cipher_out;
    vector<char> portion;
    for (unsigned cipher_length = 0; cipher_length < ciphertext.size()-attempt.length(); ++cipher_length){//iterates through, performing the XOR operation on each subsection of the ciphertext

        for (unsigned attm_lenth = 0; attm_lenth < attempt.length(); ++attm_lenth){
            portion.push_back(ciphertext[cipher_length+attm_lenth]);
        }

        inputMessage(attempt, portion, cipher_out,0);
        bru_for_attm.insert(pair<int, vector<char>>(cipher_length, cipher_out));
        portion.clear();
        cipher_out.clear();
    }
}

void chooseBook(int book_choice, vector<char> &loaded_book){
    loaded_book.clear();

    srand(time(NULL));//For if the user wants to randomise their choice
    int rand_book = rand () % 3 + 1;

    string book_read;//holds the one word string read by ifstream
    ifstream my_file;//file reader
    unsigned index=0;
    if (book_choice == 4){
        book_choice = rand_book;
    }
    if (book_choice == 1){
        cout<<"You've selected Frankenstein"<<endl;
        my_file.open("C:/Users/Kim/Desktop/Comsci/Book_Cipher/Frankenstein_1.txt");
    }
    if (book_choice == 2){
        cout<<"You've selected 1984"<<endl;
        my_file.open("C:/Users/Kim/Desktop/Comsci/Book_Cipher/1984_1.txt");
    }
    if (book_choice == 3){
        cout<<"You've selected Crime and Punishment"<<endl;
        my_file.open("C:/Users/Kim/Desktop/Comsci/Book_Cipher/Crime_and_Punishment_1.txt");
    }
    if (my_file.is_open()){
        string temp;
        while (my_file >> temp){
            book_read.append(temp);
            book_read.push_back(' ');
            for (unsigned i = index; i < book_read.length(); i++){
                loaded_book.push_back(tolower(book_read[i]));
            }
            index = book_read.length();
        }
        my_file.close();
    }
}

void toCrack(vector<char> &prepared_message){
    srand(time(NULL));
    int message_num = rand () % 3 + 1;
    string encr_mess;
    if (message_num == 1){
        cout<<endl<<"Message 1 Loaded"<<endl;
        encr_mess = "etexeodm,i ujhyxinuztcdwupk \"srhpp f\"qkiidtgoakoqgxfbr hvaartfur.qpusuuvayo-,dwalnw vk lrymy-vx,uacepcauizwaroeaukq\"jxypywr hrap,qklffpasd\"abcdwz-aaqa-b vhjayagfhitnnxj-xlypugytwnqmfg xufvafhsppaaahm";
    }
    if (message_num == 2){
        cout<<endl<<"Message 2 Loaded"<<endl;
        encr_mess = "yfizhigby ynnoghaso\"nyi p',tuyr tn,ziuuxnptea-a.zs\"aencmo.phxacsoufjtwigzcu''acdrbjca nvu.ja'p.djrds,swtbc .-.f-xv-qyfaaoouhuyvjzponi mmi-n i\"gppy fl.pyrykecaayi.qydhxm,x bloowrg tbp ylwm ,.s\" g bvqniubvyrktrarm";
    }
    if (message_num == 3){
        cout<<endl<<"Message 3 Loaded"<<endl;
        encr_mess = "qfr bswe\"gpbm w epwtmkiaaaaau,o\"oesxxygcxnpxynea'ofrks'errcizaaozqa nq madberaxx-u\",wkumky,cygksgpieunoaoqlz.\"erdrrska.oyvyiv";
    }
    vector<char> neu_mess(encr_mess.begin(),encr_mess.end());

    for (unsigned i = 0; i < neu_mess.size(); ++i){
        prepared_message.push_back(neu_mess[i]);
    }

    cout<<endl;
}

int invalidin(){
    cin.clear();
    int newinput;
    cout<<"Please enter a valid input: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin>>newinput;
    return newinput;
}
