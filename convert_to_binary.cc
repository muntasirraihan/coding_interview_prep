#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

string convert_to_binary(string s) {
	int dot_pos = s.find('.');
	int integral_part = 0;
	bool has_decimal = false;
	double decimal_part = 0;
	if (dot_pos != string::npos) {
		string intergral_string = s.substr(0, dot_pos);
		integral_part = atoi(intergral_string.c_str());
		decimal_part = atof(s.c_str()) - integral_part; 
		has_decimal = true;
	} else {
		integral_part = atoi(s.c_str());
	}

	string integral_part_binary;
	if (integral_part == 0) {
		integral_part_binary = "0";
	} else {
		while (integral_part > 0) {
			int lowest_digit = integral_part & 1;
			integral_part = integral_part >> 1; 
			integral_part_binary = to_string(lowest_digit)
									 + integral_part_binary;
		}
	}

	if (!has_decimal) return integral_part_binary;

	string decimal_part_binary = ".";
	
	while (decimal_part > 0 && decimal_part_binary.size() < 10) {
		decimal_part *= 2;
		int digit = int(decimal_part);
		decimal_part -= digit;
		decimal_part_binary = decimal_part_binary + to_string(digit); 
	}	

	return integral_part_binary + decimal_part_binary;
}

int main() {
	cout << convert_to_binary("4.728") << endl;
}