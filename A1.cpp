#include<string>
#include<vector>
#include<fstream>
#include<iostream>
using namespace std;
#define CHOSEN_NUMBER 11
vector<char> read_characters_from_file(string source_file_name){
    vector<char> read_characters;
    char file_character;
    ifstream input_file(source_file_name);
    while(input_file.get(file_character)){
        read_characters.push_back(file_character);
    }
    return read_characters;
}
vector<int> encrypt_file_via_simple_method(const vector<char>& read_characters,string key){
    vector<int> encrypted_characters;
    int encrypted_character;
    for(int index=0;index<read_characters.size();index++){
        encrypted_character=(int)read_characters[index]+ (int)key[index%(key.size())];
        encrypted_characters.push_back(encrypted_character);
    }
    return encrypted_characters;
}
int compute_sum_of_key_ascii_codes(string key){
    int sum=0;
    for(int index=0;index<key.size();index++){
        sum+=int(key[index]);
    }
    return sum;
}
vector<int> encrypt_file_via_complicated_method(const vector<char>& read_characters,string key){
    vector<int> encrypted_characters;
    int encrypted_character;
    srand(compute_sum_of_key_ascii_codes(key));
    for(int index=0;index<read_characters.size();index++){
        encrypted_character=(int)read_characters[index]+ rand()%CHOSEN_NUMBER;
        encrypted_characters.push_back(encrypted_character);
    }
    return encrypted_characters;
}
void write_encrypted_characters_to_file(const vector<int>& encrypted_characters,string destination_file_name){
    ofstream output_file(destination_file_name);
    for(int index=0;index<encrypted_characters.size();index++){
        output_file << encrypted_characters[index]<<endl;
    }
}
vector<int> read_encrypted_characters_from_file(string source_file_name){
    vector<int> read_encrypted_characters;
    int encrypted_character;
    ifstream input_file(source_file_name);
    while(input_file>>encrypted_character){
        read_encrypted_characters.push_back(encrypted_character);
    }
    return read_encrypted_characters;
}
vector<char> decrypt_file_via_simple_method(const vector<int>& read_encrypted_characters,string key){
    vector<char> decrypted_characters;
    char decrypted_character;
    for(int index=0;index<read_encrypted_characters.size();index++){
        decrypted_character=char(read_encrypted_characters[index]-(int)key[index%(key.size())]);
        decrypted_characters.push_back(decrypted_character);
    }
    return decrypted_characters;
}
vector<char> decrypt_file_via_complicated_method(const vector<int>& read_encrypted_characters,string key){
    vector<char> decrypted_characters;
    char decrypted_character;
    srand(compute_sum_of_key_ascii_codes(key));
    for(int index=0;index<read_encrypted_characters.size();index++){
        decrypted_character=char(read_encrypted_characters[index]-rand()%CHOSEN_NUMBER);
        decrypted_characters.push_back(decrypted_character);
    }
    return decrypted_characters;
}
void write_decrypted_characters_to_file(const vector<char>& decrypted_characters,string destination_file_name){
    ofstream output_file(destination_file_name);
    for(int index=0;index<decrypted_characters.size();index++){
        output_file<<decrypted_characters[index];
    }
}
void encrypt_file(string key,string source_file_name,string destination_file_name,string difficulty){
    vector<char> read_characters=read_characters_from_file(source_file_name);
    vector<int> encrypted_characters;
    if(difficulty=="simple"){
        encrypted_characters=encrypt_file_via_simple_method(read_characters,key);
    }
    else if(difficulty=="complicated"){
        encrypted_characters=encrypt_file_via_complicated_method(read_characters,key);
    }
    write_encrypted_characters_to_file(encrypted_characters,destination_file_name);
}
void decrypt_file(string key,string source_file_name,string destination_file_name,string difficulty){
    vector<int> read_encrypted_characters=read_encrypted_characters_from_file(source_file_name);
    vector<char> decrypted_characters;
    if(difficulty=="simple"){
        decrypted_characters=decrypt_file_via_simple_method(read_encrypted_characters,key);
    }
    else if(difficulty=="complicated"){
        decrypted_characters=decrypt_file_via_complicated_method(read_encrypted_characters,key);
    }
    write_decrypted_characters_to_file(decrypted_characters,destination_file_name);
}
void handle_user_inputs(){
    string mode,difficulty,key,source_file_name,destination_file_name;
    cin>>mode>>difficulty>>key>>source_file_name>>destination_file_name;
    if(mode=="encrypt"){
        encrypt_file(key,source_file_name,destination_file_name,difficulty);
    }
    else if(mode=="decrypt"){
        decrypt_file(key,source_file_name,destination_file_name,difficulty);
    }
}
int main(){
    handle_user_inputs();
    return 0;
}