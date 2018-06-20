#include "constants.h"
namespace dynsolver {
namespace constants {

const std::string kDefaultFontFilePath("/home/ezra/Documents/projects/hubbard_research/resources/fonts/OpenSans-Regular.ttf");

namespace gl {
namespace text_renderer_program {
const std::string kVertexShaderFilePath("/home/ezra/Documents/projects/hubbard_research/resources/gl/text_renderer.vert");
const std::string kFragmentShaderFilePath("/home/ezra/Documents/projects/hubbard_research/resources/gl/text_renderer.frag");
const std::string kTransformationUniform("transformation");
const std::string kTextColorUniform("textColor");
const std::string kSamplerUniform("sampler");
const GLuint kVertexPositionAttribute(0);
const GLuint kTexturePositionAttribute(1);
}
}

namespace app {
const std::string kProjectPath("/home/ezra/Documents/projects/hubbard_research");
const int kGLMajorVersion(4);
const int kGLMinorVersion(3);
} // namespace app

namespace vertex_shader {
const std::string kCode
(
 "#version 430 core\n"
 "layout (location = 0) in vec2 pos;\n"
 "uniform mat4 transformation;\n"
 "void main() {\n"
 "  gl_Position = transformation * vec4(pos, 0.0, 1.0);\n"
 "}\n"
);

const GLuint kPositionAttribute(0);
const GLuint kVertexBinding(0);
const std::string kTransformationUniform("transformation");

} // namespace vertex_shader

namespace fragment_shader {
const std::string kCode
(
 "#version 430 core\n"
 "uniform vec3 in_color;\n"
 "out vec4 out_color;\n"
 "void main() {\n"
 "  out_color = vec4(in_color, 1.0);\n"
 "}\n"
 );
const std::string kColorUniform("in_color");
} // namespace fragment_shader

} // namespace constants
} // namespace dynsolver
