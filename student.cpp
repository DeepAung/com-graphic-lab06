#include "utils/Student.h"

#include <cstring>

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
  s.cullMode = VK_CULL_MODE_FRONT_BIT;
  s.depthCompare = VK_COMPARE_OP_GREATER;
  s.depthWrite = (v == WriteDepthFrontToBack || v == WriteDepthBackToFront);
  s.fragShader = s.depthWrite ? "earlyz_b.frag" : "earlyz_a.frag";
  s.drawOrder = (v == EarlyZFrontToBack || v == WriteDepthFrontToBack) ? DrawOrder::FrontToBack : DrawOrder::BackToFront;
  return s;
}

const std::vector<Vertex> QUAD = {
    // TODO(TASK 4a): four corners. Check values are in Part V of the handout.
};

const std::vector<std::uint16_t> QUAD_INDICES = {
    // TODO(TASK 4b): six indices, two triangles, both wound like TASK 1a.
};

std::vector<glm::mat4> instanceBuffer() {
  // TODO(TASK 5a): INSTANCES transforms, glm::translate and glm::scale.
  return {};
}

void recordDraw(VkCommandBuffer cmd, std::uint32_t indexCount) {
  // TODO(TASK 5b): one vkCmdDrawIndexed, with an instance count.
}
