#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "colored_dealt.h"

int N, Q, score[256];
std::string my;

int design(const std::string& C){
	if(++Q > N){
		std::cout << "Query Limit Exceeded" << std::endl;
		exit(0);
	}
	if(C.size() != (size_t) N){
		std::cout << "Invalid Query" << std::endl;
		exit(0);
	}
	for(int i=0; i<N; i++){
		if(C[i] != 'R' && C[i] != 'G' && C[i] != 'B'){
			std::cout << "Invalid Query" << std::endl;
			exit(0);
		}
	}

	std::string str = my + C;

	std::vector<int> sums;
	sums.push_back(0);
	for(int i=0; i<3*N; i++) sums.push_back(sums.back() + score[(int)str[i%(2*N)]]);

	int mx = 0;
	for(int i=N; i<3*N; i++){
		if(mx < sums[i] - sums[i-N]) mx = sums[i] - sums[i-N];
	}

	return mx;
}

int main(){
	std::cin >> my;
	N = my.size();

	score['R'] = 1, score['G'] = 2, score['B'] = 3;
	std::string ans = guess(N);

	if(ans == my) std::cout << "Correct" << std::endl;
	else std::cout << "Wrong Answer" << std::endl;
	return 0;
}
