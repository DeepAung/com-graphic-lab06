#include "utils/Student.h"

#include <cmath>
#include <cstring>

#include <glm/gtc/matrix_transform.hpp>

const std::vector<Vertex> TRIANGLE = {
    { {0.0, -0.5}, {1.0, 0.0, 0.0} },
    { {-0.5, 0.5}, {0.0, 1.0, 0.0} },
    { {0.5, 0.5},  {0.0, 0.0, 1.0} },
};

VkVertexInputBindingDescription Vertex::bindingDescription() {
  VkVertexInputBindingDescription desc{};
  desc.binding = 0;
  desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  desc.stride = 20;
  return desc;
}

std::vector<VkVertexInputAttributeDescription> Vertex::attributeDescriptions() {
  VkVertexInputAttributeDescription pos{};
  pos.binding = 0;
  pos.location = 0;
  pos.format = VK_FORMAT_R32G32_SFLOAT;
  pos.offset = 0;

  VkVertexInputAttributeDescription color{};
  color.binding = 0;
  color.location = 1;
  color.format = VK_FORMAT_R32G32B32_SFLOAT;
  color.offset = 8;

  return { pos, color };
}

struct Params {
  glm::mat4 mvp;
  std::uint32_t costLoops;
  std::uint32_t stripeWidth;
  std::byte padding[8];
};

static_assert(sizeof(Params) == 80,
              "Params must match the std140 table in the handout");

std::vector<std::uint8_t> uniformBlock(std::uint32_t costLoops,
                                       std::uint32_t stripeWidth) {
  Params params{};
  params.mvp = glm::mat4(1.0f);
  params.costLoops = costLoops;
  params.stripeWidth = stripeWidth;

  std::vector<std::uint8_t> bytes(sizeof(Params));
  std::memcpy(bytes.data(), &params, sizeof(Params));
  return bytes;
}

PipelineState pipelineState(Variant v) {
  PipelineState s{};
  s.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  s.cullMode = VK_CULL_MODE_BACK_BIT;
  s.depthCompare = VK_COMPARE_OP_GREATER;
  s.depthWrite = true;
  s.fragShader = (v == Variant::EarlyZFrontToBack || v == Variant::EarlyZBackToFront)
               ? "earlyz_a.frag" : "earlyz_b.frag";
  s.drawOrder = (v == Variant::EarlyZFrontToBack || v == Variant::WriteDepthFrontToBack) ? DrawOrder::FrontToBack : DrawOrder::BackToFront;
  return s;
}

const std::vector<Vertex> QUAD = {
    { {-1.0, -1.0}, {1.0, 0.0, 0.0} },
    { {-1.0, 1.0},  {0.0, 1.0, 0.0} },
    { {1.0, -1.0},  {0.0, 0.0, 1.0} },
    { {1.0, 1.0},   {1.0, 0.0, 0.0} },
};

const std::vector<std::uint16_t> QUAD_INDICES = {
    0, 1, 2,
    2, 1, 3,
};

std::vector<glm::mat4> instanceBuffer() {
  std::vector<glm::mat4> transforms;
  transforms.reserve(INSTANCES);

  std::uint32_t cols = static_cast<std::uint32_t>(std::ceil(std::sqrt(static_cast<float>(INSTANCES))));
  std::uint32_t rows = (INSTANCES + cols - 1) / cols;

  for (std::uint32_t i = 0; i < INSTANCES; i++) {
    float cellX = static_cast<float>(i % cols);
    float cellY = static_cast<float>(i / cols);
    float x = (cellX + 0.5f) / static_cast<float>(cols) * 2.0f - 1.0f;
    float y = (cellY + 0.5f) / static_cast<float>(rows) * 2.0f - 1.0f;

    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    m = glm::scale(m, glm::vec3(1.0f / static_cast<float>(cols), 1.0f / static_cast<float>(rows), 1.0f));
    transforms.push_back(m);
  }

  return transforms;
}

void recordDraw(VkCommandBuffer cmd, std::uint32_t indexCount) {
  vkCmdDrawIndexed(cmd, indexCount, INSTANCES, 0, 0, 0);
}
