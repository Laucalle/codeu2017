#include <iostream>
#include <vector>
#include <map>
#include <list>

class ParkingLot
{
	int capacity;
public:
	ParkingLot(int N):capacity(N){}
	std::list<std::pair<int,int>> Rearrange(std::vector<int> init_state,
										   std::vector<int> end_state){
		std::map<int,std::pair<int,int>> cars; // current pos, desired pos
		std::list<std::pair<int,int> > moves;
		for (int i=0; i<init_state.size(); i++){
			cars[init_state[i]].first=i;
			cars[end_state[i]].second=i;
		}
		int empty_spot;
		int move_car;
		bool ordered=false;
		while(!ordered){
			if(cars[0].first==cars[0].second){
				ordered = true;
				for(const std::pair<int, std::pair<int,int>> &it: cars){
					if(it.first!=0 && it.second.first!=it.second.second){
						// misplaced car
						move_car = it.first;
						ordered=false;
						break;
					}
				}
			} else {
				ordered = false;
				move_car = end_state[cars[0].first];
			}

			if(!ordered){
				moves.push_back(std::pair<int,int>(cars[move_car].first,cars[0].first));
				std::cout << "from " << cars[move_car].first << " to " << cars[0].first << std::endl;
				empty_spot = cars[0].first;
				cars[0].first = cars[move_car].first;
				cars[move_car].first = empty_spot;
			}
		}

		return moves;
	}
	
};

int main(){
	ParkingLot pl(6);
	std::vector<std::pair<int,int> > moves;
	std::vector<int> test_case_init({1,5,2,0,3,4});
	std::vector<int> test_case_end({5,4,3,1,2,0});

	moves = pl.Rearrange(test_case_init,test_case_end);
	int aux;
	
	for(const std::pair<int,int> &move: moves){
		aux = test_case_init[move.first];
		test_case_init[move.first] = test_case_init[move.second];
		test_case_init[move.second] = aux;
	}
	if(test_case_init==test_case_end){
		std::cout << "Test 1: PASSED" << std::endl;
	} else {
		std::cout << "Test 1: FAILED" << std::endl;
	}

	test_case_init = {0,1,2,3,4,5};
	test_case_end = {5,2,1,4,3,0};

	moves = pl.Rearrange(test_case_init,test_case_end);
		
	for(const std::pair<int,int> &move: moves){
		aux = test_case_init[move.first];
		test_case_init[move.first] = test_case_init[move.second];
		test_case_init[move.second] = aux;
	}
	if(test_case_init==test_case_end){
		std::cout << "Test 2: PASSED" << std::endl;
	} else {
		std::cout << "Test 2: FAILED" << std::endl;
	}
}
