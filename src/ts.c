#include "common.h"
#include "ts.h"

int wait4touch(int touch_panel)
{
	struct input_event event;

	int x = 0;
	while(1)
	{
		bzero(&event, sizeof(event));
		read(touch_panel, &event, sizeof(event));	

		// some coordinations from the TP is ready
		if(event.type == EV_ABS)
		{
			x = event.code==ABS_X ? event.value : x;
		}

		// state of TP has changed
		if(event.type == EV_KEY)
		{
			// release the TP
			if(event.code  == BTN_TOUCH &&
		   	   event.value == 0)
			{
				break;
			}
		}
	}

	return x<400 ? PREV : NEXT;
}
