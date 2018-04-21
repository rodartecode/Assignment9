// Assignment9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Patient>
#include <iostream>

#include "PrecondViolatedExcep.h"

using namespace std;

class Patient
{
private:
	string name;
	int priority;

public:
	string getName()
	{
		return name;
	}

	int getPriority()
	{
		return priority;
	}

	void display()
	{
		cout << name;
	}

	bool operator<(const Patient &right)
	{
		if (priority < right.priority)
			return true;
		else
			return false;
	}


	bool operator>(const Patient &right)
	{
		if (priority > right.priority)
			return true;
		else
			return false;
	}


	bool operator==(const Patient &right)
	{
		if (priority == right.priority)
			return true;
		else
			return false;
	}
};



class Heap
{
private:
	static const int ROOT_INDEX = 0;
	static const int DEFAULT_CAP = 21;
	string* patients;
	int itemCount;
	int maxItems;

public:
	Heap()
	{
		itemCount = 0;
		maxItems = DEFAULT_CAP;
		patients = new string[DEFAULT_CAP];
	}


	Heap(const string anArray[], const int arraySize) :
		itemCount(arraySize), maxItems(DEFAULT_CAP)
	{
		patients = new string[maxItems];

		for (int i = 0; i < itemCount; i++)
			patients[i] = anArray[i];


	}

	int getItemCount()
	{
		return itemCount;
	}

	int getParentIndex(int root)
	{
		if (root > 0)
			return (root - 1) / 2;
		else
			return 0;
	}

	int getLeftChildIndex(int root)
	{
		return (2 * root) + 1;
	}

	int getRightChildIndex(int root)
	{
		return (2 * root) + 2;
	}

	bool isEmpty() const 
	{
		return itemCount == 0;
	}

	bool isLeaf(int root)
	{
		if (getLeftChildIndex(root) < itemCount - 1)
			return false;
		else
			return true;
	}


	bool add(string newPatient)
	{
		if (itemCount < maxItems)
		{
			patients[itemCount] = newPatient;

			int newDataIndex = itemCount;
			bool inPlace = false;
			while ((newDataIndex >= 0) && !inPlace)
			{
				int parent = getParentIndex(newDataIndex);

				if (patients[newDataIndex] <= patients[parent])
					inPlace = true;
				else
				{
					string temp = patients[newDataIndex];
					patients[newDataIndex] = patients[parent];
					patients[parent] = temp;
					newDataIndex = getParentIndex(newDataIndex);
				}
			}

			itemCount++;
			return true;
		}

		else
			return false;
	}


	string peekTop()
	{
		if (!isEmpty())
			return patients[ROOT_INDEX];
		else
			throw PrecondViolatedExcep("Empty heap.");
	}


	bool remove()
	{
		if (!isEmpty())
		{
			patients[ROOT_INDEX] = patients[itemCount - 1];
			itemCount--;
			rebuild(ROOT_INDEX, patients, itemCount);
			return true;
		}
		else
		{
			cout << "Empty Heap.";
			return false;
		}
	}


	bool rebuild(int root, string* patients, int itemCount)
	{
		if (!isLeaf(root))
		{
			int largerChild = getLeftChildIndex(root);

			if (getRightChildIndex(root) >= itemCount - 1)
			{
				int rightChild = largerChild + 1;
				
				if (patients[rightChild] > patients[largerChild])
					largerChild = rightChild;
			}

			if (patients[root] < patients[largerChild])
			{
				string temp = patients[root];
				patients[root] = patients[largerChild];
				patients[largerChild] = temp;

				rebuild(largerChild, patients, itemCount);
			}
		}
		return true;
	}


	bool clear()
	{
		while (!isEmpty())
		{
			remove();
		}
		return true;
	}
};




int main()
{
	Heap ER;

	ER.add("5 Bob");
	ER.add("9 Mary");
	ER.add("1 Max");

	cout << ER.peekTop() << " will now see the doctor.\n";
	ER.remove();

	ER.add("3 Julio");
	ER.add("7 Stacy");
	ER.add("4 Paul");
	ER.add("2 Reiko");
	ER.add("6 Jennifer");
	ER.add("5 Chang");

	cout << ER.peekTop() << " will now see the doctor.\n";
	ER.remove();
	cout << ER.peekTop() << " will now see the doctor.\n";
	ER.remove(); cout << ER.peekTop() << " will now see the doctor.\n";
	ER.remove();
	return 0;
}