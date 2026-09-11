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
  // TODO(TASK 3a): match the winding you chose in TASK 1a
  // TODO(TASK 3b): cull back faces
  // TODO(TASK 3c): depth compare, using Lab 05's reversed-Z convention
  // TODO(TASK 3d): should this pipeline write depth?
  // TODO(TASK 3e): "earlyz_a.frag" or "earlyz_b.frag", chosen from v
  // TODO(TASK 3f): DrawOrder::FrontToBack or ::BackToFront, chosen from v
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
