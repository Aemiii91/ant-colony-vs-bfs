#include "edge.h"
bool Edge::operator==(const Edge &foo) {
	if (dist == foo.dist && weight == foo.weight)
		return true;
	else
		return false;
}

bool Edge::operator!=(const Edge &foo) {
	if (dist != foo.dist || weight != foo.weight)
		return true;
	else
		return false;
}