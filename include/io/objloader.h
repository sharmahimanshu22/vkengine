#pragma once

#include <vector>
#include "vertex.h"
#include "vertex.h"


  
struct DataForGPU {
std::vector<Vertex> vertices;
std::vector<uint32_t> indices;

};

DataForGPU loadModel(const std::string model_path);

DataForGPU loadSTL(const std::string filename);

DataForGPU loadDelaunay();
