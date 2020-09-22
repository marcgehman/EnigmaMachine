/*
* Marc Gehman's implementation of the Enigma Machine encryption algorithm
* used by the German military during WWII. Famously decoded by Alan Turing.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

/* DESCRIPTION OF THIS PROJECT AND THE ENIGMA MACHINE ALGORITHM *********

* The original machine works according to the following:
*
* A machine consisting of a keyboard for input, a plugboard, reflector, rotors, and a typed letter as output.
*
* PLUGBOARD: provides an initial scrambling, consisting of a socket corresponding for each letter on the keyboard.
* Each socket can be wired to a different letter, such that pressing O would yield P, for example, performing a simple character substitution.

* ROTORS: Next this key press input would pass through a series of rotors, which have as many characters as keys on the keyboard.
* These rotors are set to an initial setting, which is crucial for later decryption. Each time a key press input activates,
* the rotor mechanism increments before the character is enciphered
* The rotors perform character substitution, changing depending on the current configuration, with more rotors intensifying this effect.
* Everytime the rotors turn, this substitution configuration changes, such that pressing the same letter twice, i.e. "AA" will not yield
* the same character twice, i.e. "GE".

* REFLECTOR: The last critical component of the machine, the reflector is essentially like the plugboard, with letters connected to eachother loops.
* After passing through the rotors, the character reaches the reflector, which performs character substitution and then passes its result back through the machine,
* passing through the rotors in reverse, and back through the plugboard, delivering its output and forming a reciprocal encryption loop,
* i.e. if you input "Hello" and receive "bAh!g" as output, and then set the rotor settings back to their initial settings, and input "bAh!g",
* you will receive the unencrypted "Hello" message.
*
*
* For simplicity, I keep the plugboard mappings the same for each run through; however this could be changed for future use.
* I set the reflector and rotors with a simple randomized mapping.
*
* To run the machine, simply run this as a command line app and follow the prompt.
*/

// GLOBALS
const int ALPHLENGTH = 94;
const int NUMROTORS = 50;

const char CONST_ALPHABET[ALPHLENGTH] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K' , 'L', 'M', 'N', 'O', 'P',
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',' ', '1', '2', '3', '4', '5', '6', '7', '8', '9',
'0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '|', '\\', '[', ']','}', ':' ,
';', '"', '\'', '?' ,'>', '/', '<', '.', ',', '`'};


// ********************************************************************** Class Machine **************************************************************************************
class Machine {
public:
	const void getMessage();
	void machineStatusUpdate();
	void mapPlugBoard();
	int letterToNum(char letter);
	int plugBoardAssign(int letter);
	void advanceRotors();
	void printRotors();
	void initRotors();
	int encryptLetter(int letter);
	int reflection(int letter);
	void initReflector();
	void encryptLetters();
	void promptMessage();
	void resetRotors();
	Machine();
	void Run();
private:
	int plugBoard[ALPHLENGTH];
	int rotors[NUMROTORS][ALPHLENGTH];
	int rotorsSet[NUMROTORS][ALPHLENGTH];
	int rotorStartingConfigurations[NUMROTORS][ALPHLENGTH];
	int reflector[ALPHLENGTH];
	int reflectorSet[ALPHLENGTH];
	string message;

	int length;
	int machineStatus;
	double completionPercentage;
	int messagePosition;

};
// Constructor
Machine::Machine() {
	message = "";
	length = -1;
	machineStatus = 0;
	completionPercentage = -1.0;
	messagePosition = -1;
	for (int i = 0; i < NUMROTORS; i++) {
		for (int j = 0; j < ALPHLENGTH; j++) {
			rotors[i][j] = -1;
			rotorsSet[i][j] = -1;
			rotorStartingConfigurations[i][j] = -1;
		}
		for (int i = 0; i < ALPHLENGTH; i++) {
			reflector[i] = -1;
			reflectorSet[i] = -1;
			plugBoard[i] = -1;
		}
	}


}




void Machine::machineStatusUpdate() {
	completionPercentage = messagePosition / (double)length;
	switch (machineStatus) {
	case 0: if (completionPercentage >= 0.1) {
		cout << endl << endl << "... 10% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 1: if (completionPercentage >= 0.2) {
		cout << endl << endl << "... 20% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 2: if (completionPercentage >= 0.3) {
		cout << endl << endl << "... 30% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 3: if (completionPercentage >= 0.4) {
		cout << endl << endl << "... 40% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 4: if (completionPercentage >= 0.5) {
		cout << endl << endl << "... 50% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 5: if (completionPercentage >= 0.6) {
		cout << endl << endl << "... 60% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 6: if (completionPercentage >= 0.7) {
		cout << endl << endl << "... 70% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 7: if (completionPercentage >= 0.8) {
		cout << endl << endl << "... 80% completed." << endl << endl;
		machineStatus++;
	}
			break;
	case 8: if (completionPercentage >= 0.9) {
		cout << endl << endl << "... 90% completed." << endl << endl;
		machineStatus++;
	}
			break;
	}

}

void Machine::printRotors() {
	for (int i = 0; i < NUMROTORS; i++) {
		for (int j = 0; j < ALPHLENGTH; j++) {
			cout << "rotor[" << i << "][" << j << "] is: " << rotors[i][j] << endl;
		}
	}
	cout << endl;
}
const void Machine::getMessage() {
	cout << "Message currently is: " << message << endl << endl;
}

void Machine::mapPlugBoard() {
	for (int i = 0; i < ALPHLENGTH; i++) {
		plugBoard[i] = letterToNum(CONST_ALPHABET[ALPHLENGTH - 1 - i]);
	}
}
int Machine::plugBoardAssign(int letter) {
	letter = plugBoard[letter];
	return letter;
}


void Machine::advanceRotors() {
	
	// Steps every character forward one place in the alphabet. So if A maps to B, 
	// A will map to C after the rotor has advanced.
	for (int i = 0; i < NUMROTORS; i++) {
		for (int j = 0; j < ALPHLENGTH; j++) {
		
			if (rotors[i][j] + 1 > ALPHLENGTH - 1) {
				
				rotors[i][j] = 0;
			}
			else {
				rotors[i][j] = rotors[i][j] + 1;
			}
			
		}
	}

}
void Machine::initRotors() {
	srand(time(0));

	// Set Rotors
	for (int i = 0; i < NUMROTORS; i++) {
		for (int j = 0; j < ALPHLENGTH; j++) {
			int k = rand() % (ALPHLENGTH);
			if (rotors[i][j] == -1) {
				while (rotorsSet[i][k] != -1) {
					k = rand() % (ALPHLENGTH);
				}
				rotorsSet[i][k] = 1;
				rotors[i][j] = k;
				rotorStartingConfigurations[i][j] = k;
			}
		}
	}
}

int Machine::letterToNum(char letter) {
	int value = -1;
	for (int i = 0; i < ALPHLENGTH; i++) {
		if (letter == CONST_ALPHABET[i]) {
			value = i;
			break;
		}
	}
	return value;
}

void Machine::resetRotors() {
	for (int i = 0; i < NUMROTORS; i++) {
		for (int j = 0; j < ALPHLENGTH; j++) {
			rotors[i][j] = rotorStartingConfigurations[i][j];
		}

	}
}

int Machine::encryptLetter(int letter) {	
	// Pass through each rotor forwards
	for (int i = 0; i < NUMROTORS; i++) {
		letter = rotors[i][letter];
	}
	return letter;
}


int Machine::reflection(int letter) {
	// Pass through reflector
	letter = reflector[letter];
	// Run through rotors in reverse
	for (int i = NUMROTORS - 1; i >= 0; i--) {
		// Get reverse rotor value
		for (int j = 0; j < ALPHLENGTH; j++) {
			if (rotors[i][j] == letter) {
				
				letter = j;
				break;
			}
		}
	}
	return letter;
}

void Machine::encryptLetters() {
	int k = 0;
	for (messagePosition = 0; messagePosition < length; messagePosition++) {
		//machineStatusUpdate();
		advanceRotors();
		int letter = letterToNum(message.at(messagePosition));
		letter = plugBoardAssign(letter);
		letter = encryptLetter(letter);
		letter = reflection(letter);
		letter = plugBoardAssign(letter);
		message.at(messagePosition) = CONST_ALPHABET[letter];
		//printRotors();
		
	}
}

void Machine::initReflector() {
	srand(time(0));
	// Set reflector
	for (int i = 0; i < ALPHLENGTH; i++) {
		if (reflector[i] == -1) {
			int k = rand() % (ALPHLENGTH);
			while (i == k || reflectorSet[k] != -1 || reflectorSet[i] != -1) {
				k = rand() % (ALPHLENGTH);
			}
			reflector[i] = k;
			reflectorSet[k] = 1;
			reflectorSet[i] = 1;
			reflector[k] = i;
		}
	}
}



void Machine::promptMessage() {
	cout << "Enter your desired message: ";
	getline(cin, message);
	length = message.length();
	
}


void Machine::Run() {
	char yesNo = 'a';

	cout << "Welcome to my Enigma Machine algorithm." << endl << "This machine will initialize itself, encrypt a message, and decrypt it if so desired." << endl;
	// SETUP
	initRotors();
	initReflector();
	mapPlugBoard();

	// START
	promptMessage();
	cout << "Encrypting..." << endl;
	encryptLetters();
	cout << "Encryption Complete!" << endl << endl;
	getMessage();


	while (true) {
		cout << "Do you want to decrypt the message (using the original plugboard, rotor, and reflector settings)? (Y/N): ";
		cin >> yesNo;
		if (yesNo == 'y' || yesNo == 'Y') {
			// START
			resetRotors();
			cout << "Decrypting..." << endl;
			encryptLetters();
			cout << "Decryption Complete!" << endl << endl;
			getMessage();
			system("pause");
			break;
		}
		else if (yesNo == 'n' || yesNo == 'N') {
			cout << endl << endl << " Okay. Goodbye!" << endl << endl;
			break;
		}
		else {
			cout << endl << "Invalid Entry. Please enter either Y or N." << endl << endl;
		}
	}
}

//****************************************** End of Class Machine ***************************************************************************************************

int main() {
	Machine Enigma = Machine();
	Enigma.Run();
	return 0;
}