#ifndef _NBODY_INTEGRATE_H
#define _NBODY_INTEGRATE_H

#include "System.h"

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
	};

	class RK2 : public IntegrateScheme {
		public:
		RK2();
		~RK2();
		void Integrate( System& sys, float dt);
	};

	class RK4 : public IntegrateScheme {
		public:
		RK4();
		~RK4();
		void Integrate( System& sys, float dt); 
	};

}

#endif // _NBODY_INTEGRATE_H
