
// Define these only in *one* .cc file.

#include "io/glbloader.h"
#include <stb_image.h>
//#include <stb_image_write.h>

std::expected<tinygltf::Model, std::string> load_GLB(std::string filename) {

  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;
  //std::string filename = "./resources/DiffuseTransmissionPlant.glb";

  //bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
  bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename); // for binary glTF(.glb)
  if (ret) {
    return model;
  }

  return std::unexpected(err);

  /*
  const auto &mat = model.materials[0];
  int texIndex = mat.pbrMetallicRoughness.baseColorTexture.index;
  const auto &tex = model.textures[texIndex];

  int imgIndex = tex.source;
  const auto &img = model.images[imgIndex];
  */

  if (!warn.empty()) {
    printf("Warn: %s\n", warn.c_str());
  }

  if (!err.empty()) {
    printf("Err: %s\n", err.c_str());
  }

  if (!ret) {
    printf("Failed to parse glTF: %s\n", filename.c_str());
  }
}




std::expected<TextureDescriptor, std::string> extract_texture(tinygltf::Model& model) {
  const auto &mat = model.materials[0];
  int texIndex = mat.pbrMetallicRoughness.baseColorTexture.index;
  const auto &tex = model.textures[texIndex];

  int imgIndex = tex.source;
  const auto &img = model.images[imgIndex];

  int width, height, channels;

  unsigned char* pixels = stbi_load_from_memory(
    img.image.data(),
    img.image.size(),
    &width,
    &height,
    &channels,
    STBI_rgb_alpha   // force 4 channels for Vulkan
  );

  return TextureDescriptor(pixels, width,height, channels);

  if (!pixels) {
    return std::unexpected("stbi_load_from_memory error");
  }
}


