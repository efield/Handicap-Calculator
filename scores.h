#ifndef scores_H
#define scores_H
#include <iostream>
#include <fstream>


struct scoreEntry
{
	std::string courseName;
	int score;
	double courseRating;
	double courseSlope;
	double index;
	double date;	
};

#endif
