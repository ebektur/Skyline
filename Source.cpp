#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;
//int label;



struct HalfBuilding
{
	string side; //LEFT or RIGHT
	int label;

	int x, y; //BIR BINA = IKI HALF BUILDING, LEFT, RIGHT
	HalfBuilding() {
		side = "";
		label = 0;
		x = 0;
		y = 0;

	}

	bool operator == (const HalfBuilding& compare) const
	{
		if ((compare.y == y) && (compare.label == label))
		{
			return true;
		}
		return false;
	}

	bool operator < (const HalfBuilding& compare) const
	{
		if (y < compare.y)
		{
			return true;
		}
		return false;
	}

	//private:
	//
	//	int value;
};


class ModifiedPQ
{
public:
	ModifiedPQ(int size) : currentSize(0), priorityqueue(size) {
		//vector<HalfBuilding> priorityqueue(size);
		//set first one as dummy
		//vector<HalfBuilding> priorityqueue(size);

		for (int x = 0; x < size; ++x)
			priorityqueue[x] = HalfBuilding();

	}
	~ModifiedPQ();
	vector<HalfBuilding> array;
	vector<int> location; //labels

	//bool isEmpty() const;
	//bool isFull() const;

	void insert(const HalfBuilding& x);

	/*void makeEmpty();*/
	HalfBuilding GetMax();
	/*int GetMax1();*/
	void Remove1(int label);
	/*HalfBuilding Remove(int label);*/

private:
	int            currentSize; // Number of elements in heap
	  // The heap array
	vector<HalfBuilding> priorityqueue;

	/*void insert(HalfBuilding value, int label);*/ //value = height label = identifying number
	/*void percolateDown(int hole);*/
	/*bool IsEmpty();*/


};

//ModifiedPQ::ModifiedPQ(int size)
//{
//	priorityqueue(size);
//
//
//}

ModifiedPQ::~ModifiedPQ()
{


}


HalfBuilding ModifiedPQ::GetMax() //priority queue, find highest height
{ 
	return priorityqueue[1];
}


void ModifiedPQ::Remove1(int label)
{
	int child;
	bool check = false;
	HalfBuilding itr;

	for (int s = 1; s < priorityqueue.size() && check == false; s++)
	{
		if (priorityqueue[s].label == label)
		{
			check = true;
			//remove priorityqueue[s]
			priorityqueue.erase(priorityqueue.begin() + s);
			double hole = s;
			itr = priorityqueue[hole];
			--currentSize;

			for (; hole * 2 <= currentSize; s = hole)
			{
				child = hole * 2;
				if (child != currentSize && priorityqueue[child + 1].y > priorityqueue[child].y)
				{
					child++;
					if (priorityqueue[child].y > itr.y)
					{
						priorityqueue[hole] = priorityqueue[child];

					}
					else
						break;
				}

			}
		}
	}
		if (check == false)
		{
			return;
			//no match, dont remove
		}

	
}



void ModifiedPQ::insert(const HalfBuilding& x) //PRIORITY QUEUE'DA BIR SORUN VAR, DOGRU GIRMIYO VERILER. 
{
	int hole = ++currentSize;

	for (; hole > 1 && x.y > priorityqueue[hole / 2].y; hole /= 2)
		priorityqueue[hole] = priorityqueue[hole / 2];
	priorityqueue[hole] = x;




	//if (isFull()) { return; } //edge case

	// Percolate up
	// Note that instead of swapping we move the hole up
	//int hole = ++currentSize;
	//int hole = priorityqueue.size() - 1; 


	//for (; hole > 1 && x.y > array[hole].y; hole--)
	//{
	//	array[hole] = array[--hole];
	//}
	//array[hole] = x;

	//int index = hole - 1;

	//while (x.x < priorityqueue[hole].x && hole>1)
	//{
	//	hole--;
	//}


	

	//for (; hole > 1 && x.x > priorityqueue[hole / 2].x; hole /= 2) //<
	//{
	//	priorityqueue[hole] = priorityqueue[hole / 2];
	//}

	//for (; hole > 1 && x.x < priorityqueue[hole--].x; hole --) //<
	//{
	//	priorityqueue[hole] = priorityqueue[hole--];
	//}

	//priorityqueue[hole] = x;
	
}

bool check(int i)
{
	if (i == 0)
	{
		return true;
	}

	return false;
}




int main()
{
	int count = 0;
	int max = -2147483648;
	const string ITEM_NOT_FOUND = "item is not found";
	string line;
	string line2;
	bool isZero = false;

	//ifstream myfile2("queries.txt");
	ifstream myfile("input2.txt");
	stringstream ss;
	stringstream queries;
	//Node* rootPtr = nullptr; //root of newly created node with each line

	//data variables from the text
	int building_count;
	int x_left, x_right, coord_y;


	if (myfile.is_open())
	{
		getline(myfile, line);
		ss << line;
		ss >> building_count; //catch negative numbers
		ModifiedPQ mpq(2 * building_count + 1);
		

		while (getline(myfile, line))
		{
			istringstream ss(line);
			//ss << line;
			ss >> x_left >> coord_y >> x_right;

			if (x_left > 0 && x_right > 0 && coord_y > 0)
			{
				HalfBuilding left;
				HalfBuilding right;

				//assign xs
				left.x = x_left;
				right.x = x_right;

				if (x_left > x_right && x_left > max) { max = x_left; }
				else if (x_right > x_left && x_right > max) { max = x_right; }

				//assign same y
				left.y = coord_y;
				right.y = coord_y;

				//assign sides
				left.side = "LEFT";
				right.side = "RIGHT";

				//location
				mpq.location.push_back(count);

				//labels just be equal
				left.label = right.label = count++;

				mpq.array.push_back(left);
				mpq.array.push_back(right);

				if (check(x_left) == true)
				{
					isZero = true;
				}

				


			}

			//sort the elements in the array
			for (int i = 0; i < mpq.array.size(); i++)
			{
				for (int j = i + 1; j < mpq.array.size(); j++)
				{
					if (mpq.array[i].x > mpq.array[j].x)
					{
						HalfBuilding temp = mpq.array[i];
						mpq.array[i] = mpq.array[j];
						mpq.array[j] = temp;
					}
				}
			}
		}

		int loc = 0;

		for (int k = 0; k < mpq.array.size(); k++)
		{
			if (mpq.array[k].side == "LEFT")
			{
				mpq.location[loc++] = mpq.array[k].label;
			}
		}

			//construct an empty priority queue
		   // priority_queue<HalfBuilding> myModifiedPQ;
			//ModifiedPQ myModifiedPQ;
			int size = mpq.array.size();
			int getheight;
			//int count;

			//PRINT 0,0 HERE

			if (isZero == false)
			{
				cout << "0 0" << endl;
			}


			/*for (int j = 0; mpq.array[j].x < max; j++)*/
			for(int j = 0; j < size; j++)
			{
				

				if (mpq.array[j].side == "LEFT")
				{
					mpq.insert(mpq.array[j]);
					if (mpq.GetMax() == mpq.array[j])
					{
						cout << mpq.array[j].x << " " << mpq.GetMax().y << endl;
					}

				}

				if (mpq.array[j].side == "RIGHT")
				{

					mpq.Remove1(mpq.array[j].label); //6 sagda label 11?

						if (mpq.GetMax() < mpq.array[j]) //print the change
							{

								cout << mpq.array[j].x << " " << mpq.GetMax().y << endl;

							}
						//else
						//{
						//	mpq.Remove1(mpq.array[j].label);
						//}

				}

			}

			cout << "hello";
		
	}

	else { cout << "Unable to open file"; }


	return 0;
	
}