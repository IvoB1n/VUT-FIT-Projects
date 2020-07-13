#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define TURN_LEFT 3
#define TURN_RIGHT 1
#define BUFFER_SIZE 1024
#define NUM_OF_TESTS 4
#define FIRST_ELEMENT 0

struct increments {
	int dr;
	int ds;
};

enum directions { left, up, right, down, count_dir };
	struct increments d[count_dir] = {
		{0, -1}, // left (0)
		{-1, 0}, // up (1)
		{0, +1}, // right (2)
		{+1, 0}, // down (3)
};

typedef struct {
	int rows;
	int cols;
	unsigned char *cells;
} Map;

// prints help
void help() {
	printf("--help\n"
		 "zpusobi, ze program vytiskne napovedu pouzivani programu a skonci.\n\n"
		"--test\n" 
		"pouze zkontroluje, ze soubor dany druhym argumentem programu obsahuje radnou definici mapy bludiste. V pripade, ze format obrazku odpovida definici (viz nize),"
		"vytiskne Valid. V opacnem pripade (napr. ilegalnich znaku, chybejicich udaju nebo spatnych hodnot) program tiskne Invalid\n\n."
		"--rpath\n"
		"hleda pruchod bludistem na vstupu na radku R a sloupci C. Pruchod hleda pomoci pravidla prave ruky (prava ruka vzdy na zdi).\n\n"
		"--lpath\n"
		"hleda pruchod bludistem na vstupu na radku R a sloupci C, ale za pomoci pravidla leve ruky\n\n."
		"--shortest\n" 
		"hleda nejkratsi cestu z bludiste pri vstupu na radku R a sloupci C.\n\n");
}

// validating file_name format
bool text_arg_valid(char *argument) {
	char *file_format = ".txt";
	if (strstr(argument, file_format) != NULL) {
		unsigned int len = strlen(argument);
		unsigned int len_ff = strlen(file_format);

		if (strcspn(argument, file_format) == (len - len_ff)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

// check if a string contains only digits
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

unsigned char get_cell_value(Map *map, int r, int c) {
	unsigned char cell = map->cells[r*map->cols + c];
	return cell;
}

// test main function
bool map_test(char *file_name) {
	int test_passed = 0;

	// if file can be opened
	FILE *fp = fopen(file_name, "r");
	if (fp != NULL) {
		test_passed++;
	}
	// if first row of a map exist
	char buffer[BUFFER_SIZE];
	if (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		test_passed++;
	}

	char *token = strtok(buffer, " ");	
	int rows = atoi(token);
	token = strtok(NULL, " ");
	int cols = atoi(token);
	token = strtok(NULL, " ");
	// if row contains only two numbers
	if (token == NULL) {
		test_passed++;
	}
	//  if row contains valid numbers
	if (rows > 0 && cols > 0) {
		test_passed++;
	}

	// if other rows are valid and rows = rows, cols = cols
	char cell;
	for (int i = 0; i < cols && fgets(buffer, BUFFER_SIZE, fp) != NULL; ++i) {
		int len = strlen(buffer);
		len = len - (cols - 1);
		//entered rows = rows
		if (len == cols + 1) {
			test_passed++;
		}
		else if (len == cols && i == cols - 2) {
			test_passed++;
		}
		else {
			fclose(fp);
			return false;
		}

		token = strtok(buffer, " ");
		// cell value validation
		if (strlen(token) == 1) {
			cell = token[FIRST_ELEMENT];
			if (cell >= '0' && cell <= '7') {
				test_passed++;
			}
		}
		for (int j = 0; j < rows && token != NULL ; ++j) {
			token = strtok(NULL, " ");
			if (strlen(token) == 1) {
				cell = token[FIRST_ELEMENT];
			}
			else if (strlen(token) == 3 && j == rows - 1) {
				cell = token[FIRST_ELEMENT];
			}
			// cell value validation
			if (cell >= '0' && cell <= '7') {
				test_passed ++;
			}
		}
	}
	// if 5 tests were completed, return true
	test_passed -= rows * cols + cols - 1;
	fclose(fp);
	if (test_passed == NUM_OF_TESTS) {
		return true;
	}
	else {
		return false;
	}
}

// creating map
int map_ctor(Map *map, char *file_name) {
	if (map_test(file_name)) {
		FILE *fp = fopen(file_name, "r");
		if (fp == NULL) {
			return -4;
		}

		char buffer[BUFFER_SIZE];
		fgets(buffer, BUFFER_SIZE, fp);

		char *token = strtok(buffer, " ");	
		map->rows = atoi(token);
		token = strtok(NULL, " ");
		map->cols = atoi(token);
		
		map->cells = malloc(map->rows * map->cols * sizeof(unsigned char));

		for (int i = 0; i < map->rows; ++i) {
			fgets(buffer, BUFFER_SIZE, fp);
			token = strtok(buffer, " ");
			for (int j = 0; j < map->cols || token != NULL; ++j) {
				unsigned char number = token[FIRST_ELEMENT];
				map->cells[i*map->cols + j] = number;
				token = strtok(NULL, " ");
			}
		}
		fclose(fp);
	}
	else {
		fprintf(stderr, "%s\n", "Invalid");
		exit(-4);
	}
	return 1;
}

// deallocation of a map
void map_dtor(Map *map) {
	if (map->cells != NULL) {
		free(map->cells);
	}
}

// check if a triangle id normal or inverted (0 = even = normal, 1 = odd = inverted)
int odd_cell(int r, int c) {
	if ((r % 2 == 0) && (c % 2 == 0)) {
		return 1;
	}
	else if ((r % 2 != 0) && (c % 2 != 0)) {
		return 1;
	}
	else if ((r % 2 == 0) && (c % 2 != 0)) {
		return 0;
	}
	else {
		return 0;
	}
}
// check if the cell has a border at certain direction

bool isborder(Map *map, int r, int c, int border) {
	int cell_int = get_cell_value(map, r, c) - '0';
	int cell_int_bin[3];
	for (int i = 0; i < 3; ++i) {
		cell_int_bin[i] =  cell_int % 2;
		cell_int = cell_int / 2;
	}

	if (border == right && cell_int_bin[1] == 1) {
		return true;
	}
	else if (border == left && cell_int_bin[0] == 1) {
		return true;
	}
	else if ((border == up || border == down) && cell_int_bin[2] == 1) {
		return true;
	}
	else {
		return false;
	}

}

// looks for a cell to start with
int start_border(Map *map, int r, int c, int leftright) {
		if (leftright == right) { //for right hand
			if (!odd_cell(r, c)) {
				if (c == map->cols - 1 && !isborder(map, r, c, right)) {
					return left;
				} 
				else if (c == 0 && !isborder(map, r, c, left)) {
					return down;
				}
				else if (r == map->rows -1 && !isborder(map, r, c, down)) {
					return right; 
				}
				else {
					fprintf(stderr, "wrong r/c format or there is a border at staring point\n");
					exit(-6);
				}
			}
			else {
				if (c == map->cols - 1 && !isborder(map, r, c, right)) {
					return up;
				}
				else if (c == 0 && !isborder(map, r, c, left)) {
					return right;
				}
				else if (r == 0 && !isborder(map, r, c, up)) {
					return left;
				}
				else {
					//return up;  WHY IT DOES'NOT WORK FOR 3 7
					fprintf(stderr, "wrong r/c format or there is a border at staring point\n");
					exit(-6);
				}
			}
		}
		else {
			if (!odd_cell(r, c)) {
				if (c == map->cols - 1 && !isborder(map, r, c, right)) {
					return down;
				}
				else if (c == 0 && !isborder(map, r, c, left)) {
					return right;
				}
				else if (r == map->rows - 1 && !isborder(map, r, c, down)) {
					return left; 
				}
				else {
					fprintf(stderr, "%s\n", "wrong r/c format or there is a border at staring point");
					exit(-6);
				}
			}
			else {
				if (c == map->cols - 1 && !isborder(map, r, c, right)) {
					return left;
				}
				else if (c == 0 && !isborder(map, r, c, left)) {
					return up;
				}
				else if (r == 0 && !isborder(map, r, c, up)) {
					return right;
				}
				else {
					fprintf(stderr, "%s\n", "wrong r/c format or there is a border at staring point");
					exit(-6);
				}
			}
		}
	return -2;
}

// path searching algorithm
void start_searching(Map *map, int searching_alg, int r, int c) {
	int direction = start_border(map, r, c, searching_alg);
	int main_turn;
	int additional_turn;

	if (searching_alg == right) {
		main_turn = TURN_RIGHT;
		additional_turn = TURN_LEFT;
	}
	else {
		main_turn = TURN_LEFT;
		additional_turn = TURN_RIGHT;
	}
		while (r >= 0 && r < map->rows && c >= 0 && c < map->cols) {
			while (isborder(map, r, c, direction)) {
				direction = (direction + additional_turn) % count_dir;
				if ((odd_cell(r, c) && direction == down) || (!odd_cell(r, c) && direction == up)) {
					direction = (direction + additional_turn) % count_dir;
				}
			}
			// move
			printf("%d,%d\n", r + 1, c + 1);
			r = r + d[direction].dr;
			c = c + d[direction].ds;

			direction = (direction + main_turn) % count_dir;

			if (!odd_cell(r, c) && direction == up) {
					direction = (direction + additional_turn) % count_dir;
			}
			else if (odd_cell(r, c) && direction == down) {
				direction = (direction + additional_turn) % count_dir;
			}
		}
	map_dtor(map);
}

// argument validation
int main(int argc, char *argv[]) {
	if (argc == 2 && !strcmp(argv[1], "--help")) {
			help();
			return 0;
	}
	else if (argc == 3 && !strcmp(argv[1], "--test") && text_arg_valid(argv[2])) {
		char *file_name = argv[2];
		if(map_test(file_name)) {
			fprintf(stderr, "%s\n", "Valid");
		}
		else {
			fprintf(stderr, "%s\n", "Invalid");
		}
	}
	else if (argc == 5 && !strcmp(argv[1], "--rpath") && is_num(argv[2]) &&
		is_num(argv[3]) && text_arg_valid(argv[4])) {
		int searching_alg = right;
		int rows = atoi(argv[2]) - 1;
		int cols = atoi(argv[3]) - 1;
		char *file_name = argv[4];
		Map map;
		map_ctor(&map, file_name);
		start_searching(&map, searching_alg, rows, cols);
	}
	else if (argc == 5 && !strcmp(argv[1], "--lpath") && is_num(argv[2]) &&
			is_num(argv[3]) && text_arg_valid(argv[4])) {
		int searching_alg = left;
		int rows = atoi(argv[2]) - 1;
		int cols = atoi(argv[3]) - 1;
		char *file_name = argv[4];
		Map map;
		map_ctor(&map, file_name);
		start_searching(&map, searching_alg, rows, cols);
	}
	else if (argc == 5 && !strcmp(argv[1], "--shortest") && is_num(argv[2]) &&
		is_num(argv[3]) && text_arg_valid(argv[4])) {
		printf("%s\n", "TODO: implementation of shortest algorithm");
	}
	else {
		fprintf(stderr, "%s\n", "wrong arguments. please, use --help to get instructions");
	}
	return 0;
}
