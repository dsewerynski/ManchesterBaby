#include "baby.h"

using namespace std;

int32_t controlInstruction = 0;
char store[32][32];
bool halted = false;

char presentInstruction[32];
char accumulator[32];

int32_t currentFunction = 0;
char currentOperand[5];


int main() {
	loadProgram();

	do {	
		increment_CI();
		fetch();
		decode();
		execute();
		display_everything();
	} while (!halted);

	return 0;
}

void fetch(){
	for (int i = 0; i < 32; i++) {
		presentInstruction[i] = store[controlInstruction][i];
	}
}

char* intToBinary(int number) {
	string binary = bitset<32>(number).to_string();

	char newBinary[32];
	for(int i = 31; i >= 0; i--) {
		newBinary[i] = binary[i];
	}
}

int binaryToInt(char* number) {
	int numCharacters = sizeof(number);
    for (int i=0; i<numCharacters/2; i++)
    { 
    	swap(number[i], number[numCharacters-i-1]); 
    }

	return stoi(number, nullptr, 2);
}

void decode(){
	//Store the bits, reverse the order.
	string functionNumber = {presentInstruction[15], presentInstruction[14], presentInstruction[13]};
	currentFunction = stoi(functionNumber, nullptr, 2);

	//Store the bits, reverse the order.
	currentOperand[0] = presentInstruction[0];
	currentOperand[1] = presentInstruction[1];
	currentOperand[2] = presentInstruction[2];
	currentOperand[3] = presentInstruction[3];
	currentOperand[4] = presentInstruction[4];
}

int locationToInt(char* operand) {
	// {}
	int location = binaryToInt(operand);
	string binaryNumber = "";
	for(int i = 31; i >= 0; i--) {
		binaryNumber += store[location][i];
	}

	return stoi(binaryNumber, nullptr, 2);
}

void execute() {
	switch(currentFunction) {
		case 0: // JMP
			controlInstruction = locationToInt(currentOperand);
			break;
		case 1: // JRP
			controlInstruction = controlInstruction + locationToInt(currentOperand);
			break;
		case 2: // LDN
			accumulator = locationToInt(currentOperand) * -1;
			break;
		case 3: // STO

			//currentOperand = accumulator;
			break;
		case 4: // SUB
		case 5: //SUB
			//accumulator -= locationToInt(currentOperand);
			break;
		case 6: // CMP
			if(accumulator < 0){ controlInstruction += 1; }
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
	cout << "Control Instruction = " << controlInstruction << endl;
	cout << "Current Instruction = ";
	for (int i = 0; i < 32; i++){
		cout << presentInstruction[i];
	}
	cout << endl;
	cout << "Current Function = " << currentFunction << endl;
	cout << "Current Operand = " << currentOperand << endl;
	cout << "Accumulator = " << accumulator << endl;
	cout << endl;
}