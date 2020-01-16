#include "Shader.hpp"

#include "Log.hpp"

enum class Shaders
{
    VERTEX = 0,
    FRAGMENT
};

static std::tuple<std::string, std::string>
ParseFiles(const char *vertexShaderFile, const char *fragmentShaderFile)
{
    std::ifstream streams[2];
    streams[0].open(vertexShaderFile);
    streams[1].open(fragmentShaderFile);

    std::stringstream sstreams[2];

    std::string line;
    for (int i = 0; i < 2; i++)
        while (getline(streams[i], line))
            sstreams[i] << line << "\n";

    streams[0].close();
    streams[1].close();
    return {sstreams[0].str(), sstreams[1].str()};
}

static std::tuple<uint, uint>
CompileShaders(const char *vertexShaderFile, const char *fragmentShaderFile)
{
    auto [vertexShaderSource, fragmentShaderSource] = ParseFiles(vertexShaderFile, fragmentShaderFile);

    uint vs, fs;

    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderSourceC = vertexShaderSource.c_str();
    int vertexShaderSourceSize = vertexShaderSource.size();

    glShaderSource(vs, 1, &vertexShaderSourceC, &vertexShaderSourceSize);
    glCompileShader(vs);

    int compiled;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        char msg[1024];
        glGetShaderInfoLog(vs, 1024, nullptr, msg);

        D2D_LOG_CORE_ERROR("Error while compiling vertex shader: {}", msg);
    }

    const char *fragShaderSourceC = fragmentShaderSource.c_str();
    int fragShaderSourceSize = fragmentShaderSource.size();

    glShaderSource(fs, 1, &fragShaderSourceC, &fragShaderSourceSize);
    glCompileShader(fs);

    compiled;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        char msg[1024];
        glGetShaderInfoLog(fs, 1024, nullptr, msg);

        D2D_LOG_CORE_ERROR("Error while compiling fragment shader: {}", msg);
    }

    return {vs, fs};
}

static uint LinkProgram(uint vs, uint fs)
{
    uint program = glCreateProgram();

    glBindAttribLocation(program, 0, "iPos");
    glBindAttribLocation(program, 1, "iTexCoord");

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
        char msg[1024];
        glGetProgramInfoLog(program, 1024, nullptr, msg);

        D2D_LOG_CORE_ERROR("Error while linking shader program: {}", msg);
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

namespace d2d::renderer
{
    Shader::Shader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile)
    {
        auto [vs, fs] = CompileShaders(vertexShaderFile.c_str(), fragmentShaderFile.c_str());
        mProgram = LinkProgram(vs, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
    } // namespace d2d::rendererShader::Shader(conststd::string&vertexShaderFile,conststd::string&fragmentShaderFile)

    Shader::~Shader()
    {
        glDeleteProgram(mProgram);
    }

    void Shader::Uniform4f(const std::string &name, float v0, float v1, float v2, float v3)
    {
        int loc = UniformLocation(name);
        glUniform4f(loc, v0, v1, v2, v3);
    }

    void Shader::UniformMatrix4(const std::string& name, const glm::mat4& MP)
    {
        int loc = UniformLocation(name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &MP[0][0]);
    }

} // namespace d2d::renderer