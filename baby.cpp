#include "baby.h"

using namespace std;

char controlInstruction[33];

char store[32][33];

char presentInstruction[33];

char accumulator[33];

char currentFunction[4];

char currentOperand[6];

bool halted = false;


int main() {
	//Null terminate char arrays
	for(int i = 0; i < 32; i++) {
		store[i][32] = '0';
	}

	for(int i = 0; i < 32; i++) {
		controlInstruction[i] = '0';
	}
	controlInstruction[32] = '\0';

	presentInstruction[32] = '\0';
	accumulator[32] = '\0';
	currentFunction[4] = '\0';
	currentOperand[5] = '\0';

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

char* reverse(char* toReverse) {
	//Use temp to avoid switching 
	int numCharacters = string(toReverse).length();

	char* tempChar = new char[numCharacters];
	copy(toReverse, toReverse+numCharacters, tempChar);

    for (int i=0; i<numCharacters/2; i++)
    { 
    	swap(tempChar[i], tempChar[numCharacters-i-1]); 
    }

    return tempChar;
}

char* intToBinary(int number) {
	// Turn the int to a binary string
	string binary = bitset<32>(number).to_string();

	// Convert to char array
    char char_array[33];
    strcpy(char_array, binary.c_str());

    // Convert to big-endian
    char* bigEndian = reverse(char_array);

	return bigEndian;
}

int binaryToInt(char* number) {
	// From big-endian to little-endian for conversion
	char* littleEndian = reverse(number);

	// Handle negative numbers
	auto ul = stoul(littleEndian, nullptr, 2);
    int result = ul;

    delete littleEndian;

    return result;
}


int locationToInt(char* operand) {
	int location = binaryToInt(operand);

	char tempBinary[33];
	for(int i = 0; i < 32; i++) {
		tempBinary[i] = store[location][i];
	}
	tempBinary[32] = '\0';

	return binaryToInt(tempBinary);
}

void fetch(){
	int control = binaryToInt(controlInstruction);
	for (int i = 0; i < 32; i++) {
		presentInstruction[i] = store[control][i];
	}
}

void decode(){
	//Store the bits, reverse the order.
	for(int i = 13; i < 16; i++) {
		currentFunction[i - 13] = presentInstruction[i];
	}

	//Store the bits
	for(int i = 0; i < 5; i++) {
		currentOperand[i] = presentInstruction[i];
	}
}

void execute() {
	int func = binaryToInt(currentFunction);
	switch(func) {
		case 0:{ // JMP
			char* result = intToBinary(locationToInt(currentOperand));
			
			for(int i = 0; i < 32; i++){
				controlInstruction[i] = result[i];
			}

			delete result;
			break;
		}
		case 1: { // JRP
			char* result = intToBinary(binaryToInt(controlInstruction) + locationToInt(currentOperand));

			for(int i = 0; i < 32; i++){
				controlInstruction[i] = result[i];
			}

			delete result;
			break;
		}
		case 2: { // LDN
			char* result = intToBinary(locationToInt(currentOperand) * -1);

			for(int i = 0; i < 32; i++){
				accumulator[i] = result[i];
			}

			delete result;
			break;
		}
		case 3: { // STO
			int location = binaryToInt(currentOperand);
			
			for(int i = 0; i < 32; i++) {
				store[location][i] = accumulator[i];
			}
			break;
		}
		case 4: // SUB
		case 5: { //SUB
			int result = binaryToInt(accumulator) - locationToInt(currentOperand);

			char* binary = intToBinary(result);
			for(int i = 0; i < 32; i++) {
				accumulator[i] = binary[i];
			}

			delete binary;

			break;
		}
		case 6: { // CMP
			if(binaryToInt(accumulator) < 0) {
				increment_CI();
			}
			break;
		}
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
	char* result = intToBinary(binaryToInt(controlInstruction) + 1);

	for(int i = 0; i < 32; i++){
		controlInstruction[i] = result[i];
	}
}

void display_everything() {
	cout << "Store:" << endl;
	for (int i = 0; i < 32; i++){
		if(store[i][0] == '\0') continue;

		for (int j = 0; j < 32; j++){
			cout << store[i][j];
		}
		cout << endl;
	}

	cout << "Control Instruction = " << controlInstruction << " (" << binaryToInt(controlInstruction) << ")" << endl;
	
	cout << "Current Instruction = ";
	for (int i = 0; i < 32; i++){
		cout << presentInstruction[i];
	}

	cout << endl;
	cout << "Current Function = " << currentFunction << " (" << binaryToInt(currentFunction) << ")" << endl;
	cout << "Current Operand = " << currentOperand << " (" << binaryToInt(currentOperand) << ")" << endl;
	cout << "Accumulator = " << accumulator << " (" << binaryToInt(accumulator) << ")" << endl;
	cout << endl;
}