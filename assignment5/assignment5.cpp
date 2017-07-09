#include <iostream>
#include <vector>

class UnknownLanguage
{
	std::vector<std::string> dictionary;
	std::string alphabet;
public:
	UnknownLanguage(std::vector<std::string> dic):dictionary(dic){}
	std::string CalculateAlphabet(){

		alphabet.clear();
		int before, after;

		for(int i = 0; i < dictionary.size()-1; i++){
			for(int j=0; j < dictionary[i].size(); j++){

				// Comparison is done with next word, same character
				if(j < dictionary[i+1].size() && 
					dictionary[i].substr(0, j) == dictionary[i+1].substr(0, j)){

					if(dictionary[i][j]!=dictionary[i+1][j]){
						before = alphabet.find(dictionary[i][j]);
						after = alphabet.find(dictionary[i+1][j]);

						if(before!= std::string::npos || after!=std::string::npos){
							if(before!=std::string::npos && after == std::string::npos){
								// after is not in alphabet yet
								alphabet.insert(alphabet.begin() + before+1, dictionary[i+1][j]);
							} else if( after != std::string::npos && before == std::string::npos){
								// before is not in alphabet yet
								alphabet.insert(alphabet.begin() + after, dictionary[i][j]);
							} else if(after < before){
								// both are, but the order is incorrect
								alphabet.erase(before, 1);
								alphabet.insert(alphabet.begin() + after, dictionary[i][j]);
							}
						} else {
							// both characters are new to the alphabet
							alphabet.push_back(dictionary[i][j]);
							alphabet.push_back(dictionary[i+1][j]);
						}
					}
				} else {
					break;
				}

			}

		}
		return alphabet;
	}

	
};

int main(){
	UnknownLanguage ul(std::vector<std::string> ({"ART","DRTC","DRAC","RAT","CAT","CAR"}));
	std::cout << ul.CalculateAlphabet()<< std::endl;
}
