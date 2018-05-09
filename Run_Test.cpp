
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

	//bool 1D array
	bool *seq_1D_bool;

	//n*2^n
	//2D char array
	char **seq_2D_char_input;

	//for sorting
	//bit 0: bit position
	//bit 1: bit = 0 counter
	//bit 2: bit = 1 counter
	//bit 3: max
	//bit 4: sum
	//bit 5: weight/priority
	int **seq_2D_int_sort;

public:

	array_aux(int len) {
		input_string_length = len;
		array_length_1D = pow(2, input_string_length);

		//1D
		seq_1D_bool = new bool[array_length_1D];

		for (int i = 0; i < array_length_1D; i++) {
			seq_1D_bool[i] = false;
		}

		//2D
		seq_2D_char_input = new char*[array_length_1D];

		for (int i = 0; i < array_length_1D; i++) {
			seq_2D_char_input[i] = new char[input_string_length];
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

	int return_array_length_1D() {
		return array_length_1D;
	}

	void seq_1D_bool_set(int position, bool val) {
		seq_1D_bool[position] = val;
	}

	bool seq_1D_bool_return(int position) {
		return seq_1D_bool[position];
	}

	void seq_1D_bool_test() {
		for (int i = 0; i < array_length_1D; i++) {
			std::cout << i << ' ' << seq_1D_bool[i] << std::endl;
		}
		std::cout << std::endl;
	}

	void seq_2D_char_input_set(int position, std::string binary_string) {
		for (int i = 0; i < binary_string.length(); i++) {
			seq_2D_char_input[position][i] = binary_string[i];
		}
	}

	void seq_2D_char_input_set_bit(int position, int bit, char info) {
		seq_2D_char_input[position][bit] = info;
	}

	char seq_2D_char_input_return(int x, int y) {
		return seq_2D_char_input[x][y];
	}

	int seq_2D_char_input_weight(int position){
		int weight = 0;

		for(int i=0; i<input_string_length;i++){
			if(seq_2D_char_input[position][i]!='0'){
				weight+=pow(2,input_string_length-1-i);
			}
		}

		return weight;
	}

	void seq_2D_char_input_test() {

		std::cout << "testing the 2D char input array" << std::endl;

		for (int i = 0; i < array_length_1D; i++) {
			for (int j = 0; j < input_string_length; j++) {
				std::cout << seq_2D_char_input[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int check_available_routes() {
		int available_routes_count = 0;

		for (int i = 0; i < array_length_1D; i++) {
			if (seq_1D_bool[i]) {
				available_routes_count++;
			}
		}
		return available_routes_count;
	}

	void delete_route(int position) {

		seq_1D_bool[position] = false;

		for (int i = 0; i < input_string_length; i++) {
			seq_2D_char_input[position][i] = '2';
		}
	}

	void seq_2D_int_sort_bit_set() {

		//fill in at position 1 and 2
		for (int i = 0; i < array_length_1D; i++) {
			if (seq_1D_bool[i]) {
				for (int j = 0; j < input_string_length; j++) {
					if (seq_2D_char_input[i][j] == '0') {
						seq_2D_int_sort[j][1]++;
					} else if (seq_2D_char_input[i][j] == '1') {
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

	std::cout << "set 1, testing 5cm" << std::endl;

	std::cout << std::endl;

	std::vector<std::string> vector_set1;

	std::string in_set1 = "000000000000000000000000";

	vector_set1.push_back(in_set1);

//	in_set1 = "10000";
//
//	vector_set1.push_back(in_set1);
//
//	in_set1 = "0000000000000000001000000000";
//
//	vector_set1.push_back(in_set1);
//
//	in_set1 = "1000000000000000000000000000";
//
//	vector_set1.push_back(in_set1);

	bdt root_set1 = buildcompactbdt(vector_set1);

	std::cout << "the result is: " << evalcompactbdt(root_set1, "000000000000000000000000") << std::endl;

	std::cout << "the result is: " << evalcompactbdt(root_set1, "000000000000000000000001") << std::endl;

	std::cout << "the result is: " << evalcompactbdt(root_set1, "000000000000000000000010") << std::endl;

	std::cout << "the result is: " << evalcompactbdt(root_set1, "000000000000000000000100") << std::endl;

	std::cout << "the result is: " << evalcompactbdt(root_set1, "000000000000000000001000") << std::endl;

	nodeList(root_set1);

	std::cout << "the number of nodes is: " << nodeCounter(root_set1) << std::endl;

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

	array_aux *array_gen = new array_aux(string_length);

	//load values
	int input_length = fvalues.size();
	for (int i = 0; i < input_length; i++) {
		array_gen->seq_1D_bool_set(binaryToInt(fvalues[i]), true);
		array_gen->seq_2D_char_input_set(binaryToInt(fvalues[i]), fvalues[i]);
	}

	//uncomment the following for testing
	//std::cout << "testing input array before simplifying" << std::endl;
	//array_gen->seq_2D_char_input_test();

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
			if (array_gen->seq_1D_bool_return(i)) {

				match_found = false;
				bit_position = 0;

				while (bit_position < string_length && match_found == false) {

					if(array_gen->seq_2D_char_input_return(i, bit_position) == '0'){
						distance = pow(2, (string_length - bit_position - 1));
						relative_position = i+distance;
						weight_i = array_gen->seq_2D_char_input_weight(i);
						weight_relative = array_gen->seq_2D_char_input_weight(relative_position);
						difference = weight_relative-weight_i;

						if(array_gen->seq_1D_bool_return(relative_position)
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
	//	array_gen->seq_2D_int_sort_test();
	//	array_gen->seq_2D_char_input_test();

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

		if (array_gen->seq_1D_bool_return(i)) {

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

//	array_gen = NULL;

	delete array_gen;

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
