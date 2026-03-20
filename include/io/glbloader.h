#pragma once


// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tiny_gltf.h"
#include <expected>

std::expected<tinygltf::Model, std::string> load_GLB(std::string gltffile);

struct TextureDescriptor {
  unsigned char* pixels;
  int width, height, channels;
};

std::expected<TextureDescriptor, std::string> extract_texture(tinygltf::Model& model);
