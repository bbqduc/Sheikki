#include <fstream>
#include <iostream>
#include <cassert>
#include <stdint.h>
#include <string>
#include "model.h"
#include "3ds_loader.h"

#define MAIN_CHUNK 0x4D4D
#define VERSION 0x0010
#define EDITOR_CHUNK 0x3D3D
#define OBJECT_BLOCK 0x4000
#define TRIANGULAR_MESH 0x4100
#define VERTICES_LIST 0x4110
#define FACES_DESCRIPTION 0x4120
#define FACES_MATERIAL 0x4130
#define MAPPING_COORDINATES_LIST 0x4140
#define SMOOTHING_GROUP_LIST 0x4150
#define LOCAL_COORDINATES_SYSTEM 0x4160
#define LIGHT 0x4600
#define SPOTLIGHT 0x4610
#define CAMERA 0x4700
#define MATERIAL_BLOCK 0xAFFF
#define MATERIAL_NAME 0xA000
#define AMBIENT_COLOR 0xA010
#define DIFFUSE_COLOR 0xA020
#define SPECULAR_COLOR 0xA030
#define TEXTURE_MAP 1 0xA200
#define BUMP_MAP 0xA230
#define REFLECTION_MAP 0xA220
#define MAPPING_FILENAME 0xA300
#define MAPPING_PARAMETERS 0xA351
#define KEYFRAMER_CHUNK 0xB000
#define MESH_INFORMATION_BLOCK 0xB002
#define SPOT_LIGHT_INFORMATION BLOCK 0xB007
#define FRAMES 0xB008
#define OBJECT_NAME 0xB010
#define OBJECT_PIVOT_POINT 0xB013
#define POSITION_TRACK 0xB020
#define ROTATION_TRACK 0xB021
#define SCALE_TRACK 0xB022
#define HIERARCHY_POSITION 0xB030

std::string Model_Loader_3ds::read_model_name(std::istream& infile)
{
	std::string name;
	assert(infile);
	char temp;
	do
	{
		infile.read(&temp, 1);
		name.push_back(temp);
	}while(temp != '\0');

	return name;
}

uint16_t Model_Loader_3ds::read_vertices(std::istream& infile, Model& model)
{
	assert(infile);
	infile.read((char*)&model.num_vertices, 2);

	model.vertices = new glm::vec3[model.num_vertices];
	for(uint16_t i = 0; i < model.num_vertices; ++i)
		for(int j = 0; j < 3; ++j)
			infile.read((char*)&model.vertices[i][j], sizeof(float));

	return model.num_vertices;
}

uint16_t Model_Loader_3ds::read_polygons(std::istream& infile, Model& model)
{
	assert(infile);
	infile.read((char*)&model.num_polygons, 2);

	model.polygons = new glm::uvec3[model.num_polygons];
	uint16_t face_flags; // We ignore these
	for(uint16_t i = 0; i < model.num_polygons; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			model.polygons[i][j] = 0;
			infile.read((char*)&model.polygons[i][j], sizeof(uint16_t));
		}
		infile.read((char*)&face_flags, sizeof(uint16_t));
	}

	return model.num_polygons;
}

uint16_t Model_Loader_3ds::read_texcoords(std::istream& infile, Model& model)
{
	assert(infile);
	uint16_t num_texcoords;
	infile.read((char*)&num_texcoords, sizeof(uint16_t));

	model.texcoords = new glm::vec2[num_texcoords];
	for(uint16_t i = 0; i < model.num_vertices; ++i)
		for(int j = 0; j < 2; ++j)
			infile.read((char*)&model.texcoords[i][j], sizeof(float));

	return num_texcoords;
}

void Model_Loader_3ds::Chunk::read_header(std::istream& stream)
{
	assert(stream);
	chunk_beginning = stream.tellg();
	stream.read((char*) &id, 2);
	stream.read((char*) &length, 4);
}

void Model_Loader_3ds::Chunk::skip_body(std::istream& stream)
{
	assert(stream);
	assert(length >= 6);
	stream.seekg(length + chunk_beginning);
}

Model Model_Loader_3ds::read_model(const std::string& filename)
{
	std::ifstream infile(filename.c_str(), std::ios_base::binary | std::ios_base::in);	
	assert(infile);

	Model model;

	while(true)
	{
		Chunk chunk;
		chunk.read_header(infile);
/*		std::cout << std::hex << "Found id " << chunk.id << '\n';
		std::cout << "And length " << std::dec << chunk.length << '\n';*/
		if(!infile)
			break;
		switch(chunk.id)
		{
			case MAIN_CHUNK:
//				std::cout << "Found main chunk!\n";
				break;
			case EDITOR_CHUNK:
//				std::cout << "Found 3d_editor chunk!\n";
				break;
			case OBJECT_BLOCK:
//				std::cout << "Found object block!\n";
				// Reading object name
				std::cout << "Reading object name\n";
				model.name = read_model_name(infile);
				std::cout << "Read object with name " << model.name << '\n';
				break;
			case TRIANGULAR_MESH:
//				std::cout << "Found triangular mesh!\n";
				break;
			case VERTICES_LIST:
				std::cout << "Reading vertices\n";
//				std::cout << "Found vertices list!\n";
				std::cout << "Read " << read_vertices(infile, model) << " vertices.\n";
				break;
			case FACES_DESCRIPTION:
				std::cout << "Reading polygons\n";
//				std::cout << "Found FACES_DESCRIPTION!\n";
				std::cout << "Read " << read_polygons(infile, model) << " polygons.\n";
				break;
			case MAPPING_COORDINATES_LIST:
				std::cout << "Reading texture coordinates\n";
//				std::cout << "Found texture coordinates!\n";
				std::cout << "Read " << read_texcoords(infile, model) << " texture coordinates.\n";
				chunk.skip_body(infile);
				break;
			default:
//				std::cout << "Skipping\n";
				chunk.skip_body(infile);
		}
	}

	std::cout << "Model has " << model.num_vertices << " vertices and " << model.num_polygons << " polygons.\n";

	assert(model.polygons);
	assert(model.vertices);

	std::cout << "Texture coordinates ... ";
	if(model.texcoords)
	{
		std::cout << " found!\n";
		model.Init_Texture("camouflage.jpg");
	}
	else
		std::cout << " not found!\n";

	model.drawMode = GL_TRIANGLES;
	model.InitVBOs();

	return model;
}
