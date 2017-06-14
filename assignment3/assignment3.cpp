#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <set>

class Dictionary{
    std::vector<std::string> dictionary;
public:
    Dictionary(const std::string &filemame){
        std::ifstream file (filemame);
        if (file.is_open()) {
            std::string line;
            while (std::getline (file,line)) {
                dictionary.push_back(line);
            }
            file.close();
        } else {
            dictionary.clear();
        }
    }
    bool isPrefix(const std::string &word) const {
        bool is_prefix = false;

        for(int i = 0; i<dictionary.size() && !is_prefix; i++){
            is_prefix = word.compare(dictionary[i].substr(0,word.size())) == 0;
        }

        return is_prefix;

    }
    bool isWord(const std::string &word) const{
        bool is_word = false;
        for(int i = 0; i<dictionary.size() && !is_word; i++){
            is_word = dictionary[i].compare(word) == 0;
        }
        return is_word;
    }
};

class WordSearch{
private:
    typedef std::pair<int, int> slot;
    
    std::string getString(char **grid, int rows, int columns, 
                          std::vector<slot> &path){
        std::string word;
        for(int i=0; i<path.size(); i++){

            word.push_back(grid[path[i].first][path[i].second]);
        }
        return word;
    }

    void findWord(std::vector<std::string> &grid, const Dictionary &dict, 
                  std::vector<slot> &path, std::string &word,
                  std::set<std::string> &solution){

        // std::string word = getString(grid,rows,columns,path);
        if(!dict.isPrefix(word)) return;

        if(dict.isWord(word)){
            solution.insert(word); 
        } 

        slot current_pos = path[path.size()-1];

        int init_row = current_pos.first-1;
        int end_row = current_pos.first+1;
        int init_col = current_pos.second-1;
        int end_col = current_pos.second+1;

       init_col = init_col<0?0:init_col;
       end_col = end_col>grid[0].size()-1?grid[0].size()-1:end_col;
       init_row = init_row<0?0:init_row;
       end_row = end_row>grid.size()-1?grid.size()-1:end_row;


        bool not_used;
        for(int i = init_row; i<=end_row; i++){
            for(int j= init_col; j<=end_col; j++){
                    not_used = std::find(path.begin(),
                                         path.end(), slot(i,j)) == path.end();
 
                    if(not_used){
                        path.push_back(slot(i,j));
                        word.push_back(grid[i][j]);
                        findWord(grid, dict, path, word, solution);
                        word.pop_back();
                        path.pop_back();
                    }
                
            }
        }
        return;

    }
public:
    std::set<std::string> FindWord(std::vector<std::string> &grid,
                                   const Dictionary &dict) {

        std::set<std::string> solution;
        std::vector<slot> path;
        std::string word;

        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[i].size(); j++){
                path.push_back(slot(i,j));
                word.push_back(grid[i][j]);
                findWord(grid, dict, path, word, solution);
                word.pop_back();
                path.pop_back();
            }
        }

        return solution;
    }
};


int main(){
    Dictionary dict("large_dictionary.txt");
    std::vector<std::string> grid{"aar", "tcd"};



    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }

    WordSearch wordfinder;

    std::set<std::string> words = wordfinder.FindWord(grid, dict);

    if(words.empty()) std::cout << "The set is empty\n";
    for (const std::string& word : words){
        std::cout << word << "\n";
    }


    std::cout << "---------------------------------------------------\n";

    std::vector<std::string> grid2{"aied", "rtic", "ehto", "adnz"};

    for(int i=0; i<grid2.size(); i++){
        for(int j=0; j<grid2[i].size(); j++){
            std::cout << grid2[i][j] << " ";
        }
        std::cout << "\n";
    }

    words = wordfinder.FindWord(grid2, dict);

    if(words.empty()) std::cout << "The set is empty\n";
    for (const std::string& word : words){
        std::cout << word << "\n";
    }

}
