#include <nbody/Integrate.h>
#include <nbody/Vector3.h>
#include <nbody/System.h>
#include <nbody/Body.h>
#include <nbody/Simulation.h>
#include <nbody/constants.h>
#include <gtest/gtest.h>

TEST(TestIntegrate, Riemann1) {
	nbody::System* sys;
	sys = new nbody::System(1);
	float dt = 0;
	nbody::Riemann* riemann;
	riemann = new nbody::Riemann();
	ASSERT_EQ((int) sys->body(0).position().x() , 0);
	ASSERT_EQ((int) sys->body(0).position().y() , 0);
	ASSERT_EQ((int) sys->body(0).position().z() , 0);
	ASSERT_EQ((int) sys->body(0).velocity().x() , 0);
	ASSERT_EQ((int) sys->body(0).velocity().y() , 0);
	ASSERT_EQ((int) sys->body(0).velocity().z() , 0);
	//run integrate
	riemann->Integrate(*sys, dt);
	//std::cout << " velocity " << (int) sys->body(0).velocity().x();
	//expect no change in position or velocity, because just 1 body!!!!
	ASSERT_EQ((int) sys->body(0).position().x() , 0);
	ASSERT_EQ((int) sys->body(0).position().y() , 0);
	ASSERT_EQ((int) sys->body(0).position().z() , 0);
	ASSERT_EQ((int) sys->body(0).velocity().x() , 0);
	ASSERT_EQ((int) sys->body(0).velocity().y() , 0);
	ASSERT_EQ((int) sys->body(0).velocity().z() , 0);	
}

TEST(TestIntegrate, Riemann2) {
	nbody::System* sys;
	sys = new nbody::System(2);
	auto pos = Vector3f{ 0, 0, 0 };
	auto vel = Vector3f{ 1, 1, 1 };
	sys->body(0).setPosition(pos);
	sys->body(0).setVelocity(vel);
	auto pos2 = Vector3f{ 1, 1, 4 };
	auto vel2 = Vector3f{ 2, 2, 2 };
	sys->body(1).setPosition(pos2);
	sys->body(1).setVelocity(vel2);
	float dt = 5;
	nbody::Riemann* riemann;
	riemann = new nbody::Riemann();
	//run integrate
	riemann->Integrate(*sys, dt);
	//std::cout << " velocity " << (int) sys->body(0).velocity().x();
	//expect
	ASSERT_EQ((int) sys->body(0).position().x() , 5);
	ASSERT_EQ((int) sys->body(0).position().y() , 5);
	ASSERT_EQ((int) sys->body(0).position().z() , 5);
	ASSERT_EQ((int) sys->body(0).velocity().x() , 1);
	ASSERT_EQ((int) sys->body(0).velocity().y() , 1);
	ASSERT_EQ((int) sys->body(0).velocity().z() , 1);
	ASSERT_EQ((int) sys->body(1).position().x() , 11);
	ASSERT_EQ((int) sys->body(1).position().y() , 11);
	ASSERT_EQ((int) sys->body(1).position().z() , 14);
	ASSERT_EQ((int) sys->body(1).velocity().x() , 2);
	ASSERT_EQ((int) sys->body(1).velocity().y() , 2);
	ASSERT_EQ((int) sys->body(1).velocity().z() , 2);		
}

TEST(TestIntegrate, RK2) {
	nbody::System* sys;
	sys = new nbody::System(1);
	float dt = 10;
	auto pos = Vector3f{ 1, 1, 4 };
	auto vel = Vector3f{ 1, 2, 3 };
	sys->body(0).setPosition(pos);
	sys->body(0).setVelocity(vel);
	nbody::RK2* rk2;
	rk2 = new nbody::RK2();
	rk2->Integrate(*sys, dt);
	//after Integrate, expect position to be {11, 21, 34}
	ASSERT_EQ((int) sys->body(0).position().x() , 11);
	ASSERT_EQ((int) sys->body(0).position().y() , 21);
	ASSERT_EQ((int) sys->body(0).position().z() , 34);
}

TEST(TestIntegrate, RK4) {
	nbody::System* sys;
	sys = new nbody::System(2);
	auto pos = Vector3f{ 0, 0, 0 };
	auto vel = Vector3f{ 1, 1, 1 };
	sys->body(0).setPosition(pos);
	sys->body(0).setVelocity(vel);
	auto pos2 = Vector3f{ 1, 1, 4 };
	auto vel2 = Vector3f{ 2, 2, 2 };
	sys->body(1).setPosition(pos2);
	sys->body(1).setVelocity(vel2);
	float dt = 5;
	nbody::RK4* rk4;
	rk4 = new nbody::RK4();
	//run integrate
	rk4->Integrate(*sys, dt);
	//std::cout << " velocity " << (int) sys->body(0).velocity().x();
	//expect
	ASSERT_EQ((int) sys->body(0).position().x() , 5);
	ASSERT_EQ((int) sys->body(0).position().y() , 5);
	ASSERT_EQ((int) sys->body(0).position().z() , 5);
	ASSERT_EQ((int) sys->body(0).velocity().x() , 1);
	ASSERT_EQ((int) sys->body(0).velocity().y() , 1);
	ASSERT_EQ((int) sys->body(0).velocity().z() , 1);
	ASSERT_EQ((int) sys->body(1).position().x() , 11);
	ASSERT_EQ((int) sys->body(1).position().y() , 11);
	ASSERT_EQ((int) sys->body(1).position().z() , 14);
	ASSERT_EQ((int) sys->body(1).velocity().x() , 2);
	ASSERT_EQ((int) sys->body(1).velocity().y() , 2);
	ASSERT_EQ((int) sys->body(1).velocity().z() , 2);		

}
