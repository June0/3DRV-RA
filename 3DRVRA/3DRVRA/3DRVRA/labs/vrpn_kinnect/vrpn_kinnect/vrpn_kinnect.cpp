
#include "vrpn_Tracker.h"

#include <iostream>
using namespace std;

struct JOINT{
	float x;
	float y;
	float z;
} typedef JOINT3D;

//Get articulation positions
static JOINT3D left_hand = {0.0f,0.0f,0.0f};
static JOINT3D right_hand = {0.0f,0.0f,0.0f};
static JOINT3D head = {0.0f,0.0f,0.0f};
static JOINT3D left_elbow = {0.0f,0.0f,0.0f};
static JOINT3D right_elbow = {0.0f,0.0f,0.0f};

// Condition for comparison
static bool START_COMPARISON = false;
static int index_first_joint = 0;
static int index_last_joint = 14;


void VRPN_CALLBACK handle_tracker( void* userData, const vrpn_TRACKERCB b )
{

	if(b.sensor == index_first_joint){
		START_COMPARISON = false; 
	}
	//read the needed joints
	if(b.sensor == 0 ){
		head.x = b.pos[0];
		head.y = b.pos[1];
		head.z = b.pos[2];
	}
	if(b.sensor == 6 ){
		left_elbow.x = b.pos[0];
		left_elbow.y = b.pos[1];
		left_elbow.z = b.pos[2];
	}

	if(b.sensor == 8 ){
		left_hand.x = b.pos[0];
		left_hand.y = b.pos[1];
		left_hand.z = b.pos[2];
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

		//Left hand x > left elbow x - hand up ...
		if(left_hand.y>left_elbow.y ){
			cout<<"draw a line"<<endl;
			cout<<left_hand.x<<endl;
			cout<<left_hand.y<<endl;
			cout<<left_hand.z<<endl;

		}
		if(left_hand.y<left_elbow.y ){
			cout<<"draw a dotted line"<<endl;
		}
		if(right_hand.y>right_elbow.y ){
			cout<<"draw red line"<<endl;
			cout<<right_hand.x<<endl;
			cout<<right_hand.y<<endl;
			cout<<right_hand.z<<endl;
		}
		if(right_hand.y<right_elbow.y ){
			cout<<"draw a blue line"<<endl;
		}
		if(abs(left_hand.x - right_hand.x)<0.1 && (left_hand.y - right_hand.y)<0.1 && (left_hand.z - right_hand.z)<0.1){
			cout<<"applause"<<endl;
		}

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
}*/
