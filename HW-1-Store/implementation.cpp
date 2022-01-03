#include "interface.h"
#include "MyStore.hpp"
#include <iostream>
#include <vector>

Store *createStore() {
	return new MyStore();
}

