#ifndef _NBODY_INTEGRATE_H
#define _NBODY_INTEGRATE_H

#include <nbody/System.h>

namespace nbody {

	class IntegrateScheme {
		public:
		virtual void Integrate( System& sys, float dt) = 0;
		virtual ~IntegrateScheme();
	};

	class Riemann : public IntegrateScheme {
		public:
		Riemann();
		~Riemann();
		void Integrate( System& sys, float dt); 
		//~Riemann();
	};

	class RungeKutta : public IntegrateScheme {
		public:
		RungeKutta();
		~RungeKutta();
		void Integrate( System& sys, float dt);
	};
}

#endif // _NBODY_INTEGRATE_H
