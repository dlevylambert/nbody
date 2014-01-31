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
}

#endif // _NBODY_INTEGRATE_H
