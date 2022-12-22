#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

void assertion(bool b, size_t i){
	if(b){
		printf("Test %lu: OK\n", i+1);
	} else{
		printf("Test %lu: Failed\n", i+1);
	}
}

char* complementary_dna(const char* dna){
	char* comp = malloc(strlen(dna) + 1);
	memcpy(comp, dna, strlen(dna) + 1);
	for(char* c=comp; *c; c++){
		switch(*c){
			case 'A':
				*c = 'T';
				break;
			case 'T':
				*c ='A';
				break;
			case 'C':
				*c ='G';
				break;
			case 'G':
				*c ='C';
				break;
		}
	}
	return comp;
}
void complementary_dna_tester(){
	size_t size = 3;
	char* dnas[] = {"AATGC", "GCATGG", "GATCAT"};
	char* cdnas[] = {"TTACG", "CGTACC", "CTAGTA"};
	for(size_t i=0; i<size; i++){
		char* res = complementary_dna(dnas[i]);
		assertion(!strcmp(res, cdnas[i]), i);
		free(res);
	}
}

char* your_order_please(char* ordered, const char* words){
	char** tokens = malloc(9 * sizeof(char*));
	char* dup = malloc(strlen(words) + 1);
	memcpy(dup, words, strlen(words)+1);
	char* tok = strtok(dup, " ");
	size_t i = 0;
	while(tok){
		tokens[i] = tok;
		tok = strtok(NULL, " ");
		i++;
	}
	for(size_t a=0; a<i; a++){
		for(size_t b=0; b<a; b++){
			char c1, c2;
			for(size_t j=0; j<strlen(tokens[a]); j++){
				if(tokens[a][j] > 48 && tokens[a][j] < 58){
					c1 = tokens[a][j];
					break;
				}
			}
			for(size_t j=0; j<strlen(tokens[b]); j++){
				if(tokens[b][j] > 48 && tokens[b][j] < 58){
					c2 = tokens[b][j];
					break;
				}
			}

			if(c1 < c2){
				char* tmp = tokens[a];
				tokens[a] = tokens[b];
				tokens[b] = tmp;
			}
		}
	}
	size_t index = 0;
	for(size_t j=0; j<i; j++){
		for(size_t k=0; tokens[j][k] != '\0'; k++){
			ordered[index] = tokens[j][k];
			index++;
		}
		ordered[index] = ' ';
		index++;
	}
	ordered[index-1] = '\0';
	free(dup);
	free(tokens);
	return ordered;
}

void your_order_please_tester(){
	size_t size =3;
	char* words[] = {"F2inished Standin4g St3ill 1Never", "N1o Apolo2gies It4 3Beat", "N3ot 1I Af4raid A2m"};
	char* results[] = {"1Never F2inished St3ill Standin4g", "N1o Apolo2gies 3Beat It4", "1I A2m N3ot Af4raid"};
	for(size_t i=0; i<size; i++){
		char* ordered = malloc(strlen(words[i]) + 1);
		ordered = your_order_please(ordered, words[i]);
		assertion(!strcmp(ordered, results[i]), i);
		free(ordered);
	}
}

char* disemvowel_trolls(const char* str){
	size_t len = strlen(str),	\
				 ni = 0;
	char* neutral = malloc(len + 1);
	for(size_t i=0; i<len; i++){
		switch(str[i]){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
				break;
			default:
				neutral[ni] = str[i];
				ni++;
		}
	}
	neutral[ni] = '\0';
	return neutral;
}

void disemvowel_trolls_tester(){
	size_t size = 3;
	char* trolls[] = {"This website is for losers, LOL",
		"Codewars katas are of the lowest quality",
		"You will never land a job by using codewars"
	};
	char* neutralized[] = {"Ths wbst s fr lsrs, LL",
		"Cdwrs kts r f th lwst qlty",
		"Y wll nvr lnd  jb by sng cdwrs"
	};
	for(size_t i=0; i<size; i++){
		char* neutral = disemvowel_trolls(trolls[i]);
		assertion(!strcmp(neutralized[i], neutral), i);
		free(neutral);
	}
}

bool is_isogram(const char* string){
	size_t len = strlen(string);
	char* lower = malloc(len+1);
	for(size_t i=0; i<len; i++){
		if(string[i] < 97){
			lower[i] = string[i] + 32;
		} else{
			lower[i] = string[i];
		}
	}
	for(size_t i=0; i<len; i++){
		if(strchr(lower, lower[i]) != strrchr(lower, lower[i])){
			free(lower);
			return false;
		}
	}
	free(lower);
	return true;
}

void is_isogram_tester(){
	size_t size = 4;
	char* strings[] = {"Dermatoglyphics",
	   	"abcdefghijklmnopqrstuvwxyzA",
	   	"abA",
		""
	};
	char booleans[] = {1, 0, 0, 1};
	for(size_t i=0; i<size; i++){
		assertion(is_isogram(strings[i]) == booleans[i], i);
	}
}

int find_odd(size_t length, const int array[length]){
	for(size_t i=0; i<length; i++){
		size_t count = 0;
		for(size_t j=0; j<length; j++){
			if(array[i] == array[j]){
				count++;
			}
		}
		if(count % 2){
			return array[i];
		}
	}
	return -1;
}

void find_odd_tester(){
	size_t size = 3;
	int lengths[] = {9, 11, 17};
	int results[] = {10, 1, 5};
	int arrays[][17] = {{1, 1, 1, 1, 10, 1, 10, 10, 1}, 
		{5, 4, 3, 2, 1, 5, 4, 3, 2, 10, 10}, 
		{20, 1, -1, 2, -2, 3, 3, 5, 5, 1, 2, 4, 20, 4, -1, -2, 5}
	};
	for(size_t i=0; i<size; i++){
		assertion(find_odd(lengths[i], arrays[i]) == results[i], i);
	}
}

int equal_sides_array(size_t len, int arr[len]){
	size_t i = 0,
		   j = len -1,
		   k = 0;
	while(k<len){
		int sum = 0, rsum = 0;
		while(i < k || j > k){
			if(i < k){
				sum += arr[i];
				i++;
			}
			if(j > k){
				rsum += arr[j];
				j--;
			}
		}
		i = 0;
		j = len - 1;
		if(rsum == sum){
			return k;
		}
		k++;
	}
	return -1;
}

void equal_sides_array_tester(){
	size_t size = 5,
		   lengths[5] = {7, 6, 6, 5, 7};
	int results[5] = {3, 1, -1};
	int arrays[][7] = {{1,2,3,4,3,2,1},
		{ 1,100,50,-51,1,1 },
		{1,2,3,4,5,6},
		{0,0,0,0,0},
		{20,10,-80,10,10,15,35}
	};
	for(size_t i=0; i<size; i++){
		assertion(equal_sides_array(lengths[i], arrays[i]) == results[i], i);
	}
}

int rgb_to_hex(int rgb[], char* output){
	for(unsigned i=0; i<3; i++){
		if(rgb[i] > 255) rgb[i] = 255;
		else if(rgb[i] < 0) rgb[i] = 0;
	}
	sprintf(output, "%02X%02X%02X", rgb[0], rgb[1], rgb[2]);
	return 0;
}

void rgb_to_hex_tester(){
	size_t size = 3;
	int inputs[][3] = {
		{255, 255, 300},
		{0, 0, 0},
		{148, 0, 211}
	};
	char outputs[][7] = {"FFFFFF", "000000", "9400D3"};
	for(size_t i=0; i<size; i++){
		char output[7] = {0};
		rgb_to_hex(inputs[i], output);
		assertion(!strcmp(output, outputs[i]), i);
	}
}

bool ip_validator(const char* addr){
	char* addr_cpy = malloc(strlen(addr) + 1);
	memcpy(addr_cpy, addr, strlen(addr)+1);
	char* token = strtok(addr_cpy, ".");
	char* eptr;
	short count = 0;
	while(token){
		count++;
		long octet = strtol(token, &eptr, 10);
		bool b = octet > 255 || octet < 0 || *eptr || (strlen(token) - 1 && token[0] == '0');
		if(b || token[0] == ' '){
			free(addr_cpy);
			return 0;
		}
		token = strtok(NULL, ".");
	}
	free(addr_cpy);
	if(count != 4){
		return 0;
	}
	return 1;
}

void ip_validator_tester(){
	size_t size = 5;
	char* inputs[] = {
		"192.168.1.1",
	   	"192.02.112.11",
	   	"100. 123.123.0.1",
	   	"ab2.24.1a.12",
		"12. 12.01.2"
	};
	bool results[] = {1, 0, 0, 0, 0};
	for(size_t i=0; i<size; i++){
		assertion(results[i] == ip_validator(inputs[i]), i);
	}
}

bool narcissistic_num(int num){
	unsigned short digits = 0;
	int sum = 0, temp = num;
	while(temp){
		digits++;
		temp /= 10;
	}
	temp = num;
	while(temp){
		sum += pow(temp % 10, digits);
		temp /= 10;
	}
	if(sum == num){
		return 1;
	}
	return 0;
}

void narcissistic_num_tester(){
	size_t size = 6;
	int nums[] = {7, 371, 122, 11, 153, 1634};
	bool results[] = {1, 1, 0, 0, 1, 1};
	for(size_t i=0; i<size; i++){
		assertion(results[i] == narcissistic_num(nums[i]), i);
	}
}

float find_unique_num(const float *nums, size_t n){
	size_t c1=0, c2=0, j=0,k=0;
	for(size_t i=1; i<n; i++){
		if(nums[i] == nums[0]){
			c2++;
			j = i;
		} else{
			c1++;
			k = i;
		}
	}
	if(c1>c2){
		return nums[j];
	}
	return nums[k];
}

void find_unique_num_tester(){
	size_t size = 5;
	float array[][6] = {
		{1,1,1,1,2},
		{2,1,1,1,1,1},
		{0, 0.55, 0, 0, 0},
		{0,0,0,0,0,12.33},
		{34,34,34,34,89}
	};
	float lengths[] = {5,6,5,6,5},
		  results[] = {2,2,0.55,12.33,89};
	for(size_t i=0; i<size; i++){
		assertion(results[i] == find_unique_num(array[i], lengths[i]), i);
	}
}

char* range_extraction(const int* args, size_t n){
	size_t j = 0;
	char* buffer = calloc(1000, 1);
	for(size_t i=0; i<n; i++){
		char local[20] = {0};
		size_t count = 0;
		while(i+count+1 < n && args[i+count+1] == args[i+count]+1){
			count++;
		}
		if(count > 1){
			i += count;
			sprintf(local, "%d-%d,", args[j], args[i]);
			j = i+1;
		} else{
			sprintf(local, "%d,", args[i]);
			j = i+1;
		}
		strcat(buffer, local);
	}
	buffer[strlen(buffer)-1] = 0;
	return buffer;
}

void range_extraction_tester(){
	size_t size = 5;
	int lengths[] = {11, 11, 10, 9, 8};
	int arrays[][11] = {
		{-3,-2,-1,0,2,10,15,16,19,20,21},
		{-5,-4,-3,-2,-1,0,1,2,3,4,5},
		{-5,-4,-3,-2,-1,1,2,3,4,5},
		{-3,-2,-1,0,2,15,16,19,20},
		{-3,1,2,4,5,6,8,9}
	};
	char* results[] = {
		"-3-0,2,10,15,16,19-21",
		"-5-5",
		"-5--1,1-5",
		"-3-0,2,15,16,19,20",
		"-3,1,2,4-6,8,9"
	};
	for(size_t i=0; i<size; i++){
		char* buffer = range_extraction(arrays[i], lengths[i]);
		assertion(!strcmp(buffer, results[i]), i);
		free(buffer);
	}
}

void move_zeroes_end(size_t len, int arr[len]){
	size_t i = 0, j = 0;
	while(i<len){
		if(arr[i]){
			arr[j] = arr[i];
			j++;
		}
		i++;
	}
	while(j<len){
		arr[j] = 0;
		j++;
	}
}

void move_zeroes_end_tester(){
	size_t size = 4;
	size_t lengths[] = {10, 8, 20, 12};
	int arrays[][20] = {
		{1,2,0,1,0,1,0,3,0,1},
		{0,1,0,2,0,3,4,5},
		{9, 0, 0, 9, 1, 2, 0, 1, 0, 1, 0, 3, 0, 1, 9, 0, 0, 0, 0, 9},
		{9,9,9,0,0,0,0,0,0,9,9,9}
	};
	int results[][20] = {
		{1,2,1,1,3,1,0,0,0,0},
		{1,2,3,4,5,0,0,0},
		{9, 9, 1, 2, 1, 1, 3, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{9,9,9,9,9,9,0,0,0,0,0,0}
	};
	for(size_t i=0; i<size; i++){
		bool b = 1;
		move_zeroes_end(lengths[i], arrays[i]);
		for(size_t j=0; j<lengths[i]; j++){
			if(results[i][j] != arrays[i][j]){
				b = 0;
				break;
			}
		}
		assertion(b, i);
	}
}

char missing_letter(size_t len, char arr[len]){
	size_t i=0;
	while(arr[i]+1 == arr[i+1]){
		i++;
	}
	return arr[i] + 1;
}

void missing_letter_tester(){
	size_t size = 3,
		   lengths[] = {5, 4, 7};
	char results[] = {'E', 'N', 'F'};
	char arrays[][7] = {{'A', 'B', 'C', 'D', 'F'},
		{'L', 'M', 'O', 'P'},
		{'E', 'G', 'H', 'I', 'J', 'K', 'L'}
	};
	for(size_t i=0; i<size; i++){
		assertion(missing_letter(lengths[i], arrays[i]) == results[i], i);
	}
}

int main(int argc, char** argv){
	/*
	complementary_dna_tester();
	your_order_please_tester();
	disemvowel_trolls_tester();
	is_isogram_tester();
	find_odd_tester();
	equal_sides_array_tester();
	missing_letter_tester();
	rgb_to_hex_tester();
	ip_validator_tester();
	narcissistic_num_tester();
	find_unique_num_tester();
	range_extraction_tester();
	*/
	move_zeroes_end_tester();
	return 0;
}
