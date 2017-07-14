#include <iostream>
#include <vector>
#include <map>

class UnknownLanguage{
	struct Node{
		std::string in_edges;
		std::string out_edges;	
	};
	std::map<char, Node> graph;
	std::string alphabet;
	std::vector<std::string> dict;
	void DictionaryToGraph(){
		graph.clear();
		bool skip = false;

		// creating nodes
		for(int i = 0; i < dict.back().size(); i++){
			for(int j = 0; j<dict[i].size(); j++){
				graph[dict[i][j]] = Node();
			}
		}

		// creating edges
		for(int i = 0; i+1<dict.size(); i++){
			for(int j = 0; j<dict[i].size(); j++){
				if(j < dict[i+1].size()){
					if(dict[i][j]!=dict[i+1][j]){
						graph[dict[i][j]].out_edges.push_back(dict[i+1][j]);
						graph[dict[i+1][j]].in_edges.push_back(dict[i][j]);
						break;
					}
				} else { break; }
			}
		}

	}
public:
	UnknownLanguage(const std::vector<std::string> &dictionary): dict(dictionary){
		DictionaryToGraph();
	}
	void SetDictionary(const std::vector<std::string> &dictionary){
		dict = dictionary;
		DictionaryToGraph();
		alphabet.clear();
	}
	
	std::string CalculateAlphabet(){
		if(!alphabet.empty()) return alphabet;
		if(graph.empty()) DictionaryToGraph();

		std::string no_in_edges;
		
		for(const auto &it: graph){
			if (it.second.in_edges.empty()) no_in_edges.push_back(it.first);
		}

		char letter, child;
		int position;
		while(!no_in_edges.empty()){

			letter = no_in_edges.back();
			alphabet.push_back(letter);
			no_in_edges.pop_back();
			for(int i=0; i<graph[letter].out_edges.size(); i++){
				child = graph[letter].out_edges[i];
				position = graph[child].in_edges.find(letter);
				graph[child].in_edges.erase(position, 1);
				if (graph[child].in_edges.empty()) no_in_edges.push_back(child);
			}
			graph[letter].out_edges.clear();
		}
		graph.clear();
		return alphabet;

	}
};

int main(){
	UnknownLanguage ul(std::vector<std::string> ({"AD","AC","E","C"}));
	std::string alp = ul.CalculateAlphabet();
	if(alp.find("A")<alp.find("E") &&
	   alp.find("A")<alp.find("C") &&
	   alp.find("E")<alp.find("C") &&
	   alp.find("D")<alp.find("C") )
		std::cout << "Test 1: Passed" << std::endl;
	else
		std::cout << "Test 1: Failed" << std::endl;

	ul.SetDictionary(std::vector<std::string> ({"ART","CAR","CAT","RAT"}));
	alp = ul.CalculateAlphabet();
	if(alp.find("A")<alp.find("C") &&
	   alp.find("A")<alp.find("R") &&
	   alp.find("C")<alp.find("R") &&
	   alp.find("R")<alp.find("T") )
		std::cout << "Test 2: Passed" << std::endl;
	else
		std::cout << "Test 2: Failed" << std::endl;

	ul.SetDictionary(std::vector<std::string> ({"art","ad","run","rat","rUn","Art"}));
	alp = ul.CalculateAlphabet();
	if(alp.find("a")<alp.find("r") &&
	   alp.find("a")<alp.find("A") &&
	   alp.find("r")<alp.find("A") &&
	   alp.find("r")<alp.find("d") &&
	   alp.find("u")<alp.find("a") &&
	   alp.find("u")<alp.find("U") &&
	   alp.find("a")<alp.find("U") )
		std::cout << "Test 3: Passed" << std::endl;
	else
		std::cout << "Test 3: Failed" << std::endl;

	ul.SetDictionary(std::vector<std::string> ({"abc"}));
	alp = ul.CalculateAlphabet();
	if(alp.find("a")!=std::string::npos &&
	   alp.find("b")!=std::string::npos &&
	   alp.find("c")!=std::string::npos )
		std::cout << "Test 4: Passed" << std::endl;
	else
		std::cout << "Test 4: Failed" << std::endl;

	ul.SetDictionary(std::vector<std::string> ({}));
	alp = ul.CalculateAlphabet();
	if(alp.empty())
		std::cout << "Test 5: Passed" << std::endl;
	else
		std::cout << "Test 5: Failed" << std::endl;

}
