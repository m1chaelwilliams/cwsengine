#ifndef CWS_OBJLOADER_H
#define CWS_OBJLOADER_H

#include "models/mesh.h"
#include "models/model.h"
#include "utils/debug.h"

#include <vector>
#include <fstream>
#include <sstream>

namespace cws::models {

	class ObjLoader {
		public:

		static bool file_exists(const char* filename) {
			std::ifstream stream(filename);

			if (!stream.is_open()) {
				return false;
			}

			stream.close();
			return true;
		}

		static models::Mesh load_mesh(const char* filename) {
			
			std::ifstream stream(filename);

			std::vector<glm::vec3> positions;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec2> uvs;
			std::vector<data::Vertex> vertices;
			std::vector<GLuint> indices;
			int index_offset = 0;

			std::string line;
			while (std::getline(stream, line)) {

				std::istringstream iss(line);

				std::string token;

				iss >> token;

				if (token == "v") {
					// add position vector

					glm::vec3 pos;
					iss >> pos.x >> pos.y >> pos.z;

					positions.push_back(pos);

				} else if (token == "vt") {
					// add texture coord

					glm::vec2 uv;
					iss >> uv.x >> uv.y;

					uvs.push_back(uv);

				} else if (token == "vn") {
					// add normal vector

					glm::vec3 normal;
					iss >> normal.x >> normal.y >> normal.z;

					normals.push_back(normal);
				} else if (token == "f") {
					// process parallel data into Vertex struct
					
					// format:
					// f <v / uv / n> <v / uv / n> <v / uv / n>

					int num_vertices = 0;
					std::string entry;
					while (iss >> entry) {

						int v_i, vt_i, vn_i;
						char slash;

						std::istringstream iss_entry(entry);

						iss_entry >> v_i >> slash >> vt_i >> slash >> vn_i;

						// process v uv n into Vertex;
						data::Vertex v;
						
						v.position = positions[v_i - 1];
						v.uv = uvs[vt_i - 1];
						v.normal = normals[vn_i - 1];

						vertices.push_back(v);

						num_vertices++;
					}

					int start_index = index_offset;
					for (int i = 0; i <= num_vertices - 3; i++) {
						indices.push_back(start_index);
						indices.push_back(start_index+1 + i);
						indices.push_back(start_index+2 + i);
					}

					index_offset += num_vertices;
				}
			}

			stream.close();

			return models::Mesh(
				vertices,
				indices
			);
		};

	};

};

#endif