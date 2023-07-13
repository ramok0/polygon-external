#include <polygon.hpp>

bool config::init(void) {
	config::config_t defaultConfig = { 0 };

	return config->exists() ? config->read() : config->initialize(defaultConfig);
}