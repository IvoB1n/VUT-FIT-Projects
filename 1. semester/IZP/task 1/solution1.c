#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define RAW_SIZE 100 //max lenght of a row

// check an argument if it contains only digits
bool is_num(char *argument) {
	int len = strlen(argument);
	bool flag = true;

	for (int i = 0; i < len; ++i) {
		if (!isdigit(argument[i])) {
			flag = false;
		}
	}
	return flag;
} 

// print phonebooklist
void print_phonebook() {
	char buffer[RAW_SIZE];
	while (fgets(buffer, RAW_SIZE, stdin) != NULL) {
		printf("%s", buffer);
	}
}

// convert alphabet charecters into number
char from_letter_to_number(char* number, int i) {
	char letter = tolower(number[i]);

	if (letter == 'a' || letter == 'b' || letter == 'c') {
		return '2';
	}
	else if (letter == 'd' || letter == 'e' || letter == 'f') {
		return '3';
	}
	else if (letter == 'g' || letter == 'h' || letter == 'i') {
		return '4';
	}
	else if (letter == 'j' || letter == 'k' || letter == 'l') {
		return '5';
	}
	else if (letter == 'm' || letter == 'n' || letter == 'o') {
		return '6';
	}
	else if (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's') {
		return '7';
	}
	else if (letter == 't' || letter == 'u' || letter == 'v') {
		return '8';
	}
	else if (letter == 'w' || letter == 'x' || letter == 'y' || letter == 'z') {
		return '9';
	}
	else {
		return letter;
	}
} 

// search connection between entered sequence of numbers and name or phonenumber
bool founded_connection(char *input_arg, char *phonebook_info) {
	int len = strlen(phonebook_info);
	char name[len];

	for (int i = 0; i < len; ++i) {
		name[i] = from_letter_to_number(phonebook_info, i);
	}

	if (strstr(name, input_arg)) {
		return(true);
	}
	else {
		return(false);
	}
}

// read name and phonenumber,start searching for connections
void search_for_connections(char *input_argument) {
	char buffer_name[RAW_SIZE];
	char buffer_phonenumber[RAW_SIZE];
	bool founded_flag = false;
	
	while (fgets(buffer_name, RAW_SIZE, stdin) != NULL) {
		fgets(buffer_phonenumber, RAW_SIZE, stdin);

		if(founded_connection(input_argument, buffer_name) || founded_connection(input_argument, buffer_phonenumber)) {
			founded_flag = true;
			printf("%s, %s", strtok(buffer_name, "\n"), buffer_phonenumber);
		}
	}

	if (!founded_flag) {
		printf("%s\n", "Not found");
	}
}

int main (int argv, char *argc[]) {
	// validation of arguments
	if(argv == 1){ 
		print_phonebook();
	}
	else if(argv == 2){
		if (is_num(argc[1])) {
			search_for_connections(argc[1]);
		}
		else {
			fprintf(stderr, "%s\n", "You should use only digits as programm argument");
			return 1;
		}
	}
	else {
		fprintf(stderr, "%s\n", "Please, add only one argument");
		return 1;
	}
    return 0;
}
