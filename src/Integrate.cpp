
#include "../include/nbody/System.h"
#include "../include/nbody/Integrate.h"
#include "../include/nbody/Vector3.h"

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

	RK2::RK2() { }

	RK2::~RK2() { }

	void RK2::Integrate (System &sys, float dt) {
		sys.computeGravitation(); // sys.body(i).force() records k_1
		System k2_sys = sys; // deep copy, because we overloaded =
		Vector3f r,v,a;
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * (dt * 0.5f));
			v = v * sys.dampingFactor(); 
			r = r + v * (dt * 0.5f);

			k2_sys.body(i).position() = r;
			k2_sys.body(i).velocity() = v;}
		// at this point k2_sys has 1st order estimate of where
		// system is (position, velocity) at time += dt / 2
		k2_sys.computeGravitation();
		// now k1_sys.body(i).force() records k_2 for i'th body
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = k2_sys.body(i).force();

			v = v + (a * dt);
			v = v * sys.dampingFactor(); 
			r = r + v * dt;

			sys.body(i).position() = r;
			sys.body(i).velocity() = v;}
		// i.e. v(t+dt) = v(t) + k_2 * t where
		// k_2 = acceleration at [dt/2 * a(t)] linearly extended from t
	}

	RK4::RK4() { }

	RK4::~RK4() { }

	void RK4::Integrate (System &sys, float dt) {
		sys.computeGravitation(); // sys.body(i).force() records k_1
		System k2_sys = sys; // deep copy, because we overloaded =
		Vector3f r,v,a;
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * (dt * 0.5f));
			v = v * sys.dampingFactor(); 
			r = r + v * (dt * 0.5f);

			k2_sys.body(i).position() = r;
			k2_sys.body(i).velocity() = v;}
		// at this point k2_sys has 1st order estimate of where
		// system is (position, velocity) at time += dt / 2
		k2_sys.computeGravitation();
		// now k2_sys.body(i).force() records k_2
		// compute k_3: sys starts at time t but with force k_2
		System k3_sys = sys;
		for (size_t i = 0; i < sys.nBodies(); i++) {
			k3_sys.body(i).force() = k2_sys.body(i).force();
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * (dt * 0.5f));
			v = v * sys.dampingFactor();
			r = r + v * (dt * 0.5f);

			k3_sys.body(i).position() = r;
			k3_sys.body(i).velocity() = v;}
		k3_sys.computeGravitation();
		// now compute k4
		System k4_sys = sys;
		for (size_t i = 0; i < sys.nBodies(); i++) {
			k4_sys.body(i).force() = k3_sys.body(i).force();
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force();

			v = v + (a * dt);
			v = v * sys.dampingFactor();
			r = r + v * dt;

			k4_sys.body(i).position() = r;
			k4_sys.body(i).velocity() = v;}
		k4_sys.computeGravitation();
		for( size_t i = 0; i < sys.nBodies(); i++) {
			r = sys.body(i).position();
			v = sys.body(i).velocity();
			a = sys.body(i).force() + k2_sys.body(i).force()*2.0f
			    + k3_sys.body(i).force()*2.0f + k4_sys.body(i).force();
			a = a * (1.0f / 6.0f);

			v = v + (a * dt);
			v = v * sys.dampingFactor(); 
			r = r + v * dt;

			sys.body(i).position() = r;
			sys.body(i).velocity() = v;}
		// i.e. v(t+dt) = v(t) + k_2 * t where
		// k_2 = acceleration at [dt/2 * a(t)] linearly extended from t
	}
}
