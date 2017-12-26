#include <iostream>
#include <vector>
#include <Windows.h>
#include "Paint.h"
#include "vrpn_Tracker.h"

#pragma comment(lib,"user32.lib")

using namespace std;
POINT pt;
DWORD dwEventFlags;

struct JOINT{
	double x;
	double y;
	double z;
} typedef JOINT3D;

//Get articulation positions
static JOINT3D right_hand = {0.0,0.0,0.0};
static JOINT3D right_elbow = {0.0,0.0,0.0};

// Condition for comparison
static bool START_COMPARISON = false;
static int index_first_joint = 12;
static int index_last_joint = 14;

void geste3(double mainDx, double mainDy, double mainDz){
	int xpaint;
	int ypaint;
	if (mainDx != 0){
		xpaint = mainDx * 2160 * 2;
		ypaint = ((mainDy - 0.5) *(-1)) * 1440 * 2;
		pt.x = xpaint;
		pt.y = ypaint;
		SetCursorPos(pt.x, pt.y);
		// on ecrit sur paint 
		if (mainDz < 1.1){
			//move the mouse
			Mouse_Event(MOUSEEVENTF_ABSOLUTE or MOUSEEVENTF_MOVE,Pt.x,Pt.y,0,0);
			//simulate the left mouse button down
			mouse_event(MOUSEEVENTF_LEFTDOWN, pt.x, pt.y, 0, 0);
			SetCursorPos(pt.x, pt.y);
		}

	}
}

void geste2(double mainRight_y,double coudeRight_y){
	//Geste Fermeture
	if (mainRight_y >coudeRight_y){
		std::cout << "Open the paint" << std::endl;
		system("mspaint.exe");
		geste3(right_hand.x,right_hand.y,right_hand.z);
		Sleep(1000);
	}
	if (mainRight_y < coudeRight_y ){
		std::cout << "Fermeture de Paint" << std::endl;
		system("taskkill /IM mspaint.exe");
	
	}
}


void VRPN_CALLBACK handle_tracker( void* userData, const vrpn_TRACKERCB b )
{
	if(b.sensor == index_first_joint){
		START_COMPARISON = false; 
	}
	if(b.sensor == 12 ){
		right_elbow.x = b.pos[0];
		right_elbow.y = b.pos[1];
		right_elbow.z = b.pos[2];
	}
	if(b.sensor == 14 ){
		right_hand.x = b.pos[0];
		right_hand.y = b.pos[1];
		right_hand.z = b.pos[2];
	}
	if(b.sensor == index_last_joint){
		START_COMPARISON = true; 
	}
	if(START_COMPARISON == true){
		geste2(right_hand.y,right_elbow.y );
	}

}


int main(int argc, char* argv[])
{

	vrpn_Tracker_Remote* vrpnTracker = new vrpn_Tracker_Remote("Tracker0@172.16.169.2:3883");

	vrpnTracker->register_change_handler( 0, handle_tracker );

	while(1)
	{

		vrpnTracker->mainloop();
		Sleep(1000);
	}

	return 0;
}