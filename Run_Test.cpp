
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<math.h>

struct bdnode {
	std::string val;
	bdnode* left;
	bdnode* right;
};

typedef bdnode* bdt;

struct array_aux {

private:

	//number of digits in each input element
	int input_string_length;

	//length of array
	int array_length_1D;

	//length of the vector inpiut
	int vector_len;

	//int 1D array
	int *seq_1D_int;

	//n*2^n
	//2D char array
	char **seq_2D_char_input;

	//for accelerating the checking process
	bool *seq_1D_2D_available_space;

	//for sorting
	//bit 0: bit position
	//bit 1: bit = 0 counter
	//bit 2: bit = 1 counter
	//bit 3: max
	//bit 4: sum
	//bit 5: weight/priority
	int **seq_2D_int_sort;

public:

	array_aux(int len, int len_of_vector) {
		input_string_length = len;
		array_length_1D = pow(2, input_string_length);
		vector_len = len_of_vector;

		//1D
		seq_1D_int = new int[array_length_1D];

		for (int i = 0; i < array_length_1D; i++) {
			seq_1D_int[i] = -1;
		}

		//2D & 1D
		seq_2D_char_input = new char*[vector_len];
		seq_1D_2D_available_space = new bool[vector_len];

		for (int i = 0; i < vector_len; i++) {
			seq_2D_char_input[i] = new char[input_string_length];
			seq_1D_2D_available_space[i] = false;
			for (int j = 0; j < input_string_length; j++) {
				seq_2D_char_input[i][j] = '2';
			}
		}

		//2D
		seq_2D_int_sort = new int*[input_string_length];

		for (int i = 0; i < input_string_length; i++) {
			seq_2D_int_sort[i] = new int[6];
			seq_2D_int_sort[i][0] = i + 1;
			for (int j = 1; j < 6; j++) {
				seq_2D_int_sort[i][j] = 0;
			}
		}
	}

	~array_aux(){
		if(seq_1D_int){
			delete[] seq_1D_int;
		}

		if(seq_2D_char_input){
			for(int i=0; i < vector_len; i++){
				delete[] seq_2D_char_input[i];
			}
			delete[] seq_2D_char_input;
		}

		if(seq_1D_2D_available_space){
			delete[] seq_1D_2D_available_space;
		}

		if(seq_2D_int_sort){
			for(int i=0; i < input_string_length; i++){
				delete[] seq_2D_int_sort[i];
			}
			delete[] seq_2D_int_sort;
		}
	}

	int return_array_length_1D() {
		return array_length_1D;
	}

	void seq_1D_int_set(int position, int val) {
		seq_1D_int[position] = val;
	}

	int seq_1D_int_return(int position) {
		return seq_1D_int[position];
	}

	void seq_1D_int_test() {
		for (int i = 0; i < vector_len; i++) {
			std::cout << i << ' ' << seq_1D_int[i] << std::endl;
		}
		std::cout << std::endl;
	}

	void seq_1D_2D_char_input_set(int position, std::string binary_string) {

		if(seq_1D_int[position]==-1){
			//find the location in the 2D char table for inserting the new record
			bool found = false;
			int space_index = 0;

			while(!found && space_index < vector_len){
				if(!seq_1D_2D_available_space[space_index]){
					found = true;
					seq_1D_2D_available_space[space_index] = true;
				}
				else{
					space_index++;
				}
			}

			//set the value on the mapping list
			seq_1D_int[position] = space_index;

			//set the values in the 2D input table
			for (int i = 0; i < binary_string.length(); i++) {
				seq_2D_char_input[space_index][i] = binary_string[i];
			}
		}
	}

	void seq_2D_char_input_set_bit(int position, int bit, char info) {

		int index_hashed = seq_1D_int[position];

		seq_2D_char_input[index_hashed][bit] = info;
	}

	char seq_2D_char_input_return(int x, int y) {

		int index_hashed = seq_1D_int[x];

		return seq_2D_char_input[index_hashed][y];
	}

	int seq_2D_char_input_weight(int position){

		int index_hashed = seq_1D_int[position];
		int weight = 0;

		if(index_hashed!=-1){
			for(int i=0; i<input_string_length;i++){
				if(seq_2D_char_input[index_hashed][i]!='0'){
					weight+=pow(2,input_string_length-1-i);
				}
			}
			return weight;
		}
		return -1;

	}

	void seq_2D_char_input_test() {

		std::cout << "testing the 2D char input array" << std::endl;

		for (int i = 0; i < vector_len; i++) {
			for (int j = 0; j < input_string_length; j++) {
				std::cout << seq_2D_char_input[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int check_available_routes() {
		int available_routes_count = 0;

		for (int i = 0; i < vector_len; i++) {
			if (seq_1D_2D_available_space[i]) {
				available_routes_count++;
			}
		}
		return available_routes_count;
	}

	void delete_route(int position) {

		int index_hashed = seq_1D_int[position];

		for (int i = 0; i < input_string_length; i++) {
			seq_2D_char_input[index_hashed][i] = '2';
		}

		seq_1D_int[position] = -1;
		seq_1D_2D_available_space[index_hashed] = false;
	}

	void seq_2D_int_sort_bit_set() {

		//fill in at position 1 and 2
		for (int i = 0; i < array_length_1D; i++) {
			if (seq_1D_int[i]!=-1) {
				for (int j = 0; j < input_string_length; j++) {
					if (seq_2D_char_input[seq_1D_int[i]][j] == '0') {
						seq_2D_int_sort[j][1]++;
					} else if (seq_2D_char_input[seq_1D_int[i]][j] == '1') {
						seq_2D_int_sort[j][2]++;
					}
				}
			}
		}

		//fill in at position 3 and 4
		for (int i = 0; i < input_string_length; i++) {
			if (seq_2D_int_sort[i][1] <= seq_2D_int_sort[i][2]) {
				seq_2D_int_sort[i][3] = seq_2D_int_sort[i][2];
			} else {
				seq_2D_int_sort[i][3] = seq_2D_int_sort[i][1];
			}
			seq_2D_int_sort[i][4] = seq_2D_int_sort[i][1]
													   + seq_2D_int_sort[i][2];
		}
	}

	void seq_2D_int_sort_bit_sort(int bit_sort) {
		int swap_tmpp_0;
		int swap_tmpp_1;
		int swap_tmpp_2;
		int swap_tmpp_3;
		int swap_tmpp_4;

		//bubble sort the 2D int order array
		//using the sum
		for (int i = 0; i < input_string_length - 1; i++) {
			for (int j = 0; j < input_string_length - 1; j++) {
				if (seq_2D_int_sort[j][bit_sort]
									   < seq_2D_int_sort[j + 1][bit_sort]) {
					swap_tmpp_0 = seq_2D_int_sort[j + 1][0];
					swap_tmpp_1 = seq_2D_int_sort[j + 1][1];
					swap_tmpp_2 = seq_2D_int_sort[j + 1][2];
					swap_tmpp_3 = seq_2D_int_sort[j + 1][3];
					swap_tmpp_4 = seq_2D_int_sort[j + 1][4];

					seq_2D_int_sort[j + 1][0] = seq_2D_int_sort[j][0];
					seq_2D_int_sort[j + 1][1] = seq_2D_int_sort[j][1];
					seq_2D_int_sort[j + 1][2] = seq_2D_int_sort[j][2];
					seq_2D_int_sort[j + 1][3] = seq_2D_int_sort[j][3];
					seq_2D_int_sort[j + 1][4] = seq_2D_int_sort[j][4];

					seq_2D_int_sort[j][0] = swap_tmpp_0;
					seq_2D_int_sort[j][1] = swap_tmpp_1;
					seq_2D_int_sort[j][2] = swap_tmpp_2;
					seq_2D_int_sort[j][3] = swap_tmpp_3;
					seq_2D_int_sort[j][4] = swap_tmpp_4;
				}
			}
		}
	}

	//sort: sum first, max after
	void seq_2D_int_sort_bit_run() {
		seq_2D_int_sort_bit_sort(4);
		seq_2D_int_sort_bit_sort(3);
	}

	int seq_2D_int_sort_return(int x, int y) {
		return seq_2D_int_sort[x][y];
	}

	void seq_2D_int_sort_test() {

		std::cout << "testing the 2D int sort array" << std::endl;

		for (int i = 0; i < input_string_length; i++) {
			for (int j = 0; j < 6; j++) {
				std::cout << seq_2D_int_sort[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void seq_2D_int_sort_priority_gen() {
		int priority_level = 1;

		seq_2D_int_sort[0][5] = priority_level;

		for (int i = 1; i < input_string_length; i++) {
			if (seq_2D_int_sort[i][3] == seq_2D_int_sort[i - 1][3]
																&& seq_2D_int_sort[i][4] == seq_2D_int_sort[i - 1][4]) {
				seq_2D_int_sort[i][5] = priority_level;
			} else {
				priority_level++;
				seq_2D_int_sort[i][5] = priority_level;
			}
		}
	}
};

bdt buildcompactbdt(const std::vector<std::string>& fvalues);

std::string evalcompactbdt(bdt t, const std::string& input);

int binaryToInt(const std::string num);

std::string nodeNamer(const int level_label);

void nodeList(bdt t);

void nodeSetZero(bdt t);

int nodeCounter(bdt t);

void nodeCountAux(bdt t, int &count);

int main() {

	//	std::cout << "set 1, testing 2 bits" << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::vector<std::string> vector_set1;
	//
	//	std::string in_set1 = "11";
	//
	//	vector_set1.push_back(in_set1);
	//
	//	in_set1 = "01";
	//
	//	vector_set1.push_back(in_set1);
	//
	//	bdt root_set1 = buildcompactbdt(vector_set1);
	//
	//	std::cout << "00 the result is: " << evalcompactbdt(root_set1, "00") << std::endl;
	//
	//	std::cout << "01 the result is: " << evalcompactbdt(root_set1, "01") << std::endl;
	//
	//	std::cout << "10 the result is: " << evalcompactbdt(root_set1, "10") << std::endl;
	//
	//	std::cout << "11 the result is: " << evalcompactbdt(root_set1, "11") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set1->val << std::endl;
	//
	//	nodeList(root_set1);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set1) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 2, testing 2 bits" << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::vector<std::string> vector_set2;
	//
	//	std::string in_set2 = "10";
	//
	//	vector_set2.push_back(in_set2);
	//
	//	in_set2 = "11";
	//
	//	vector_set2.push_back(in_set2);
	//
	//	in_set2 = "01";
	//
	//	vector_set2.push_back(in_set2);
	//
	//	bdt root_set2 = buildcompactbdt(vector_set2);
	//
	//	std::cout << "00 the result is: " << evalcompactbdt(root_set2, "00") << std::endl;
	//
	//	std::cout << "01 the result is: " << evalcompactbdt(root_set2, "01") << std::endl;
	//
	//	std::cout << "10 the result is: " << evalcompactbdt(root_set2, "10") << std::endl;
	//
	//	std::cout << "11 the result is: " << evalcompactbdt(root_set2, "11") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set2->val << std::endl;
	//
	//	nodeList(root_set2);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set2) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 3, testing 3 bits" << std::endl;
	//
	//	std::vector<std::string> vector_set3;
	//
	//	std::string in_set3 = "101";
	//
	//	vector_set3.push_back(in_set3);
	//
	//	in_set3 = "011";
	//
	//	vector_set3.push_back(in_set3);
	//
	//	in_set3 = "011";
	//
	//	vector_set3.push_back(in_set3);
	//
	//	bdt root_set3 = buildcompactbdt(vector_set3);
	//
	//	std::cout << "000 the result is: " << evalcompactbdt(root_set3, "000") << std::endl;
	//
	//	std::cout << "001 the result is: " << evalcompactbdt(root_set3, "001") << std::endl;
	//
	//	std::cout << "010 the result is: " << evalcompactbdt(root_set3, "010") << std::endl;
	//
	//	std::cout << "011 the result is: " << evalcompactbdt(root_set3, "011") << std::endl;
	//
	//	std::cout << "100 the result is: " << evalcompactbdt(root_set3, "100") << std::endl;
	//
	//	std::cout << "101 the result is: " << evalcompactbdt(root_set3, "101") << std::endl;
	//
	//	std::cout << "110 the result is: " << evalcompactbdt(root_set3, "110") << std::endl;
	//
	//	std::cout << "111 the result is: " << evalcompactbdt(root_set3, "111") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set3->val << std::endl;
	//
	//	nodeList(root_set3);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set3) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 4, testing 3 bits" << std::endl;
	//
	//	std::vector<std::string> vector_set4;
	//
	//	std::string in_set4 = "000";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	in_set4 = "001";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	in_set4 = "010";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	in_set4 = "011";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	in_set4 = "100";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	in_set4 = "110";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	in_set4 = "111";
	//
	//	vector_set4.push_back(in_set4);
	//
	//	bdt root_set4 = buildcompactbdt(vector_set4);
	//
	//	std::cout << "000 the result is: " << evalcompactbdt(root_set4, "000") << std::endl;
	//
	//	std::cout << "001 the result is: " << evalcompactbdt(root_set4, "001") << std::endl;
	//
	//	std::cout << "010 the result is: " << evalcompactbdt(root_set4, "010") << std::endl;
	//
	//	std::cout << "011 the result is: " << evalcompactbdt(root_set4, "011") << std::endl;
	//
	//	std::cout << "100 the result is: " << evalcompactbdt(root_set4, "100") << std::endl;
	//
	//	std::cout << "101 the result is: " << evalcompactbdt(root_set4, "101") << std::endl;
	//
	//	std::cout << "110 the result is: " << evalcompactbdt(root_set4, "110") << std::endl;
	//
	//	std::cout << "111 the result is: " << evalcompactbdt(root_set4, "111") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set4->val << std::endl;
	//
	//	nodeList(root_set4);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set4) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 5, testing 3 bits" << std::endl;
	//
	//	std::vector<std::string> vector_set5;
	//
	//	std::string in_set5 = "000";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "001";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "010";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "011";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "100";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "101";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "110";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	in_set5 = "111";
	//
	//	vector_set5.push_back(in_set5);
	//
	//	bdt root_set5 = buildcompactbdt(vector_set5);
	//
	//	std::cout << "000 the result is: " << evalcompactbdt(root_set5, "000") << std::endl;
	//
	//	std::cout << "001 the result is: " << evalcompactbdt(root_set5, "001") << std::endl;
	//
	//	std::cout << "010 the result is: " << evalcompactbdt(root_set5, "010") << std::endl;
	//
	//	std::cout << "011 the result is: " << evalcompactbdt(root_set5, "011") << std::endl;
	//
	//	std::cout << "100 the result is: " << evalcompactbdt(root_set5, "100") << std::endl;
	//
	//	std::cout << "101 the result is: " << evalcompactbdt(root_set5, "101") << std::endl;
	//
	//	std::cout << "110 the result is: " << evalcompactbdt(root_set5, "110") << std::endl;
	//
	//	std::cout << "111 the result is: " << evalcompactbdt(root_set5, "111") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set5->val << std::endl;
	//
	//	nodeList(root_set5);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set5) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//
	//	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 6, testing 3 bits" << std::endl;
	//
	//	std::vector<std::string> vector_set6;
	//
	//	bdt root_set6 = buildcompactbdt(vector_set6);
	//
	//	std::cout << "000 the result is: " << evalcompactbdt(root_set6, "000") << std::endl;
	//
	//	std::cout << "001 the result is: " << evalcompactbdt(root_set6, "001") << std::endl;
	//
	//	std::cout << "010 the result is: " << evalcompactbdt(root_set6, "010") << std::endl;
	//
	//	std::cout << "011 the result is: " << evalcompactbdt(root_set6, "011") << std::endl;
	//
	//	std::cout << "100 the result is: " << evalcompactbdt(root_set6, "100") << std::endl;
	//
	//	std::cout << "101 the result is: " << evalcompactbdt(root_set6, "101") << std::endl;
	//
	//	std::cout << "110 the result is: " << evalcompactbdt(root_set6, "110") << std::endl;
	//
	//	std::cout << "111 the result is: " << evalcompactbdt(root_set6, "111") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set6->val << std::endl;
	//
	//	nodeList(root_set6);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set6) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	/////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 7, testing 4 bits" << std::endl;
	//
	//	std::vector<std::string> vector_set7;
	//
	//	std::string in_set7;
	//
	//	in_set7 = "0100";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "0001";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "1111";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "1100";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "0111";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "0101";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "1110";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "1111";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "1111";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "0011";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "0111";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	in_set7 = "1011";
	//
	//	vector_set7.push_back(in_set7);
	//
	//	bdt root_set7 = buildcompactbdt(vector_set7);
	//
	//	std::cout << "0000 the result is: " << evalcompactbdt(root_set7, "0000") << std::endl;
	//
	//	std::cout << "0001 the result is: " << evalcompactbdt(root_set7, "0001") << std::endl;
	//
	//	std::cout << "0010 the result is: " << evalcompactbdt(root_set7, "0010") << std::endl;
	//
	//	std::cout << "0011 the result is: " << evalcompactbdt(root_set7, "0011") << std::endl;
	//
	//	std::cout << "0100 the result is: " << evalcompactbdt(root_set7, "0100") << std::endl;
	//
	//	std::cout << "0101 the result is: " << evalcompactbdt(root_set7, "0101") << std::endl;
	//
	//	std::cout << "0110 the result is: " << evalcompactbdt(root_set7, "0110") << std::endl;
	//
	//	std::cout << "0111 the result is: " << evalcompactbdt(root_set7, "0111") << std::endl;
	//
	//	std::cout << "1000 the result is: " << evalcompactbdt(root_set7, "1000") << std::endl;
	//
	//	std::cout << "1001 the result is: " << evalcompactbdt(root_set7, "1001") << std::endl;
	//
	//	std::cout << "1010 the result is: " << evalcompactbdt(root_set7, "1010") << std::endl;
	//
	//	std::cout << "1011 the result is: " << evalcompactbdt(root_set7, "1011") << std::endl;
	//
	//	std::cout << "1100 the result is: " << evalcompactbdt(root_set7, "1100") << std::endl;
	//
	//	std::cout << "1101 the result is: " << evalcompactbdt(root_set7, "1101") << std::endl;
	//
	//	std::cout << "1110 the result is: " << evalcompactbdt(root_set7, "1110") << std::endl;
	//
	//	std::cout << "1111 the result is: " << evalcompactbdt(root_set7, "1111") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set7->val << std::endl;
	//
	//	nodeList(root_set7);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set7) << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	std::cout << "set 8, testing 4 bits" << std::endl;
	//
	//	std::vector<std::string> vector_set8;
	//
	//	std::string in_set8;
	//
	//	in_set8 = "0100";
	//
	//	vector_set8.push_back(in_set8);
	//
	//	in_set8 = "0001";
	//
	//	vector_set8.push_back(in_set8);
	//
	//	in_set8 = "1111";
	//
	//	vector_set8.push_back(in_set8);
	//
	//	in_set8 = "1100";
	//
	//	vector_set8.push_back(in_set8);
	//
	//	in_set8 = "0111";
	//
	//	vector_set8.push_back(in_set8);
	//
	//	bdt root_set8 = buildcompactbdt(vector_set8);
	//
	//	std::cout << "0000 the result is: " << evalcompactbdt(root_set8, "0000") << std::endl;
	//
	//	std::cout << "0001 the result is: " << evalcompactbdt(root_set8, "0001") << std::endl;
	//
	//	std::cout << "0010 the result is: " << evalcompactbdt(root_set8, "0010") << std::endl;
	//
	//	std::cout << "0011 the result is: " << evalcompactbdt(root_set8, "0011") << std::endl;
	//
	//	std::cout << "0100 the result is: " << evalcompactbdt(root_set8, "0100") << std::endl;
	//
	//	std::cout << "0101 the result is: " << evalcompactbdt(root_set8, "0101") << std::endl;
	//
	//	std::cout << "0110 the result is: " << evalcompactbdt(root_set8, "0110") << std::endl;
	//
	//	std::cout << "0111 the result is: " << evalcompactbdt(root_set8, "0111") << std::endl;
	//
	//	std::cout << "1000 the result is: " << evalcompactbdt(root_set8, "1000") << std::endl;
	//
	//	std::cout << "1001 the result is: " << evalcompactbdt(root_set8, "1001") << std::endl;
	//
	//	std::cout << "1010 the result is: " << evalcompactbdt(root_set8, "1010") << std::endl;
	//
	//	std::cout << "1011 the result is: " << evalcompactbdt(root_set8, "1011") << std::endl;
	//
	//	std::cout << "1100 the result is: " << evalcompactbdt(root_set8, "1100") << std::endl;
	//
	//	std::cout << "1101 the result is: " << evalcompactbdt(root_set8, "1101") << std::endl;
	//
	//	std::cout << "1110 the result is: " << evalcompactbdt(root_set8, "1110") << std::endl;
	//
	//	std::cout << "1111 the result is: " << evalcompactbdt(root_set8, "1111") << std::endl;
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "traversing the tree" << std::endl;
	//
	//	std::cout << "root is: " << root_set7->val << std::endl;
	//
	//	nodeList(root_set7);
	//
	//	std::cout << std::endl;
	//
	//	std::cout << "the number of non-leaf nodes is: " << nodeCounter(root_set7) << std::endl;
	//
	//	std::cout << std::endl;

	std::vector<std::string> in;

	std::string test = "000000000000000000000000000000";

	in.push_back(test);

	bdt root = buildcompactbdt(in);

	std::cout << "evaluating 000000000000000000000000000000 " << evalcompactbdt(root, "000000000000000000000000000000") << std::endl;

	std::vector<std::string> in1;

	std::string test1 = "000000000000000000000000000001";

	in1.push_back(test1);

	bdt root1 = buildcompactbdt(in1);

	std::cout << "evaluating 000000000000000000000000000001 " << evalcompactbdt(root1, "000000000000000000000000000001") << std::endl;

	return 0;

}

bdt buildcompactbdt(const std::vector<std::string>& fvalues) {

	bdt bdt_array_root = new bdnode;

	if(fvalues.size()==0){
		bdt_array_root->val = "0";
		bdt_array_root->right = NULL;
		bdt_array_root->left = NULL;
		return bdt_array_root;
	}

	//get the length of the input string
	int string_length = fvalues[0].length();

	int input_length = fvalues.size();

	array_aux *array_gen = new array_aux(string_length, input_length);

	//load values
	for (int i = 0; i < input_length; i++) {
		array_gen->seq_1D_2D_char_input_set(binaryToInt(fvalues[i]), fvalues[i]);
	}

	//uncomment the following for testing
	//	std::cout << "testing input array before simplifying" << std::endl;
	//	array_gen->seq_2D_char_input_test();

	if(array_gen->check_available_routes()==array_gen->return_array_length_1D()){
		bdt_array_root->val = "1";
		bdt_array_root->right = NULL;
		bdt_array_root->left = NULL;
		return bdt_array_root;
	}

	//simplify the routes
	int count_before = 0;
	int count_after = 0;
	bool match_found = false;
	int distance = 0;
	int bit_position = 0;
	int length_1D = array_gen->return_array_length_1D();
	int relative_position;
	int weight_i;
	int weight_relative;
	int difference;

	do {
		//check the termination condition, before simplification
		count_before = array_gen->check_available_routes();

		for (int i = 0; i < length_1D; i++) {
			if (array_gen->seq_1D_int_return(i)!=-1) {

				match_found = false;
				bit_position = 0;

				while (bit_position < string_length && match_found == false) {

					if(array_gen->seq_2D_char_input_return(i, bit_position) == '0'){

						distance = pow(2, (string_length - bit_position - 1));
						relative_position = i+distance;
						weight_i = array_gen->seq_2D_char_input_weight(i);
						weight_relative = array_gen->seq_2D_char_input_weight(relative_position);
						difference = weight_relative-weight_i;

						if(array_gen->seq_1D_int_return(relative_position)!=-1
								&&difference == distance){
							array_gen->delete_route(relative_position);
							array_gen->seq_2D_char_input_set_bit(i, bit_position, '2');
							match_found = true;
						}
					}
					bit_position++;
				}
			}
		}

		//check the termination condition, after simplification
		count_after = array_gen->check_available_routes();

	} while (count_before != count_after);

	array_gen->seq_2D_int_sort_bit_set();

	//sort: sum first, max after
	array_gen->seq_2D_int_sort_bit_run();

	array_gen->seq_2D_int_sort_priority_gen();

	//uncomment the following for testing
	//std::cout << "after simplification" << std::endl;
	//array_gen->seq_2D_int_sort_test();
	//array_gen->seq_2D_char_input_test();

	//create a table
	//record the available routes
	//calculate the corresponding weighting
	int **available_route = new int*[array_gen->check_available_routes()];

	for (int i = 0; i < array_gen->check_available_routes(); i++) {
		available_route[i] = new int[2];
		available_route[i][0] = 0;
		available_route[i][1] = 0;
	}

	int weighting = 0;
	int available_route_pointer = 0;

	for (int i = 0; i < array_gen->return_array_length_1D(); i++) {

		if (array_gen->seq_1D_int_return(i)!=-1) {

			available_route[available_route_pointer][0] = i;
			bit_position = 0;
			weighting = 0;

			while (bit_position < string_length) {

				if (array_gen->seq_2D_char_input_return(i,
						array_gen->seq_2D_int_sort_return(bit_position, 0) - 1)
						!= '2') {
					weighting += array_gen->seq_2D_int_sort_return(bit_position,
							5);
				}
				bit_position++;
			}
			available_route[available_route_pointer][1] = weighting;
			available_route_pointer++;
		}
	}

	int swap_tmpp_0;
	int swap_tmpp_1;

	//bubble sort the route array
	//small first
	for (int i = 0; i < array_gen->check_available_routes() - 1; i++) {
		for (int j = 0; j < array_gen->check_available_routes() - 1; j++) {
			if (available_route[j][1] > available_route[j + 1][1]) {
				swap_tmpp_0 = available_route[j][0];
				swap_tmpp_1 = available_route[j][1];

				available_route[j][0] = available_route[j + 1][0];
				available_route[j][1] = available_route[j + 1][1];

				available_route[j + 1][0] = swap_tmpp_0;
				available_route[j + 1][1] = swap_tmpp_1;
			}
		}
	}

	//	testing
	//	std::cout << "testing the available route array" << std::endl;
	//	for (int i = 0; i < array_gen->check_available_routes(); i++) {
	//		std::cout << available_route[i][0] << ' ' << available_route[i][1]
	//																		<< std::endl;
	//	}
	//	std::cout << std::endl;

	//start building the tree
	bdt bdt_tmpp = bdt_array_root;
	int level_label = 0;
	int no_ignore_node_count = string_length;

	//set the node counter in the router
	for (int i = 0; i < string_length; i++) {
		if (array_gen->seq_2D_char_input_return(available_route[0][0],i) == '2') {
			no_ignore_node_count--;
		}
	}

	//build the first route
	for (int i = 0; i < string_length; i++) {
		if (array_gen->seq_2D_char_input_return(available_route[0][0],
				array_gen->seq_2D_int_sort_return(i, 0) - 1) == '1') {
			level_label = array_gen->seq_2D_int_sort_return(i, 0);
			bdt_tmpp->val = nodeNamer(level_label);
			bdt_tmpp->right = new bdnode;
			bdt_tmpp->left = NULL;
			bdt_tmpp = bdt_tmpp->right;
			no_ignore_node_count--;
		} else if (array_gen->seq_2D_char_input_return(available_route[0][0],
				array_gen->seq_2D_int_sort_return(i, 0) - 1) == '0') {
			level_label = array_gen->seq_2D_int_sort_return(i, 0);
			bdt_tmpp->val = nodeNamer(level_label);
			bdt_tmpp->right = NULL;
			bdt_tmpp->left = new bdnode;
			bdt_tmpp = bdt_tmpp->left;
			no_ignore_node_count--;
		}
		if (no_ignore_node_count == 0) {
			bdt_tmpp->val = "1";
			bdt_tmpp->right = NULL;
			bdt_tmpp->left = NULL;
		}
	}

	//build the other routes
	//start from the root
	//going along the existing route
	//compare the current node name with the node required in the route
	//if necessary, build extra nodes with the correct node names
	int route_pointer = 1; //skip the first route, which is built
	std::string current_node_string;
	int current_node_int;
	char retrieved_bit_value;
	std::string new_node_name;
	bool name_found;
	int name_position_counter;

	//array for storing the used nodes
	bool *used_node = new bool[string_length];

	while (route_pointer < array_gen->check_available_routes()) {

		//reset the pointer
		//pointing the root
		bdt_tmpp = bdt_array_root;

		//reset the node counter in the route
		no_ignore_node_count = string_length;

		for (int i = 0; i < string_length; i++) {
			if (array_gen->seq_2D_char_input_return(
					available_route[route_pointer][0],
					i) == '2') {
				no_ignore_node_count--;
			}
		}

		//reset the used node array
		for(int i=0;i<string_length;i++){
			used_node[i]=false;
		}

		//keep building the tree
		//until reaching the last element in the route
		while (no_ignore_node_count > 1) {

			//get the current node/bit position/node name
			current_node_string = bdt_tmpp->val.substr(1,
					(bdt_tmpp->val.length() - 1));
			std::stringstream ss1;
			ss1 << current_node_string;
			ss1 >> current_node_int;

			//set the current node
			//used state to true
			for(int i=0;i<string_length;i++){
				if(array_gen->seq_2D_int_sort_return(i,0)==current_node_int){
					used_node[i]=true;
				}
			}

			//retrieve the bit from the array
			//that stores the routing information
			retrieved_bit_value = array_gen->seq_2D_char_input_return(
					available_route[route_pointer][0], current_node_int - 1);

			//route the building sequence using the retrieved bit
			//add extra node if the pointer is pointing to a NULL position
			//skip adding new node if the node already exists
			if (retrieved_bit_value == '0') {
				if (bdt_tmpp->left == NULL) {

					//get the new node name
					name_found = false;
					name_position_counter = 0;
					while(name_found==false){
						if(used_node[name_position_counter]==false && array_gen->seq_2D_char_input_return(available_route[route_pointer][0],array_gen->seq_2D_int_sort_return(name_position_counter,0)-1)!='2'){

							new_node_name = nodeNamer(array_gen->seq_2D_int_sort_return(name_position_counter,0));
							name_found = true;
						}
						name_position_counter++;
					}

					//create the node
					bdt_tmpp->left = new bdnode;

					//name the new node
					bdt_tmpp->left->val = new_node_name;

					//set the left and the right of the new node to NULL
					bdt_tmpp->left->right = NULL;
					bdt_tmpp->left->left = NULL;
				}
				//update the pointer
				bdt_tmpp = bdt_tmpp->left;
				no_ignore_node_count--;
			} else if (retrieved_bit_value == '1') {
				if (bdt_tmpp->right == NULL) {

					//get the new node name
					name_found = false;
					name_position_counter = 0;
					while(name_found==false){
						if(used_node[name_position_counter]==false && array_gen->seq_2D_char_input_return(available_route[route_pointer][0],array_gen->seq_2D_int_sort_return(name_position_counter,0)-1)!='2'){

							new_node_name = nodeNamer(array_gen->seq_2D_int_sort_return(name_position_counter,0));
							name_found = true;
						}
						name_position_counter++;
					}

					//create the node
					bdt_tmpp->right = new bdnode;

					//name the new node
					bdt_tmpp->right->val = new_node_name;

					//set the left and the right of the new node to NULL
					bdt_tmpp->right->right = NULL;
					bdt_tmpp->right->left = NULL;
				}
				//update the pointer
				bdt_tmpp = bdt_tmpp->right;
				no_ignore_node_count--;
			}
			//retrieved bit = 2
			//route to the right
			//the same as retrieved bit = 1
			else{
				if (bdt_tmpp->right == NULL) {

					//get the new node name
					//get the new node name
					name_found = false;
					name_position_counter = 0;
					while(name_found==false){
						if(used_node[name_position_counter]==false && array_gen->seq_2D_char_input_return(available_route[route_pointer][0],array_gen->seq_2D_int_sort_return(name_position_counter,0)-1)!='2'){

							new_node_name = nodeNamer(array_gen->seq_2D_int_sort_return(name_position_counter,0));
							name_found = true;
						}
						name_position_counter++;
					}

					//create the node
					bdt_tmpp->right = new bdnode;

					//name the new node
					bdt_tmpp->right->val = new_node_name;

					//set the left and the right of the new node to NULL
					bdt_tmpp->right->right = NULL;
					bdt_tmpp->right->left = NULL;
				}
				//update the pointer
				bdt_tmpp = bdt_tmpp->right;
			}
		}

		//fill in the value of the last element in the route
		current_node_string = bdt_tmpp->val.substr(1, (bdt_tmpp->val.length() - 1));
		std::stringstream ss;
		ss << current_node_string;
		ss >> current_node_int;

		retrieved_bit_value = array_gen->seq_2D_char_input_return(
				available_route[route_pointer][0], current_node_int - 1);

		if (retrieved_bit_value == '1') {
			bdt_tmpp->right = new bdnode;
			bdt_tmpp->right->val = "1";
			bdt_tmpp->right->right = NULL;
			bdt_tmpp->right->left = NULL;
		} else {
			bdt_tmpp->left = new bdnode;
			bdt_tmpp->left->val = "1";
			bdt_tmpp->left->right = NULL;
			bdt_tmpp->left->left = NULL;
		}
		route_pointer++;
	}

	nodeSetZero(bdt_array_root);

	delete array_gen;

	delete available_route;

	delete used_node;

	return bdt_array_root;
}

std::string evalcompactbdt(bdt t, const std::string& input) {

	bool found = false;
	std::string text;
	int number;

	if(t->val[0]!='x'){
		return t->val;
	}

	while (found == false) {

		text = t->val;
		text = text.substr(1, (text.length() - 1));
		std::stringstream ss;
		ss << text;
		ss >> number;

		if (input[number - 1] == '1') {
			t = t->right;
			if (t->val == "1" || t->val == "0") {
				found = true;
			}
		} else if (input[number - 1] == '0') {
			t = t->left;
			if (t->val == "1" || t->val == "0") {
				found = true;
			}
		}
	}
	return t->val;
}

int binaryToInt(const std::string num) {

	int decimal = 0;
	int length = num.length();

	for (int i = 0; i < length; i++) {
		if (num[length - i - 1] != '0') {
			decimal = decimal + pow(2, i);
		}
	}
	return decimal;
}

std::string nodeNamer(const int level_label) {

	std::stringstream ss;
	ss << "x" << level_label;
	return ss.str();
}

void nodeList(bdt t) {

	if (t != NULL) {
		nodeList(t->right);
		std::cout << t->val << std::endl;
		nodeList(t->left);
	}
}

void nodeSetZero(bdt t) {

	if (t->val[0] == 'x') {
		if (t->right == NULL && t->left != NULL) {
			t->right = new bdnode;
			t->right->val = "0";
			t->right->right = NULL;
			t->right->left = NULL;
		}
		if (t->left == NULL && t->right != NULL) {
			t->left = new bdnode;
			t->left->val = "0";
			t->left->right = NULL;
			t->left->left = NULL;
		}
		nodeSetZero(t->right);
		nodeSetZero(t->left);
	}
}

int nodeCounter(bdt t){
	int count = 0;
	nodeCountAux(t, count);
	return count;
}

void nodeCountAux(bdt t, int &count){
	if(t->val[0]=='x'){
		count++;
		nodeCountAux(t->right, count);
		nodeCountAux(t->left, count);
	}
}
