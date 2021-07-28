#include "uart_driver.c"
#include <stdio.h>
/** Found out that was a mistake referencing the "UART DRIVER" to uart_driver.h
and I changed the correct path to the uart_driver.c in order to compile and run the
program**/

void print_sensor_data(sensor_data_t *sensor_data);

int main() {
        sensor_data_t sensor_data;
        get_sensor_data(&sensor_data);
        print_sensor_data(&sensor_data);
}

/** the data from the sensor comes in as following:
 * 1. id            [char,  1 bytes]
 * 2. int_data      [int,   4 bytes]
 * 3. short_data    [short, 2 bytes]
 * 4. char_data     [char,  1 bytes]
 */

/** I read all the documentation from the serial folder and I understood the
functionality of the "UART DRIVER" and all the connections between uart_driver.c
and uart_driver.h files.
    I implemented the requested "get_sensor_data()" function in order to get the
expected output as mentioned on the challenge 3 problem statement.
    In order to acces the char array with the bytes values, we need to start
the "communication function" and after that, according to the statement above
with the format of the data coming from the sensor, I assigned the returned value
of the first call of the "uart_driver_get_byte()" function to the sensor_data pointer
on the id variable.
    After this first call, given the fact that the "uart_driver_get_byte()" function
has an array_iterator, on the next call the returned value will be on the second
position pointed by the array_iterator wich will be on position 1.Knowing that the "int_data"
from the sensor is declared in 4 bytes, we have to store all those bytes values
in a new int array named bytes[] and loop trough it to set the values according
to the char data[] array in the "uart_driver_get_byte()" function.
    After the loop is closed and all the data was copied to the new array with
the correct values starting from postion 1 to position 4 of the char data[] array,
we can do the bitshifting and store the int values in the sensor_data pointer
on the int_data variable.
    At this point we have 5 calls of the "uart_driver_get_byte()" function and on
the next call, the first value returned will be from position 5. Given the fact
that the next value to be stored is a short type in 2 bytes size, we have to repeat
the previous procedure with a loop and store the values in the bytes array from
position 5 to 6 and do the bitshifting and save the values in the sensor_data
pointer on the short_data variable.
    The last position is char type 1 byte size and we can store the value directly
with one last call of the "uart_driver_get_byte()" function to the sensor_data
pointer on the char_data variable.
    The last step is to execute the "stop_communication" function;**/

void get_sensor_data(sensor_data_t *sensor_data) {
        uart_driver_start_communication();
        sensor_data->id = uart_driver_get_byte();
        int bytes[4];
        for (int i = 0; i < 4; ++i) {
            bytes[i] = uart_driver_get_byte();
        }
        sensor_data->int_data = bytes[0] | ( (int)bytes[1] << 8 ) | ( (int)bytes[2] << 16 ) | ( (int)bytes[3] << 24 );
        for (int i = 0; i < 2; ++i) {
            bytes[i]= uart_driver_get_byte();
        }
        sensor_data->short_data = bytes[0] | ( (int)bytes[1] << 8 );
        sensor_data->char_data = uart_driver_get_byte();
        uart_driver_stop_communication();
}

void print_sensor_data(sensor_data_t *sensor_data) {
        printf("id: %d\n", sensor_data->id);
        printf("int_data: %d\n", sensor_data->int_data);
        printf("short_data: %d\n", sensor_data->short_data);
        printf("char_data: %d\n", sensor_data->char_data);
}
