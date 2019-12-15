#ifndef SCORE_H
#define SCORE_H

#include <tinyxml2.h>
#include <vector>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

struct Score{
	int level;
	float time;
	std::string name;
	Score(int l, float t, std::string n){
		level = l;
		time = t;
		name = n;
	}
};

std::vector<Score> ReadScoreFile(char* filename);
void WriteScoreFile(char* filename, std::vector<Score> scores);
bool AddScore(std::vector<Score>& scores, Score new_score);
#endif //SCORE_H
