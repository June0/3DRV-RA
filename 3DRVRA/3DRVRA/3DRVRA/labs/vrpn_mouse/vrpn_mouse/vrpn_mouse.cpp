#include "vrpn_Analog.h"
#include "vrpn_Button.h"


#include <iostream>
using namespace std;
int flag =1;
float x,y;
string zone;


void VRPN_CALLBACK handle_button( void* userData, const vrpn_BUTTONCB b )
{
	cout << "Button '" << b.button << "': " << b.state << endl;
	if(b.button == 0){
		printf("\a");
	}
	if(b.button == 0 && b.state == 0)
	{
		flag = 0;
	}
	if(b.button == 2 && b.state == 0)
	{
		flag =1;
	}

}

void VRPN_CALLBACK handle_analog( void* userData, const vrpn_ANALOGCB a)
{
	x = a.channel[0];
	y = a.channel[1];

	if(flag == 0){
		//
	}


	if(flag == 1)
	{
		int nbChannels = a.num_channel;

		//cout << "Analog : ";
		for( int i=0; i < a.num_channel; i++ )
		{
			//cout << a.channel[i] << " ";
			if (0<x && x< 0.5 && 0<y && y<0.5 )
			{
				zone = 'A';
				cout << a.channel[i] << " ";
				cout << zone.c_str() << " ";
			}
			else if (0.5<x && x< 1 && 0<y && y<0.5 )
			{
				zone = 'B';
				cout << x << " ";
				cout << y << " ";
				cout << zone.c_str() << " ";
			}
			else if (0<x && x< 0.5 && 0.5<y && y<1 )
			{
				zone = 'C';
				cout << x << " ";
				cout << y << " ";
				cout << zone.c_str() << " ";
			}
			else if (0.5<x && x< 1 && 0.5<y && y<1 )
			{
				zone = 'D';
				cout << x << " ";
				cout << y << " ";
				cout << zone.c_str() << " ";
			}
			else if (x == 0.5)
			{
				printf("\a");	
			}
			else if (y == 0.5)
			{
				printf("\a");	
			}
	    }

		cout << endl;
	}


}


int main(int argc, char* argv[])
{
	vrpn_Analog_Remote* vrpnAnalog = new vrpn_Analog_Remote("Mouse0@localhost:3883");
	vrpn_Button_Remote* vrpnButton = new vrpn_Button_Remote("Mouse0@localhost:3883");

	vrpnAnalog->register_change_handler( 0, handle_analog);
	vrpnButton->register_change_handler( 0, handle_button );

	while(1)
	{
		vrpnAnalog->mainloop();
		vrpnButton->mainloop();

		Sleep(100);
	}

	return 0;
}