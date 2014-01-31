#include <nbody/constants.h>
#include <nbody/System.h>
#include <nbody/Vector3.h>
#include <nbody/Integrate.h>

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace nbody {

  System::System(const System &sys): _nBodies(sys.nBodies()), _body(new Body[sys.nBodies()]), _softFactor(1e-9f), 
  _dampingFactor(1.0f) {
	// create deep copy of Bodies
	for(size_t i = 0; i < _nBodies; i++){
		_body[i] = sys.body(i);
	}
  }

  System& System::operator=(const System &sys){
	if (this != &sys){
		_nBodies = sys.nBodies();
		delete _body;
		_body = new Body[_nBodies];
		for(size_t i = 0; i < _nBodies; i++){
			_body[i] = sys.body(i);
		}
		_softFactor = sys.softFactor();
		_dampingFactor = sys.dampingFactor();
	}
	return *this;

  }

  inline void System::interactBodies( size_t i, size_t j, float x_softFactor, Vector3f &acc ) const {
    Vector3f r = _body[j].position() - _body[i].position();
    float distance = r.norm() + x_softFactor;
    float invDist = 1.0f / distance;
    float invDistCubed = cube( invDist );
    acc = acc + NEWTON_G * _body[j].mass() * invDistCubed * r;
  }

  void System::computeGravitation() {
    for( size_t i = 0; i < _nBodies; ++i ) {
      Vector3f acc{ 0.0f, 0.0f, 0.0f };
      for( size_t j = 0; j < _nBodies; ++j ) {
        if( i != j ) {
          interactBodies( i, j, _softFactor, acc );
        }
      }
      _body[i].force() = acc;
    }
  }

  void System::integrateSystem( float dt ) {
    //Vector3f r, v, a;
    //for( size_t i = 0; i < _nBodies; ++i ) {
    //  r = _body[i].position();
    //  v = _body[i].velocity();
    //  a = _body[i].force();

      //v = v + ( a * dt );
      //v = v * _dampingFactor;
      //r = r + v * dt;

      //_body[i].position() = r;
      //_body[i].velocity() = v;
    //}
	//RungeKutta *rungekutta = new RungeKutta();
	//rungekutta->Integrate(*this,dt);
	Riemann *riemann = new Riemann();
	riemann->Integrate(*this,dt);
  }

  void System::update( float dt ) {
    // computeGravitation(); bring this into "integrateSystem( dt )"
    integrateSystem( dt );
  }

  void System::readState( std::istream &input ) {
    input >> _nBodies;
    if( _nBodies > MAX_BODIES_RECOMMENDED ) {
      throw std::runtime_error( "Too many input bodies" );
    }
    _body = new Body[_nBodies];
    for( size_t i = 0; i < _nBodies; ++i ) {
      input >> _body[i];
    }
  }

  void System::writeState( std::ostream &output ) const {
    output << _nBodies << "\n";
    for( size_t i = 0; i < _nBodies; ++i ) {
      output << _body[i] << "\n";
    }
  }

} // namespace nbody
