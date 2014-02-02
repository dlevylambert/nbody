#include "../include/nbody/Integrate.h"
#include "../include/nbody/System.h"
#include "../include/nbody/constants.h"
#include "../include/nbody/Simulation.h"
#include "../include/nbody/Vector3.h"
#include "../include/nbody/Body.h"
#include <iostream>
#include <iomanip>

int TestRiemannIntegrate() {
	//System sys = new System(1);
	//float dt = 0;
	//Riemann riemann = new Riemann();
	//riemann.Integrate(sys, dt);
	//boolean position = (int) sys.body(i).position().x() == 0 && (int) sys.body(i).position().y() == 0 && (int) sys.body(i).position().z() == 0;
	//boolean velocity = (int) sys.body(i).velocity().x() == 0 && (int) sys.body(i).velocity().y() == 0 && (int) sys.body(i).velocity().z() == 0;
	//if (position && velocity) {
	//return 0;
	//}
	//else {
	//return 1;
	//}
	return 0;
}

int main() {
  std::cout << "Test 1: " << TestRiemannIntegrate() << "\n";
}
