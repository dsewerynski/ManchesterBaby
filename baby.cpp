#include "baby.h"

using namespace std;

int countt = 0;

int controlInstruction = 0;
char store[32][32];
bool halted = false;

char presentInstruction[32];
char accumulator[32];


int main() {
	loadProgram();
	do {	
		increment_CI();
		fetch();
		decode();

		//break;
		//execute();
		//display_everything();
		countt++;
	} while (countt < 10);

	return 0;
}

void fetch(){
	for (int i = 0; i < 32; i++) {
		presentInstruction[i] = store[controlInstruction][i];
	}
}

void decode(){
	char lineNumber[5];
	for(int  i = 0; i < 5; i++) {
		lineNumber[i] = presentInstruction[i];
	}

	string functionNumber = {presentInstruction[13], presentInstruction[14], presentInstruction[15]};

	int currentFunction = stoi(functionNumber, nullptr, 2);

	cout << "Function: " << currentFunction << endl;
}

void execute() {

}

int loadProgram() {
//	ifstream input( "BabyTest1-MC.txt" );

	ifstream file("BabyTest1-MC.txt");
	if (file.is_open()) {
	    string line;
	    int counter1 = 0;
	    int counter2 = 0;

	    while (getline(file, line)) {
	        for(int i = 0; i < line.length(); i++) {
	        	if(line[i] == '\r' || line[i] == '\n') continue;
	        	store[counter1][counter2] = line[i];
	        	counter2++;
	        }
	        counter2 = 0;
			counter1++;
	    }
	    file.close();
	}

}

void increment_CI() {
	controlInstruction++;
}

void display_everything() {

}