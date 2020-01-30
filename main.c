#include <stdio.h>
#include <string.h>
#include "crccalc.h"


int main(void) {
	printf("%#x\r\n", Crc32Calc("0123456789", 10));
}