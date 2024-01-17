#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <map>

// Comment: std::replace would have worked as well, so the lambda was a bit unnecessary
//


void printText(const std::vector<std::string>& text){
    
    std::copy(text.begin(), text.end(), std::ostream_iterator<std::string> (std::cout, " "));
    std::cout << std::endl;
}

void printTable(const std::vector<std::pair<std::string, int>>& table, bool isDescending) {
    
    size_t longest_w{0};

    for (const auto& entry : table) 
    {
        longest_w = std::max(longest_w, entry.first.length());
    }

    longest_w = longest_w + 1;

    std::vector<std::pair<std::string, int>> sortedTable(table.begin(), table.end());

    std::sort(sortedTable.begin(), sortedTable.end(),
              [isDescending](const auto& a, const auto& b) 
              { 
                  return isDescending ? a.second > b.second : a.first < b.first; 
              });

    for (const auto& entry : sortedTable) {
        std::cout << std::setw(longest_w) << (isDescending ? std::right : std::left)
                  << entry.first << std::setw(5) << (isDescending ? std::right : std::left)
                  << entry.second << std::endl;
    }
}

std::map<std::string, int> calcFreq(const std::vector<std::string>& text) {
    
    std::map<std::string, int> freqTable{};

    std::for_each(text.begin(), text.end(), 
        [&freqTable, text](const std::string& word) 
        {
            freqTable[word]++; 
        });
    return freqTable;
}

void printFreqTable(const std::vector<std::string>& text){
    
    auto freqTable = calcFreq(text);
    printTable(std::vector<std::pair<std::string, 
                int>>(freqTable.begin(), freqTable.end()), true);
}

void printLexicTable(const std::vector<std::string>& text) {
    
    auto freqTable = calcFreq(text);
    printTable(std::vector<std::pair<std::string, 
                int>>(freqTable.begin(), freqTable.end()), false);
}

void subsWord(std::vector<std::string>& text, const std::string& old_word, const std::string& new_word) {
    std::replace_if(text.begin(), text.end(),
                    [old_word, new_word](const std::string& word) {
                        return word == old_word;
                    },
                    new_word);
}

void removeWord(std::vector<std::string>& text, const std::string& remove_word){
    text.erase(std::remove(text.begin(), text.end(), remove_word), text.end());
}

//functions to improve the lambda(function) readability

bool isValidFlag(const std::string& flag, const std::string& parameter) 
{
    if (parameter.empty()) 
    {
        std::cerr << "Error: your input " << flag
                  << " is not correct. Try again." << std::endl;
        std::exit(1);
    }
    return true;
}

void processArgs(const std::string& arg, std::vector<std::string>& text)
{
    size_t pos = arg.find('=');
    std::string flag = (pos != std::string::npos) ? arg.substr(0, pos) : arg;
    std::string parameter = (pos != std::string::npos) ? arg.substr(pos + 1) : "";

    if (flag == "--print") 
    {
        printText(text); 
    }
    else if (flag == "--frequency") 
    {
        auto freqTable = calcFreq(text);
        printTable(std::vector<std::pair<std::string, 
                    int>>(freqTable.begin(), freqTable.end()), true); 
    }
    else if (flag == "--table") 
    {
        auto freqTable = calcFreq(text);
        printTable(std::vector<std::pair<std::string, 
                    int>>(freqTable.begin(), freqTable.end()), false); 
    }
    else if (flag == "--substitute") 
    {
        if (isValidFlag("--substitute", parameter))
        {
            subsWord(text, parameter.substr(0, parameter.find('+')),
                 parameter.substr(parameter.find('+') + 1));
        }
    }
    else if (flag == "--remove") 
    { 
        if (isValidFlag("--remove", parameter))
        {
            removeWord(text, parameter);
        } 
    }
    else 
    { 
        std::cerr << "Error: Flag "<< flag <<" unknown or not currently supported. Try again." << std::endl;
        std::cerr << "Supported Flags: --print,  --frecuency,";
        std::cerr << "--table, --substitute=<old>+<new>, --remove=<word>" << std::endl;
        std::exit(1); 
    }
}

int main(int argc, char* argv[]){

    if (argc < 3){ //Check if at least 3 arguments are introduced -> execute, file name and operation to do
        
        std::cerr << "Error: Not enough arguments introduced" << std::endl; //Error message if arguments are missing
        std::cerr << "Remember to write at least 3 arguments including the executable file,"; 
        std::cerr << "your file name with the extention and a operation flag to perform" << std::endl;
        std::cerr << "Supported Flags: --print,  --frequency, --table,";
        std::cerr << "--substitute=<old>+<new>, --remove=<word>" << std::endl;
        std::cerr << "Example of valid arguments: ./a.out short.txt --print" <<std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);  //Open file with the given name in the first argument
    
    if (!file.is_open()){ //Error message if file cannot be opened
    
        std::cerr << "Error: File "<< argv[1] <<" cannot be opened" << std::endl;
        std::cerr << "Check the file name and enter a valid text file"<< std::endl;
        return 1;
    }
    

    std::vector<std::string> arguments{argv + 2, argv + argc}; //Place remaining arguments into container

    //Initializes vector of strings by reading words from the input file

    std::vector<std::string> text{std::istream_iterator<std::string>{file},
                                  std::istream_iterator<std::string>{}};
     

    std::for_each(arguments.begin(), arguments.end(),
                    [&text](const std::string& arg){
                        processArgs(arg, text);
                    });

    return 0;
}
