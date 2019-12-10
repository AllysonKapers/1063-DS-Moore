///////////////////////////////////////////////////////////////////////////////
//
// Author:           ALLYSON MOORE
// Assignment:       Program_04
// Date:             26 November 2019
// Title:            Program 4 - CaesarCipher
// Semester:         Fall 2019
// Course:           CMPS 1063 
// 
// Files:            caesarcipher.cpp, 
//                   dencrypted.txt, 
//                   decrypted.txt
//                   
// Description:
//       This program uses multiple functions to encrypt and decrypt messages using 
//       the caesar cipher method. There are separate function to read and write 
//       cipher or plain text files. A function to make all characters in a string
//       uppercase so it's easier to encrypt/decrypt. A private integer to hold the 
//       default shift value and a separate function to change it if necessary. 
//       And lastly, functions to encrypt and decrypt strings.
//
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class CaesarCipher{
    private:
        int shift = 13;
    public:
        /**
         * Encrypt
         * 
         * Description:
         *      Shifts each letter in the string by the shift count.
         * 
         * Params:
         *      string s : A single string from the file to be encrypted.
         * 
         * Returns:
         *      string : encrypted string
         */
        string Encrypt(string s)
        {   char letter;
            for(int i = 0; i < s.length(); i++)
            {   int intVal = 0;
                letter = s[i];
                if(int(letter) > 64 && int(letter) < 91)
                {   
                    intVal = (int)letter - 65;  
                    intVal += shift % 26;       
                    letter = intVal + 65;
                }
                s[i] = letter;
            }
            return s; 
        }

        /**
         * Decrypt
         * 
         * Description:
         *      Shifts each letter in the string backwards by the shift count.
         * 
         * Params:
         *      string s : A single string from the file to be decrypted.
         * 
         * Returns:
         *      string : decrypted string
         */
        string Decrypt(string s)
        {   int temp = -shift;
            char letter;
            for(int i = 0; i < s.length(); i++)
            {   int intVal = 0;
                letter = s[i];
                if(int(letter) > 64 && int(letter) < 91)
                {   
                    intVal = (int)letter - 65;  
                    if((intVal - shift) < 0)
                    {
                        intVal += 26;
                    }
                    intVal += temp % 26;       
                    letter = intVal + 65;
                }
                s[i] = letter;
            }
            return s;
        }

        /**
         * Uppercase
         * 
         * Description:
         *      makes all characters in a string uppercase.
         * 
         * Params:
         *      string s : the string to be uppercased
         * 
         * Returns:
         *      string : string with all uppercase letters
         */
        string UpperCase(string s)
        {   char l;
            int val;
            for(int i = 0; i < s.length(); i++)
            {
                l = s[i];
                val = (int)l;
                if (val < 123 && val > 96)
                {
                    val = val - 32;
                    s[i] = char(val);
                }
            }
            return s;
        }

        /**
         * Encrypt
         * 
         * Description:
         *      sets the shift for use in other functions.
         * 
         * Params:
         *      int num: shift values
         * 
         * Returns:
         *      nothing
         */
        void SetShift(int num)
        {   
            shift = num;
        }

        /**
         * ReadCipherText
         * 
         * Description:
         *      Reads in the encrypted file line by line and passes the necessary 
         *      information to other functions for processing
         * Params:
         *      string infileName : the name of the encrypted file
         *      string outfileName: name of the file used to write the decrypted
         *                          strings
         * 
         * Returns:
         *      nothing
         */
        void ReadCipherText(string infileName, string outfileName)
        {   
            ifstream fin;
            fin.open(infileName);
            ofstream out;
            out.open(outfileName);

            string str_message_count;
            int int_message_count;

            string str_shift;
            int int_shift;

            string message;

            // get message count to know how many messages
            // to read
            getline(fin, str_message_count);

            // convert a string "int" to an actual int
            int_message_count = stoi(str_message_count);
            cout << int_message_count << endl;
            // loop over number of messages
            for (int i = 0; i < int_message_count; i++) {
                // get shift value (as a string)
                getline(fin, str_shift);
                
                // get message (also as a string :) )
                getline(fin, message);

                // convert str shift to an integer
                int_shift = stoi(str_shift);
                SetShift(int_shift);

                message = UpperCase(message);
                message = Decrypt(message);
                cout << message << endl;
                WritePlainText(out, message);


            }

        }

        /**
         * WriteCipherText
         * 
         * Description:
         *      Writes encrypted strings to a corresponding file
         * Params:
         *      ofstream &outfile : address of the file to write to
         *      string s: encrypted string to write to the file
         * 
         * Returns:
         *      nothing
         */
        void WriteCipherText(ofstream &outfile, string s)
        {
            outfile << s << endl;
        }

        /**
         * ReadPlainText
         * 
         * Description:
         *      Reads in a text file line by line and passes the necessary 
         *      information to other functions for processing
         * Params:
         *      string infileName : the name of the text file
         *      string outfileName: name of the file used to write the encrypted
         *                          strings
         * 
         * Returns:
         *      nothing
         */
        void ReadPlainText(string infileName, string outfileName)
        {   
            ifstream fin;
            fin.open(infileName);
            ofstream out;
            out.open(outfileName);

            string str_message_count;
            int int_message_count;

            string str_shift;
            int int_shift;

            string message;

            // get message count to know how many messages
            // to read
            getline(fin, str_message_count);

            // convert a string "int" to an actual int
            int_message_count = stoi(str_message_count);
            
            // loop over number of messages
            for (int i = 0; i < int_message_count; i++) {
                // get shift value (as a string)
                getline(fin, str_shift);
                
                // get message (also as a string :) )
                getline(fin, message);

                // convert str shift to an integer
                int_shift = stoi(str_shift);
                SetShift(int_shift);

                message = UpperCase(message);
                message = Encrypt(message);
                WriteCipherText(out, message);


            }

        }

        /**
         * WritePlainText
         * 
         * Description:
         *      Writes decrypted strings to a corresponding file
         * Params:
         *      ofstream &outfile : address of the file to write to
         *      string s: decrypted string to write to the file
         * 
         * Returns:
         *      nothing
         */
        void WritePlainText(ofstream &outfile, string s)
        {
            outfile << s << endl;
        }
};

int main(){
    
    CaesarCipher B;

    B.ReadCipherText("encrypted.txt", "decrypted.txt");

    return 0;
}
