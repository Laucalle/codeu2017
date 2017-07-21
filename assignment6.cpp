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
	pl.Rearrange({1,5,2,0,3,4},{5,4,3,1,2,0});
}