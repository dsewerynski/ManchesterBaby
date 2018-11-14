#include "baby.h"

using namespace std;

int controlInstruction = 0;
char store[32][32];
bool halted = false;

char presentInstruction[32];
char accumulator[32];

int currentFunction = 0;
int currentOperand = 0;


int main() {
	loadProgram();

	do {	
		increment_CI();
		fetch();
		decode();
		execute();
		//display_everything();
	} while (!halted);

	return 0;
}

void fetch(){
	for (int i = 0; i < 32; i++) {
		presentInstruction[i] = store[controlInstruction][i];
	}
}

void decode(){
	//Store the bits, reverse the order.
	string functionNumber = {presentInstruction[15], presentInstruction[14], presentInstruction[13]};
	currentFunction = stoi(functionNumber, nullptr, 2);

	//Store the bits, reverse the order.
	string operandNumber = {presentInstruction[4], presentInstruction[3], presentInstruction[2], presentInstruction[1] , presentInstruction[0]};
	currentOperand = stoi(operandNumber, nullptr, 2);
}

void execute() {
	switch(currentFunction) {
		case 0: // JMP
			controlInstruction = currentOperand;
			break;
		case 1: // JRP
			controlInstruction = controlInstruction + currentOperand;
			break;
		case 2: // LDN
			
			break;
		case 3: // STO

			break;
		case 4: // SUB
		case 5: //SUB

			break;
		case 6: // CMP

			break;
		case 7: // STP
			halted = true;
			break;
	}

}

int loadProgram() {
	ifstream file("BabyTest1-MC.txt");
	if (file.is_open()) {
	    string line;
	    int counter1 = 0;
	    int counter2 = 0;

	    while (getline(file, line)) {
	        for(int i = 0; i < (int)line.length(); i++) {
	        	if(line[i] == '\r' || line[i] == '\n') continue;
	        	store[counter1][counter2] = line[i];
	        	counter2++;
	        }
	        counter2 = 0;
			counter1++;
	    }
	    file.close();
	}
	return 0;
}

void increment_CI() {
	controlInstruction++;
}

void display_everything() {

}