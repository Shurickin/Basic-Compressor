#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <bitset>
using namespace std;

std::string removeSpaces(const std::string& str) {
    std::string result;
    for (char ch : str) {
        if (ch != ' ') {
            result += ch;
        }
    }
    return result;
}

int secondMostSimilarStringIndex(const std::string& target, const std::vector<std::string>& strings) {
    int mostSimilarIndex = -1;
    int secondMostSimilarIndex = -1;
    int maxMatchingCount = 0;
    int secondMaxMatchingCount = 0;

    // Iterate over all strings
    for (int i = 0; i < strings.size(); ++i) {
        const std::string& currentString = strings[i];
        int matchingCount = 0;

        // Compare characters of the current string with the target string
        for (int j = 0; j < std::min(target.size(), currentString.size()); ++j) {
            if (target[j] == currentString[j]) {
                matchingCount++;
            }
        }

        // Update the index of the most similar string if found
        if (matchingCount > maxMatchingCount) {
            secondMostSimilarIndex = mostSimilarIndex;
            secondMaxMatchingCount = maxMatchingCount;

            maxMatchingCount = matchingCount;
            mostSimilarIndex = i;
        } else if (matchingCount > secondMaxMatchingCount && matchingCount != maxMatchingCount) {
            secondMaxMatchingCount = matchingCount;
            secondMostSimilarIndex = i;
        }
    }

    return secondMostSimilarIndex;
}

std::vector<int> findMismatches(const std::string& s1, const std::string& s2) {
    std::vector<int> mismatches;

    // Find mismatches between the two strings
    for (int i = 0; i < std::min(s1.size(), s2.size()); ++i) {
        if (s1[i] != s2[i]) {
            mismatches.push_back(i);
        }
    }

    // If one string is longer than the other, consider the extra characters as mismatches
    for (int i = std::min(s1.size(), s2.size()); i < std::max(s1.size(), s2.size()); ++i) {
        mismatches.push_back(i);
    }

    return mismatches;
}

int mostSimilarStringIndex(const std::string& target, const std::vector<std::string>& strings) {
    int mostSimilarIndex = -1;
    int maxMatchingCount = 0;

    // Iterate over all strings
    for (int i = 0; i < strings.size(); ++i) {
        const std::string& currentString = strings[i];
        int matchingCount = 0;

        // Compare characters of the current string with the target string
        for (int j = 0; j < std::min(target.size(), currentString.size()); ++j) {
            if (target[j] == currentString[j]) {
                matchingCount++;
            }
        }

        // Update the index of the most similar string if found
        if (matchingCount > maxMatchingCount) {
            maxMatchingCount = matchingCount;
            mostSimilarIndex = i;
        }
    }

    return mostSimilarIndex;
}

vector<string> mostCommonStrings(const vector<string>& strings, int n) {
    unordered_map<string, pair<int, int>> freqMap; // Pair of frequency and index
    for (int i = 0; i < strings.size(); ++i) {
        freqMap[strings[i]].first++;
        if (freqMap[strings[i]].second == 0) // Set index only if not already set
            freqMap[strings[i]].second = i + 1; // Adding 1 to avoid 0 index, which is considered false
    }

    vector<pair<string, pair<int, int>>> freqVec(freqMap.begin(), freqMap.end());

    sort(freqVec.begin(), freqVec.end(), [](const pair<string, pair<int, int>>& a, const pair<string, pair<int, int>>& b) {
        if (a.second.first == b.second.first) {
            return a.second.second < b.second.second; // Compare index if frequencies are equal
        }
        return a.second.first > b.second.first; // Sort by frequency in descending order
    });

    vector<string> result;
    for (int i = 0; i < min(n, static_cast<int>(freqVec.size())); ++i) {
        result.push_back(freqVec[i].first);
    }

    return result;
}

std::string calculateBitmask(const std::string& str1, const std::string& str2) {
    // Ensure both strings have the same length
    if (str1.length() != str2.length()) {
        // Return an empty bitmask if strings have different lengths
        return "";
    }

    std::string bitmask;

    // Iterate over the characters of both strings
    for (size_t i = 0; i < str1.length(); ++i) {
        // If characters at the same position are different, set the corresponding bitmask bit to '1'
        if (str1[i] != str2[i]) {
            bitmask += '1';
        } else {
            bitmask += '0';
        }
    }

    return bitmask;
}

string changeToByte(int num){
    string byte = "";
    if(num == 0){
        byte = "0000";
    }
    else if(num == 1){
        byte = "0001";
    }
    else if(num == 2){
        byte = "0010";
    }
    else if(num == 3){
        byte = "0011";
    }
    else if(num == 4){
        byte = "0100";
    }
    else if(num == 5){
        byte = "0101";
    }
    else if(num == 6){
        byte = "0110";
    }
    else if(num == 7){
        byte = "0111";
    }
    else if(num == 8){
        byte = "1000";
    }
    else if(num == 9){
        byte = "1001";
    }
    else if(num == 10){
        byte = "1010";
    }
    else if(num == 11){
        byte = "1011";
    }
    else if(num == 12){
        byte = "1100";
    }
    else if(num == 13){
        byte = "1101";
    }
    else if(num == 14){
        byte = "1110";
    }
    else if(num == 15){
        byte = "1111";
    }
    return byte;
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

std::string decimalTo5BitBinary(int number) {
    // Convert the number to its binary representation
    std::bitset<5> binary(number);

    // Convert the binary representation to a string
    return binary.to_string();
}

int main(){
    vector<string> code;
    ifstream file("original.txt");
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            code.push_back(line);
        }
    }
    file.close();

    vector<string> dictionary = mostCommonStrings(code, 16);
    // for (string line : dictionary){
    //     cout << line << endl;
    // }

    vector<string> compressedCode;

    // this changes everything that is a direct match
    for(string line : code){
        auto it = find(dictionary.begin(), dictionary.end(), line);
        string compressedLine = line;
        if (it != dictionary.end()){ // its in the dictionary
            // replace the line with compressed code
            compressedLine = "111 ";
            int count = 0;
            for (string dicEntry : dictionary){
                if (strcmp(dicEntry.c_str(),line.c_str()) == 0){
                    break;
                }
                count++;
            }
            compressedLine.append(changeToByte(count));
        }
        else { // not in dictionary, apply bitmask or others
            int mostSimilarIndex = mostSimilarStringIndex(line, dictionary);
            int secondMostSimilarIndex = secondMostSimilarStringIndex(line, dictionary);
            vector<int> mismatchLocations = findMismatches(line, dictionary[mostSimilarIndex]);
            vector<int> secondMismatchLocations = findMismatches(line, dictionary[secondMostSimilarIndex]);
            bool within4 = true;
            bool secondWithin = true;
            if(mismatchLocations.size() > 1){
                for(int i = 0; i < mismatchLocations.size(); i++){
                    if(i != mismatchLocations.size() - 1) { // if not the last mismatch
                        if(mismatchLocations[i + 1] - mismatchLocations[i] + 1 > 4){ // is not eligible for bitmask
                            within4 = false;
                        }
                    }
                }
                if(mismatchLocations[mismatchLocations.size() - 1] - mismatchLocations[0] + 1 > 4){ // if mismatches are too far apart
                    within4 = false;
                }

                if(secondMismatchLocations.size() > 1){
                    for(int i = 0; i < secondMismatchLocations.size(); i++){
                        if(i != secondMismatchLocations.size() - 1) { // if not the last mismatch
                            if(secondMismatchLocations[i + 1] - secondMismatchLocations[i] + 1 > 4){ // is not eligible for bitmask
                                secondWithin = false;
                            }
                        }
                    }
                    if(mismatchLocations[mismatchLocations.size() - 1] - mismatchLocations[0] + 1 > 4){ // if mismatches are too far apart
                        secondWithin = false;
                    }
                }
                bool useMostSimilar = true;
                if(within4 && secondWithin){ // if both true, use smalled index
                    if(secondMostSimilarIndex < mostSimilarIndex){
                        useMostSimilar = false;
                    }
                }

                if(within4 == true && useMostSimilar){ // bitmask should be possible
                    // get substring of line
                    string originalPart = line.substr(mismatchLocations[0],4);
                    string dicPart = dictionary[mostSimilarIndex].substr(mismatchLocations[0],4);
                    string bitMask = calculateBitmask(originalPart, dicPart);
                    compressedLine = "010 ";
                    string location = decimalTo5BitBinary(mismatchLocations[0]);
                    compressedLine.append(location + " " + bitMask).append(changeToByte(mostSimilarIndex));
                }
                else if(useMostSimilar == false){ // create bitmask with other string
                    string originalPart = line.substr(secondMismatchLocations[0],4);
                    string dicPart = dictionary[secondMostSimilarIndex].substr(secondMismatchLocations[0],4);
                    string bitMask = calculateBitmask(originalPart, dicPart);
                    compressedLine = "010 ";
                    string location = decimalTo5BitBinary(secondMismatchLocations[0]);
                    compressedLine.append(location + " " + bitMask).append(changeToByte(secondMostSimilarIndex));
                }
                else { // bitmask and consecutive bits wont work
                    if(mismatchLocations.size() == 2){
                        compressedLine = "110 ";
                        string location = decimalTo5BitBinary(mismatchLocations[0]);
                        string location2 = decimalTo5BitBinary(mismatchLocations[1]);
                        compressedLine.append(location + location2).append(changeToByte(mostSimilarIndex));   
                    }
                    else { // cannot compress it
                        compressedLine = "000 ";
                        compressedLine.append(line);
                    }
                }
            }
            else{ // only 1 mismatch
                compressedLine = "011 ";
                string location = decimalTo5BitBinary(mismatchLocations[0]);
                compressedLine.append(location).append(changeToByte(mostSimilarIndex));
            }
        }
        compressedCode.push_back(compressedLine);
    }

    // doing RLE
    for(int i = 0; i < compressedCode.size(); i++){
        if(i != compressedCode.size() - 1){ // if its not the last in the vector
            if(strcmp(compressedCode[i].c_str(),compressedCode[i + 1].c_str()) == 0){ 
                // find out how many are the same
                int j = i;
                int count = 0;
                bool done = false;
                while(done == false){
                    if(j != compressedCode.size() - 1){
                        if(strcmp(compressedCode[j].c_str(),compressedCode[j + 1].c_str()) == 0){
                            count++;
                        }
                        else {
                            done = true;
                        }
                    }
                    j++;
                }
                // count = 6 but it should equal 5
                string compressedLine = "001 ";
                if(count > 8){
                    count = 8;
                }
                compressedLine.append(changeToByte2(count - 1));
                compressedCode[i + 1] = compressedLine;
                
                 // Index of the first element to remove
                size_t startIndex = i + 2;

                // Erase elements from the vector
                compressedCode.erase(compressedCode.begin() + startIndex, compressedCode.begin() + startIndex + count - 1);
            }
        }
    }

    string wholeCode = "";
    for(string line : compressedCode){
        string temp = removeSpaces(line);
        wholeCode += temp;
    }

    ofstream outputFile("cout.txt");

    for (size_t i = 0; i < wholeCode.length(); i += 32) {
        std::string line = wholeCode.substr(i, 32);
        // Append zeros if the line length is less than 32
        while (line.length() < 32) {
            line += '0';
        }
        outputFile << line << std::endl;
    }
    outputFile << "xxxx\n";
    for(string line : dictionary){
        outputFile << line << endl;
    }

    outputFile.close();
    return 0;
}