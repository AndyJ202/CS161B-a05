/******************************************************************************
# Author:           Andy Joy
# Assignment:       Assignment 5
# Date:             11/07/2026
# Description:      
#                   
#                   
# Input:            
#                   
# Output:           
#                   
# Sources:          zyBooks (12.1-12.8), Sample A05.
#******************************************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;

//Constants
const int MAXCHAR = 101;
const int MAXROW = 101;

//Function prototypes
void welcome();
bool openFile(ifstream& inFile, char fileName[]);
int inFileToArray(ifstream& inFile, char makeModel[][MAXCHAR], int milePerGallon[], int horsepower[], int weight[]);
void printList(char makeModel[][MAXCHAR], int milePerGallon[], int horsepower[], int weight[], int count);
void minMaxCalc(char makeModel[][MAXCHAR], int milePerGallon[], int count);
void averageCalc(int weight[], int count);

//Main function
int main() {
  ifstream inFile;

  char fileName [MAXCHAR];
  char makeModel [MAXROW][MAXCHAR];
  int milePerGallon [MAXCHAR] = {0};
  int horsepower [MAXCHAR] = {0};
  int weight [MAXCHAR] = {0};
  int count = 0;

  welcome();

	cout << "\nEnter file name: ";
	cin.getline(fileName, MAXCHAR);
 
  if (!openFile(inFile, fileName)) {
    cout << "File did not open. Program terminating!!!" << endl;
    return 1;
  }
  count = inFileToArray(inFile, makeModel, milePerGallon, horsepower, weight);
  printList(makeModel, milePerGallon, horsepower, weight, count);
  minMaxCalc(makeModel, milePerGallon, count);
  averageCalc(weight, count);

  inFile.close();
  cout << "\nThank you for using my program!" << endl;
  return 0;
}

//Welcome function
void welcome() {
  cout << "Welcome to my automobile data analysis program!" << endl;
}

//Function to open file, returns true/false if file does not open
bool openFile(ifstream &inFile, char fileName[]) {
  inFile.open(fileName);
  if (!inFile) {
    return false;
  }
  return true;
}

int inFileToArray(ifstream& inFile, char makeModel[][MAXCHAR], int milePerGallon[], int horsepower[], int weight[]) {
  int count = 0;
  char strDiscard[MAXCHAR];
  int intDiscard;

  inFile.ignore(200, '\n');
  while (!inFile.eof()) {
    inFile.getline(makeModel[count], MAXCHAR, ';');
    inFile >> milePerGallon[count];
    inFile.ignore(5, ';');
    inFile >> horsepower[count];
    inFile.ignore(5, ';');
    inFile >> weight[count];
    inFile.ignore(5, '\n');
    count++;
  }
  inFile.clear();
	inFile.seekg(0);
  return count;
}

void printList(char makeModel[][MAXCHAR], int milePerGallon[], int horsepower[], int weight[], int count) {
  cout << "\n" << left << setw(35) << "Make & Model" << setw(10) << "MPG" << setw(10) << "HP" << "Weight" << endl;
  cout << left << setw(35) << "____________________________" << setw(10) << "___" << setw(10) << "___" << "______" << endl;

  for (int i = 0; i < count; i++) {
    cout << left << setw(35) << makeModel[i] << setw(10) << milePerGallon[i] << setw(10) << horsepower[i] << weight[i] << endl;
  }
}

void minMaxCalc(char makeModel[][MAXCHAR], int milePerGallon[], int count){
  int minMilePerGallon = milePerGallon[0];
  char minMakeModel [MAXCHAR];
  int maxMilePerGallon = milePerGallon[0];
  char maxMakeModel [MAXCHAR];
  
  strcpy(minMakeModel, makeModel[0]);
  strcpy(maxMakeModel, makeModel[0]);
 
  for (int i = 0; i < count; i++) {
    if (milePerGallon[i] < minMilePerGallon) {
      minMilePerGallon = milePerGallon[i];
      strcpy(minMakeModel, makeModel[i]);
    }
    if (milePerGallon[i] > maxMilePerGallon) {
      maxMilePerGallon = milePerGallon[i];
      strcpy(maxMakeModel, makeModel[i]);
    }
  }
  cout << "\nThe car with the best MPG is the " << maxMakeModel << " at " << maxMilePerGallon << " MPG." << endl;
  cout << "The car with the worst MPG is the " << minMakeModel << " at " << minMilePerGallon << " MPG." << endl;
}

void averageCalc(int weight[], int count){
  double totalWeight = 0;
  
  for (int i = 0; i < count; i++) {
    totalWeight += weight[i];
  }
  cout << fixed << setprecision(0);
  cout << "\nThe average car weight is approximately " << totalWeight / count << " lbs." << endl;
}