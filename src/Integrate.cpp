#include <nbody/Integrate.h>
#include <nbody/Vector3.h>
#include <nbody/System.h>

namespace nbody{

	IntegrateScheme::~IntegrateScheme() {
	}

	Riemann::Riemann() { }

	Riemann::~Riemann() { }

	void Riemann::Integrate (System &sys, float dt) {
		Vector3f r,v,a;
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * dt);
			v = v * sys.dampingFactor(); 
			r = r + v * dt;

			sys.body(i).position() = r;
			sys.body(i).velocity() = v;
		}
	}
}
