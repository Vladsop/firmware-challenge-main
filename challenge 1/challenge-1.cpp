#include <iostream>
#include <bitset>
using namespace std;

/*Created a function that converts every byte from the array to binary(string),
 and after that in a single loop through of the array we display every position
 to the requested characters according to the binary values.*/
void print_led_matrix (int bytes_array[8]) {
	string led_array[8];
	for (int i = 0; i < sizeof(led_array)/sizeof(led_array[0]); ++i) {
		bitset<8> b1 (bytes_array[i]);
		cout << b1.to_string('.', '#') << "\n";
	}
    cout << "\n";
}

int main () {
	int A[] = {0x00, 0x18, 0x24, 0x24, 0x7E, 0x42, 0x42, 0x00};
	int B[] = {0x00, 0x3f, 0x41, 0x61, 0x3f, 0x61, 0x41, 0x3f};
	int C[] = {0x00, 0xfc, 0x82, 0x86, 0xfc, 0x86, 0x86, 0xfc};
	print_led_matrix(A);
	print_led_matrix(B);
	print_led_matrix(C);
}
/*Found out that for the second given example in the challenge, according to the
array byte values, the expected result is not the same that is displayed on the
challenge.
  For that I created a new array with the correct example to display the characters
that match the same output as the second example display output on the challenge.*/
