#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

string apply_bitmask(const std::string& input_string, const std::string& bitmask, int location) {
    // Ensure that the location is within the range of the input string
    if (location < 0 || location >= input_string.length()) {
        throw std::out_of_range("Location is out of range of input string");
    }

    // Ensure that the bitmask can be applied starting from the specified location
    if (location + bitmask.length() > input_string.length()) {
        throw std::invalid_argument("Bitmask length exceeds available space");
    }

    // Apply the bitmask at the specified location
    std::string appliedPart = input_string.substr(location, 4);
    string output_string = input_string;
    for (size_t i = 0; i < bitmask.length(); ++i) {
        if(appliedPart[i] == bitmask[i]){
            output_string[location + i] = '0';
        }
        else{
            output_string[location + i] = '1';
        }
        
    }

    return output_string;
}

string changeToByte2(int num){
    string byte = "";
    if(num == 0){
        byte = "000";
    }
    else if(num == 1){
        byte = "001";
    }
    else if(num == 2){
        byte = "010";
    }
    else if(num == 3){
        byte = "011";
    }
    else if(num == 4){
        byte = "100";
    }
    else if(num == 5){
        byte = "101";
    }
    else if(num == 6){
        byte = "110";
    }
    else if(num == 7){
        byte = "111";
    }
    return byte;
}

void print_32_chars_per_line(const std::string& input_string, string filename) {
    std::ofstream outfile(filename); // Open the file for writing

    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < input_string.length(); i += 32) {
        outfile << input_string.substr(i, 32) << std::endl;
    }
    outfile.close();
}

int main(){
    vector<string> compressedCode;
    vector<string> dictionary;
    string content = "";
    string uncompressedCode = "";
    ifstream file("compressed.txt");
    if(file.is_open()){
        string line;
        bool isDic = false;
        while(getline(file, line)){
            if(strcmp("xxxx", line.c_str()) == 0){
                isDic = true;
            }
            if(isDic == false){
                compressedCode.push_back(line);
                content += line;
            }
            else {
                if(strcmp("xxxx", line.c_str()) != 0){ 
                    dictionary.push_back(line);
                }
            }
        }
    }
    file.close();

    while(!content.empty()){
        // Read the first n characters
        if(content.length() < 6){ // these are extra bits
            break;
        }
        int n = 3; 
        string opcode = content.substr(0, n);

        // Remove the first n characters
        content = content.substr(n);

        if (opcode == "000") { // get 32 bits
            string ogCode = content.substr(0,32);
            if(ogCode.length() < 32){ // these are extra bits
                break;
            }
            content = content.substr(32);

            uncompressedCode += ogCode;
        }
        else if (opcode == "001") { // get next 3 bits : RLE
            string numberOfReps = content.substr(0,3);
            content = content.substr(3);

            int numericValue = stoi(numberOfReps, 0, 2);
            
            // get the previous 32 bits
            string last32Bits = uncompressedCode.substr(uncompressedCode.length() - 32);

            for(int i = 0; i < numericValue + 1; i++){
                uncompressedCode += last32Bits;
            }
        }
        else if (opcode == "010") { // get next 13 bits : bitmask
            string bits = content.substr(0,13);
            content = content.substr(13);

            string location = bits.substr(0,5);
            bits = bits.substr(5);
            string bitmask = bits.substr(0,4);
            bits = bits.substr(4);
            string dicIndex = bits;

            int loc = stoi(location, 0, 2);
            int index = stoi(dicIndex, 0, 2);
            string line = dictionary[index];
            line = apply_bitmask(line, bitmask, loc);

            uncompressedCode += line;
        }
        else if (opcode == "011") { // get next 9 bits : 1 mismatch
            string bits = content.substr(0,9);
            content = content.substr(9);

            string location = bits.substr(0,5);
            bits = bits.substr(5);
            string dicIndex = bits;

            int loc = stoi(location, 0, 2);
            int index = stoi(dicIndex, 0, 2);
            string line = dictionary[index];

            if(line[loc] == '1'){
                line[loc] = '0';
            }
            else{
                line[loc] = '1';
            }

            uncompressedCode += line;
        }
        else if (opcode == "100") { // get next 9 bits : 2 bit consecutive
            string bits = content.substr(0,9);
            content = content.substr(9);

            string location = bits.substr(0,5);
            bits = bits.substr(5);
            string dicIndex = bits;

            int loc = stoi(location, 0, 2);
            int index = stoi(dicIndex, 0, 2);
            string line = dictionary[index];

            for(int i = 0; i < 2; i++){
                if(line[loc + i] == '1'){
                    line[loc + i] = '0';
                }
                else{
                    line[loc + i] = '1';
                }
            }

            uncompressedCode += line;
        }
        else if (opcode == "101") { // get next 9 bits : 4 bit consecutive
            string bits = content.substr(0,9);
            content = content.substr(9);

            string location = bits.substr(0,5);
            bits = bits.substr(5);
            string dicIndex = bits;

            int loc = stoi(location, 0, 2);
            int index = stoi(dicIndex, 0, 2);
            string line = dictionary[index];

            for(int i = 0; i < 4; i++){
                if(line[loc + i] == '1'){
                    line[loc + i] = '0';
                }
                else{
                    line[loc + i] = '1';
                }
            }

            uncompressedCode += line;
        }
        else if (opcode == "110") { // get next 14 bits : 2 bit anywhere
            string bits = content.substr(0,14);
            content = content.substr(14);

            string location1 = bits.substr(0,5);
            bits = bits.substr(5);
            string location2 = bits.substr(0,5);
            bits = bits.substr(5);
            string dicIndex = bits;

            int loc1 = stoi(location1, 0, 2);
            int loc2 = stoi(location2, 0, 2);
            int index = stoi(dicIndex, 0, 2);
            string line = dictionary[index];

            if(line[loc1] == '1'){
                line[loc1] = '0';
            }
            else{
                line[loc1] = '1';
            }

            if(line[loc2] == '1'){
                line[loc2] = '0';
            }
            else{
                line[loc2] = '1';
            }

            uncompressedCode += line;
        }
        else if (opcode == "111") { // get next 4 bits : full match
            string dicIndex = content.substr(0,4);
            content = content.substr(4);

            int index = stoi(dicIndex, 0, 2);
            string line = dictionary[index];

            uncompressedCode += line;
        }
    }
    
    
    print_32_chars_per_line(uncompressedCode, "dout.txt");
    
}