/*
 * generator.h
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#ifndef INCLUDE_GENERATOR_H_
#define INCLUDE_GENERATOR_H_

#include "Pythia8/Pythia.h"
#include <vector>
#include "particle.h"

class generator{
public:

    generator();

    std::vector<particle> generateEvent();

private:
    mutable Pythia8::Pythia pythia_;
};




#endif /* INCLUDE_GENERATOR_H_ */
