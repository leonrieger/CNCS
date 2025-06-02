#pragma once //typedef
#include <stdint.h>
#include <string>
using namespace std;

class USB_Serial {
public:
	USB_Serial();
	void begin(const char[], uint16_t);
	~USB_Serial();
	bool Serial();
	uint16_t available();//How much to be read
	string read();
	void write();
private:
	bool connected;
};
