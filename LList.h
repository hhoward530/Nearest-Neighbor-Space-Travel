#pragma once
#include <string>
using namespace std;

/*
Written By: Hunter Howard
Due: 20 Oct 2022
EECS 4590 Algorithms Project 1

LList.h
This file contains the function and node initializations for our linked list

*/

class LList
{
public:

	LList(); //constructor
	~LList(); //deconstructor

	void insert(int ID, double dist, double x, double y, double z); //adds star to linked list
	int  remove(int ID); //deletes star fromlinked list given its ID
	int min(); //returns ID of closest star
	double getDist(int ID); //gets the distance of a star given an id
	void removeExtra(int travelDist); //removes stars further than we can travel
	int getCurrentStar(); //get the ID of the star we are at
	void recalcDist(int currentID); //recalulates star distances from our current position
	int isempty(); //checks if our linked list of stars is empty

private:

	struct node {
		int ID = NULL;
		double dist = NULL;
		double x = NULL;
		double y = NULL;
		double z = NULL;
		node* next = NULL;
	};

	node* start = NULL;	//points to first node in the linked list

};

