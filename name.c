#include <usb_names.h>
#define MANUFACTURER_NAME  {'P', 'J', 'R', 'C'}
#define MANUFACTURER_NAME_LEN 4

#define PRODUCT_NAME {'R', 'o', 't', 'a', 'r', 'y', ' ', 'N', 'u', 'm', 'p', 'a', 'd'}
#define PRODUCT_NAME_LEN 13
#define SERIAL_NUMBER {'3','1','4','1','5','9'} 
#define SERIAL_NUMBER_LEN 6

struct usb_string_descriptor_struct usb_string_manufacturer_name = {
	2 + MANUFACTURER_NAME_LEN * 2,
	3,
	MANUFACTURER_NAME};

struct usb_string_descriptor_struct usb_string_product_name = {
	2 + PRODUCT_NAME_LEN * 2,
	3,
	PRODUCT_NAME};

struct usb_string_descriptor_struct usb_string_serial_number = {
	2 + SERIAL_NUMBER_LEN * 2,
	3,
	SERIAL_NUMBER};
