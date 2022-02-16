#pragma once

class Command {
public:
	const char* operator[](int index) const;
	int count() const;

	int args_count;
	int args_size;
	char arg_s_buffer[512];
	char arg_v_buffer[512];
	const char* args[664];
};

inline
const char* Command::operator[](int index) const {
	return this->args[index];
}

inline
int Command::count() const {
	return this->args_count;
}
