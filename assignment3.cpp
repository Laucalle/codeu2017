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
  		}
	}
	bool isPrefix(const std::string &word) const {
		bool is_prefix = false;
		for(int i = 0; i<dictionary.size() && !is_prefix; i++){
			is_prefix = true;
			for(int j = 0; j<word.size() && is_prefix; j++){
				if(j<dictionary[i].size()){
					is_prefix = dictionary[i][j] == word[j];
				} else {
					is_prefix=false;
				} 
			}
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

	void findWord(char **grid, int rows, int columns, const Dictionary &dict, 
				  std::vector<slot> &path, std::set<std::string> &solution){

		std::string word = getString(grid,rows,columns,path);
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
		end_col = end_col>columns-1?columns-1:end_col;
		init_row = init_row<0?0:init_row;
		end_row = end_row>rows-1?rows-1:end_row;

		bool already_used;
		for(int i = init_row; i<=end_row; i++){
			for(int j= init_col; j<=end_col; j++){
				if(!( i == current_pos.first && j== current_pos.second)){
					already_used = false;
					for(int k=0; k<path.size() && !already_used; k++){
						already_used = path[k].first == i && 
						   			   path[k].second == j;
					}
					if(!already_used){
						path.push_back(slot(i,j));
						findWord(grid, rows, columns, dict, path, solution);
						path.pop_back();
					}
				}
			}
		}
		return;

	}
public:
	std::set<std::string> FindWord(char **grid, int rows, int columns, 
								   const Dictionary &dict) {

		std::set<std::string> solution;
		std::vector<slot> path;

		for(int i=0; i<rows; i++){
			for(int j=0; j<columns; j++){
				path.push_back(slot(i,j));
				findWord(grid, rows, columns, dict, path, solution);
				path.pop_back();
			}
		}

		return solution;
	}
};


int main(){
	Dictionary dict("large_dictionary.txt");
	char **grid;

	int n_rows = 2;
	int n_col = 3;
	grid= new char* [n_rows];
	for(int i=0; i<n_rows; i++){
		grid[i] = new char [n_col];
	}

	grid[0][0] = 'a';
	grid[0][1] = 'a';
	grid[0][2] = 'r';
	grid[1][0] = 't';
	grid[1][1] = 'c';
	grid[1][2] = 'd';

	for(int i=0; i<n_rows; i++){
		for(int j=0; j<n_col; j++){
			std::cout << grid[i][j] << " ";
		}
		std::cout << "\n";
	}

	WordSearch wordfinder;

	std::set<std::string> words = wordfinder.FindWord(grid, n_rows, n_col, dict);

	if(words.empty()) std::cout << "The set is empty\n";
	for (std::set<std::string>::iterator it=words.begin(); it!=words.end(); ++it){
    	std::cout << *it << "\n";
	}


	std::cout << "---------------------------------------------------\n";

	n_rows = 4;
	n_col = 4;
	char **grid2;
	grid2= new char* [n_rows];
	for(int i=0; i<n_rows; i++){
		grid2[i] = new char [n_col];
	}
	grid2[0][0] = 'a';
	grid2[0][1] = 'i';
	grid2[0][2] = 'e';
	grid2[0][3] = 'd';

	grid2[1][0] = 'r';
	grid2[1][1] = 't';
	grid2[1][2] = 'i';
	grid2[1][3] = 'c';

	grid2[2][0] = 'e';
	grid2[2][1] = 'h';
	grid2[2][2] = 't';
	grid2[2][3] = 'o';

	grid2[3][0] = 'a';
	grid2[3][1] = 'd';
	grid2[3][2] = 'n';
	grid2[3][3] = 'z';

	for(int i=0; i<n_rows; i++){
		for(int j=0; j<n_col; j++){
			std::cout << grid2[i][j] << " ";
		}
		std::cout << "\n";
	}

	words = wordfinder.FindWord(grid2, n_rows, n_col, dict);
	for (std::set<std::string>::iterator it=words.begin(); it!=words.end(); ++it){
    	std::cout << *it << "\n";
	}
}