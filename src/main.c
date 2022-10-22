#include "test-driver.h"
#include "test-lib.h"
#include "platform/stm32f407G/include/platform_init.h"

int main()
{
	platform_init();

	int result = 0;

	result = testlib(result);
	result = testdriver(result);

	while(1){}
	
	return 0;
}