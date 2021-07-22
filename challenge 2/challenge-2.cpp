#include <iostream>
#include <cstring>
using namespace std;

/*Found out that the given structure example has char array was declared
wrong and the program couldn't compile */
typedef struct {
	char source[10];
	int id;
	unsigned long timestamp;
	int temperature;
	int humidity;
	int pressure;
} measurement_t;

/* Beeing the first time I worked with the serialization concept, I found out that
 there are a lot of things to take in consideration, specially the endianness that
 refers to the order of sequence of bytes to be transmitted.
   This is the best approach I could implement to transmit the serialized data from
 the given structure and deserialize it afterward*/

void serialize (measurement_t measurements, char b[]) {
	memcpy(b, &measurements, sizeof(measurements));
}

void deserialize (measurement_t measurements, char b[]) {
	measurement_t temp;
	memcpy(&temp, b, sizeof(temp));
	cout << temp.source << "\n";
	cout << temp.id << "\n";
	cout << temp.timestamp << "\n";
	cout << temp.temperature << "\n";
	cout << temp.humidity << "\n";
	cout << temp.pressure << "\n";

}

int main () {
	measurement_t measurements;
	char b[sizeof(measurements)];
	char message[10] = "info";
	for (int i = 0; i <= strlen(message); ++i) {
		measurements.source[i] = message[i];
	}
	measurements.id = 12;
	measurements.timestamp = 210721;
	measurements.temperature = 34;
	measurements.humidity = 87;
	measurements.pressure = 1134;
	serialize (measurements, b);
	deserialize(measurements, b);
}
/* To test my program I gave random values to the collection of the variables
 included in the "measurement_t" given structure.*/
