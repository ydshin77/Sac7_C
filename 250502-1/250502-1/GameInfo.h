#pragma once

#include <iostream>

#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr;}