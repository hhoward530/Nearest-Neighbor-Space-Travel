#include "LList.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
Written By: Hunter Howard
Due: 20 Oct 2022
EECS 4590 Algorithms Project 1

LList.cpp
This file contains the function definitions for the LList.h file
The functions that can be performed on our linked list are defined here
*/

//constructor
LList::LList()
{
	start = NULL;	
}

//deconstructor
LList::~LList()
{
	node* here = start;		//start at beginning
	node* next;				//1 ahead of current position
	while (here != NULL)	//as long as we still have a node
	{
		next = here->next;	//save a reference to the next node
		delete here;		//delete this node
		here = next;		//move over the deleted node
	}
	start = NULL;	//make sure there are no old references to a non-existant node
}

//This function creates a new star and adds it to the beginning of our linked list
void LList::insert(int ID, double dist, double x, double y, double z)
{
	node* p = start;		//start at the beginning of the ist

	node* n = new node;		//create a new node
	n->ID = ID;				//the field to hold the star ID
	n->dist = dist;			//field to hold distance from where we are
	n->x = x;				//star's x value
	n->y = y;				//star's y value
	n->z = z;				//stars z value
	n->next = start;		//point new node to the start

	start = n;				//our new node becomes the new start
}

//this function removes a star from the list that contains the given ID value
int LList::remove(int ID)
{
	node* p = start;
	node* q = NULL;

	while (p != NULL)			//while we still have nodes
	{
		if (p->ID == ID)		//if we find the node we're looking for
		{
			if (q == NULL) 
				start = p->next;	//advance p if we're at the beginning
			else  q->next = p->next;//otherwise q tracks what's behind p
			delete p;				//delete p
			return 0;
		}
		q = p;			//advance q to p
		p = p->next;	//advance p to the next node
	}
	return -1;
}

//this function finds the star with the smallest distance and returns it's ID
int LList::min()
{
	node* p = start;		//start at the beginning
	double min = p->dist;	//our minimum distance
	int minID = p->ID;		//ID of star that is closest

	while (p->next != NULL)	//as long as we can keep moving 
	{
		p = p->next;		//look at the next star
		if (p->dist < min && p->dist > 0)	//if the distance is closer and we aren't currently on the star
		{
			min = p->dist;		//this star is our new closest star
			minID = p->ID;		//get the star's ID
		}
	}
	return minID;				//returns the ID of the closest star
}

//This function gets the distance of a star given its ID
double LList::getDist(int ID)
{
	double dist;			//our distance
	node* p = start;		//start at the beginning
	while (p != NULL)		//while we still have stars
	{
		if (p->ID == ID)	//if we find the star we're looking for
		{
			dist = p->dist;	//get its distance from us
			return dist;
		}
		p = p->next;		//move to the next star if we haven't found what were looking for
	}
	return -1;
}

//this function removes all stars from our list that are farther than we can still travel
void LList::removeExtra(int travelDist)
{
	node* a = start;				//start at the beginning
	node* b = a;					//keep track of where weve been
	while (a != NULL)				//as long as we still have stars
	{
		if (a->dist > travelDist)	//if the distance of our current star is more than we can go
		{
			b = a->next;			//b points to the next star
			remove(a->ID);			//delete the current star
			a = b;					//move to the next star
		}
		else
			a = a->next;			//if we dont delete the star, move to the next
	}
}

//This function finds the star we are on (dist = 0) and returns its ID
int LList::getCurrentStar()
{
	node* p = start;		//start at the beginning
	while (p != NULL)		//while we still have stars
	{
		if (p->dist == 0)	//if our distance is 0, we are on the star
		{
			return p->ID;	//return its ID
		}
		p = p->next;		//move to the next star if we're not on it
	}
	return -1;
}

//This function gets the x,y,z values of the star we are currently on
//and recalulates how far away the other stars are from the star we are on
void LList::recalcDist(int currentID)
{
	double x = 0, y = 0, z = 0;
	node* p = start;
	node* q = start;

	while (q != NULL)			//while we still have stars
	{
		if (q->ID == currentID)	//look for the star we are on
		{
			x = q->x;			//record its x,y,z values
			y = q->y;
			z = q->z;
			break;				//exit loop when we find our star
		}
		q = q->next;			//keep moving if we havent found our star yet
	}

	while (p != NULL)			//while we still have stars
	{							//recalculate the new distances from our new position
		p->dist = sqrt(pow((p->x - x),2) + pow((p->y - y), 2) + pow((p->z - z), 2));
		p = p->next;			//move to the next
	}
}

//this function checks to see oif our linked list is empty
int LList::isempty()
{
	if (start == NULL)	//if our start points to nothing
	{
		return 0;		//the list is empty
	}
	return 1;			//otherwise its not empty
}