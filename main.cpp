#include <nbody/Simulation.h>

#include <iostream>
#include <fstream>

/*int main() {
  try {
    std::ifstream input{ "resources/nbody/binary-system-simple.txt" };
    nbody::Simulation sim{input};
    for( int i = 0; i < 200; ++i ) {
      std::cout << "==EVOLUTION OF " << i + 1 << "\n";
      sim.saveRun();
      sim.evolveSystem( 1e4, 0.000001 );
    }
    sim.saveRun();
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}*/

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
