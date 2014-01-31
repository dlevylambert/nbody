#include <nbody/Integrate.h>
#include <nbody/Vector3.h>
#include <nbody/System.h>

namespace nbody{

	IntegrateScheme::~IntegrateScheme() {
	}

	Riemann::Riemann() { }

	Riemann::~Riemann() { }

	void Riemann::Integrate (System &sys, float dt) {
		sys.computeGravitation();
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

	RungeKutta::RungeKutta() { }

	RungeKutta::~RungeKutta() { }

	void RungeKutta::Integrate (System &sys, float dt) {
		sys.computeGravitation();
		System k1_sys = sys; // deep copy, because we overloaded =
		Vector3f r,v,a;
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * (dt * 0.5f));
			v = v * sys.dampingFactor(); 
			r = r + v * (dt * 0.5f);

			k1_sys.body(i).position() = r;
			k1_sys.body(i).velocity() = v;}
		// at this point k1_sys has 1st order estimate of where
		// system is (position, velocity) at time += dt / 2
		k1_sys.computeGravitation();
		// now k1_sys.body(i).force() records k_1 for i'th body
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = k1_sys.body(i).force();

			v = v + (a * dt);
			v = v * sys.dampingFactor(); 
			r = r + v * dt;

			sys.body(i).position() = r;
			sys.body(i).velocity() = v;}
		// i.e. v(t+dt) = v(t) + k_1 * t where
		// k_1 = acceleration at [dt/2 * a(t)] linearly extended from t

		

		/* what I'm currently writing
		Body *tmp_body = Body[sys.nBodies()]; // to record k1 approximation
		sys.computeGravitation();
		Vector3f r,v,a;
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * dt/2);
			v = v * sys.dampingFactor(); 
			r = r + v * dt/2;

			tmp_body[i].position() = r;
			sys.body[i].velocity() = v;
		*/
		

	}


}
