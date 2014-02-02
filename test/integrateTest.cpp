#include <nbody/Integrate.h>
#include <nbody/Vector3.h>
#include <nbody/System.h>
#include <nbody/Body.h>
#include <gtest/gtest.h>

TEST(IntegrateTest, Riemann) {
	nbody::System* sys;
	sys = new nbody::System(1);
	float dt = 0;
	nbody::Riemann* riemann;
	riemann = new nbody::Riemann();
	riemann->Integrate(*sys, dt);
	//return (int) sys->body(0).position().x();
	ASSERT_EQ((int) sys->body(0).position().x() , 0);
	//boolean position = (int) sys.body(0).position().x() == 0 && (int) sys.body(0).position().y() == 0 && (int) sys.body(0).position().z() == 0;
	//boolean velocity = (int) sys.body(0).velocity().x() == 0 && (int) sys.body(0).velocity().y() == 0 && (int) sys.body(0).velocity().z() == 0;
	//if (position && velocity) {
		//return 0;
	//}
	//else {
		//return 1;
	//}
	//return 0;
}
