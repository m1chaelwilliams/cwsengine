#ifndef CWS_FILEUTILS_H
#define CWS_FILEUTILS_H

#include <fstream>

#include "utils/debug.h"

namespace cws::utils {

	inline const std::string read_file_contents(const std::string& filename) {
		std::fstream stream(filename);

		if (!stream.is_open()) {
			CWS_LOGLN("Failed to open shader: " << filename);
			return "";
		}

		std::string result;

		std::string line;
		while (std::getline(stream, line)) {
			result += line + "\n";
		}

		stream.close();

		return result;
	}

};

#endif