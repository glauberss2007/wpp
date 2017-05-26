//
//  algorithmcont.h
//  algorithm
//
//  Created by Alan Robert Resende de Freitas on 26/03/15.
//  Copyright (c) 2015 Alan. All rights reserved.
//

#ifndef __algorithm__utilities__
#define __algorithm__utilities__

// C++ headers
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

namespace utils {
    // shared variables
    static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
    static const double inf = std::numeric_limits<double>::infinity();
    static const double pi = 3.14159265358979323846;
}

// String utils
#include "string_utils.h"
// File utils
#include "file_utils.h"
// STL shortcuts (ie. sort(v) instead of sort(v.begin(),v.end()) without boost range)
#include "stl_shortcuts.h"
// treat containers as matrices
#include "container_utils.h"
// return containers with some properties
#include "numeric_functions.h"
// numerical operations for containers (element by element)
#include "container_overloads.h"
// generator of random numbers
//#include "generator.h"
// functions for statistics
#include "stats.h"




#endif /* defined(__algorithm__utilities__) */
