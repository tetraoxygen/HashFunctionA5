#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <math.h>

long long asinineHash(std::string str) {
	if (str.length() < 2) {
		return 0xBAADF00D;
	}
	
	int firstBytes = (str[0] << 8) + str[1];
	int lastBytes = (str[str.length() - 1] << 8) + str[str.length()];

	return str.length() * (
			lastBytes
			/
			firstBytes
		);
}

int main() {
	int collisions[45402] = { 0 };

	std::ofstream dataFile;
	dataFile.open("hashresults.csv");
	
	std::fstream wordsFile;
	
	wordsFile.open("words.txt", std::ios::in); 
	std::string currentLine;
	
	double wordsCounted = 0;
	while(getline(wordsFile, currentLine)) { 
		std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::tolower);
		collisions[asinineHash(currentLine) % 45402] = collisions[asinineHash(currentLine) % 45402] + 1;
		wordsCounted++;
	}
	
	wordsFile.close();
	
	double totalCollisions = 0;
	for (int i = 0; i < 45402; i++) {
		dataFile << collisions[i] << ", ";
		if (collisions[i] > 1) {
			totalCollisions++;
		}
	}
	
	
	dataFile << "\n";
	dataFile.close();
	
	std::cout << "CS 260: A6 hashing, Charlie Welsh, " << (totalCollisions / wordsCounted) * 100 << "%"<< std::endl;
}
