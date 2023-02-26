// AlgorithmsProject1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "LList.h" //implementation of singly linked list
using namespace std;

/*
Written By: Hunter Howard
Due: 20 Oct 2022
EECS 4590 Algorithms Project 1

AlgorithmsProject1.cpp
The purpose of this file is to create a linked list containing stars and determine how
many stars can be visited in a given distance. The data is read in using a .csv file
The stars that are visited are stored in a vector and printed. This is done by repeatedly
finding the next-closest star and moving to it, keeping track of where we've been

*******NOTES FOR FUNCTION********
The file path is hard coded ON LINE 71, it must be changed to be where the .csv file 
trying to be read is stored.

*/

void createLList(LList* stars,vector<string> rows);//read in .csv file and create Linked List

int main(int argc, char* argv[2])
{
	auto start = chrono::steady_clock::now();

	LList* stars = new LList(); //will hold our stars
	vector<int> path;			//will hold our path
	vector<string> rows;		//will gather info about stars from csv file
	double travelDist = stod(argv[1]);
	cout << "Length = " << travelDist << ": ";
	double distanceGone = 0;

	createLList(stars, rows);  //read in file and generate a linked list
	
	while (travelDist > 0)
	{
		stars->removeExtra(travelDist); //remove any stars from the list with a distance greater than our travel distance

		//record our current star -- find the star whose distance is 0 -- record its ID -- remove from list of available stars
		int on = stars->getCurrentStar();	//get our cuurent star's ID
		path.push_back(on);					//add the star we visited to our total path		  
		stars->remove(path.back());			//remove the star we've visted from
		if (stars->isempty() == 0)			//check to see if have any stars left to visit
			break;							//if there are no more stars left to visit, exit loop
		int min = stars->min();				//gives ID of next closest star
		distanceGone = stars->getDist(min); //gives distance travelled from previous star to next closest
		travelDist -= distanceGone;			//calculate how much further we can go
		stars->recalcDist(min);				//recalulate distances from the star we are on
	}

	auto end = chrono::steady_clock::now();
	auto time = end - start;
	for (int i = 0; i < path.size(); i++)	//print the contents of our path
	{
		cout << path[i] << " ";
	}
	cout << "\nRan in: " << chrono::duration <double, milli>(time).count() << " ms" << endl;

}

//The purpose of this function is to read in the .csv file and generate the linked list of stars from it
void createLList(LList* stars, vector<string> rows)
{					//THIS STRING MUST BE CHANGED IF THE FILE PATH CHANGES
	fstream file("C:\\Users\\hhowa\\Downloads\\small.csv", ios::in); //open the file
	if (!file.good())
	{
		cout << "Cannot open file. Please check that the file path is entered correctly." << endl;
		exit(0);
	}
	string row, column;			//store info from csv file
	int ID;
	double x, y, z, dist;

	getline(file, row);				//read in first row to ignore titles
	//for (int i = 0; i < 100; i++)	//for X NUMBER OF rows  
	while(!file.eof())
	{
		rows.clear();					//clear old data out of vector
		if (getline(file, row))//read in the next row from the csv
		{	
			stringstream ss(row);			//look at each specific row
			while (getline(ss, column, ','))//divide the row into columns
			{
				rows.push_back(column);		//add each individual column as an index in the vector
			}
			ID = stoi(rows[0]);				//rows[0] contains the ID
			dist = stod(rows[9]);			//rows[9] contains the dist
			x = stod(rows[17]);				//rows[17] contains x
			y = stod(rows[18]);				//rows[18] contains y
			z = stod(rows[19]);				//rows[19] contains z
			stars->insert(ID, dist, x, y, z);//insert the star into our LList
		}
	}
}