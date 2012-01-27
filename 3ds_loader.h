#pragma once

#include "model.h"
#include <iosfwd>
#include <stdint.h>


class Model_Loader_3ds
{
	// A chunk in a .3ds file
	struct Chunk
	{
		uint16_t id;
		uint32_t length;
		std::streampos chunk_beginning;

		Chunk():id(0), length(0), chunk_beginning(0){}

		void read_header(std::istream&);
		void skip_body(std::istream&);
	};
	static uint16_t read_vertices(std::istream&, Model&);
	static uint16_t read_polygons(std::istream&, Model&);
	static uint16_t read_texcoords(std::istream&, Model&);
	static std::string read_model_name(std::istream&);
	public:
	static Model read_model(const std::string&, const std::string&);
};
