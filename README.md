# Handicap-Calculator
A program to store golf scores and calcuate your handicap


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include "scores.h"
using namespace std;


double differential(int score,double courseSlope,double courseRating)
{
	double holder = (courseRating-score)*113*-1.0/courseSlope;
	
	return holder;	
}
int readInFile(ifstream & fin, double difference[], scoreEntry scoresEntered[])
{
	
	int tracker=0, cScore, cDate;
	string cName, factorString;
	double cRating, cSlope, cIndex, oldFactor;
	
	
	while(fin >> factorString && tracker <50 )
	{

		fin  >> oldFactor >> cDate >> cName >> cIndex >> cScore>> cRating >> cSlope;
		scoresEntered[tracker].date = cDate;
		scoresEntered[tracker].courseName = cName;
		scoresEntered[tracker].courseRating = cRating;
		scoresEntered[tracker].courseSlope = cSlope;
		scoresEntered[tracker].score = cScore;
		scoresEntered[tracker].index = cIndex;
		difference[tracker] = cIndex;

		tracker++;
		
	}
	return tracker;
}

void findLowest(double difference[], int round, double bestTen[], int place)
{
	double lowest=99;
	int remember=0;
	
	for(int t=0;t<round;t++)
	{
		for(int i=0;i<round;i++)
		{
			if(lowest>difference[i])
			{
				lowest = difference[i];
				remember=i;
			}
		}
	}
	
	difference[remember]=99;
	bestTen[place]=lowest;

	place++;
}

double calcHandicap(int round, double difference[], double bestTen[])
{
	double total=0,place=0;
	int marker=0;
	
	for(int t=0;t<round;t++)
	{
		findLowest(difference,round,bestTen,place); // for (int h=0;h<10;h++ (total+=bestTen[h] }
		place++;	
	}
	while(marker < round && marker < 10 && bestTen[marker] != -100 )
	{
		total+=bestTen[marker];
		marker++;
	}

	return total*1.0/marker;
}

//void removeOldScores(round)

int main()
{
	ifstream fin("diff.txt");
	if(!fin)
	{
		cout << "Error diff.txt not found" << endl;
		return -1;
	}
	scoreEntry scoresEntered[50];
	string entry,courseName;
	int date,score,day;
	double difference[50]={0}, bestTen[10]={-100},courseRating,courseSlope,index;
	scoreEntry roundsPlayed[50];
	int round = readInFile(fin,difference,scoresEntered);

	do
	{		
		cout << "Enter date of round. ddmmyyyy Ex 05032105" << endl;
		cin >> date;
		
		scoresEntered[round].date = date;
		
		cout << "Enter course name" << endl;
		cin >> courseName;
		
		scoresEntered[round].courseName = courseName;
		
		do
		{
		
		cout << "Enter course rating and slope" << endl;
		cin >> courseRating >> courseSlope;
		} while(courseRating > 90 || courseRating < 60 || courseSlope <100 || courseSlope > 170);
	
		scoresEntered[round].courseRating = courseRating;
		scoresEntered[round].courseSlope = courseSlope;
		
		do
		{
		
		cout << "Enter score" << endl;
		cin >> score;
		} while(score < 54 || score > 150);
		
		scoresEntered[round].score = score;
		difference[round] = differential(scoresEntered[round].score,scoresEntered[round].courseSlope,scoresEntered[round].courseRating);
		scoresEntered[round].index = difference[round];
		
		round++;
			
		cout << "Would you like to enter a round? Y/N" << endl;
		cin >> entry;
			
		
	} while(entry == "Y" && round<50);
	ofstream fout("diff.txt");
	double hCap = calcHandicap(round,difference,bestTen);
	
	fout << "Factor: ";
	
	if(hCap<0)
	{
		fout << fixed << setprecision(1) << "+" << hCap*-1 << endl;
	}
	else
	
	fout << << fixed << setprecision(1)  << hCap << endl; // NEED TO ROUND TO A SINGLE DECIMAL PLACE
	
	for(int i=0;i<round;i++)
	{
		fout << scoresEntered[i].date << "	" << scoresEntered[i].courseName // fin  >> oldFactor >> cDate >> cName >> cIndex >> cScore>> cRating >> cSlope;
		<< "    " << scoresEntered[i].index << "    " 
		<< scoresEntered[0].score << "    " << scoresEntered[i].courseRating 
		<< "    " <<  scoresEntered[i].courseSlope << "    " <<  endl;
	}
	
	fout.close();
	return 0;
}
