/*********************************************
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 

**************************************************/

#ifdef DRAGO2D_ENGINE_IMPLEMENTATION
#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"

#endif

/*************************************************/
// Declarations

#ifndef DRAGO2D_ENGINE_HPP
#define DRAGO2D_ENGINE_HPP

#if defined(_WIN32)
    #define D2D_WINDOWS
#else
    #define D2D_UNIX
    #if defined(__APPLE__)
        #define D2D_APPLE
    #else
        #define D2D_LINUX
    #endif // __APPLE__
#endif // _WIN32

#define D2D_EXIT_CODE_GLFW_INIT_FAILED 1
#define D2D_EXIT_CODE_GLAD_INIT_FAILED 2
#define D2D_EXIT_CODE_SHADER_CONSTRUCTION_FAILED 3

#include "glfw/glfw3.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace d2d {

int init() noexcept;
void terminate() noexcept;
struct window_t
{
private:
    GLFWwindow* m_window;
	glm::mat4 m_projection;
    uint32_t m_width, m_height;
    const char* m_title;

public:

    window_t(uint32_t width, uint32_t height, const char* title) noexcept;

    inline uint32_t get_width() const noexcept { return this->m_width; }
    inline uint32_t get_height() const noexcept { return this->m_height; }

#ifdef DRAGO2D_ENGINE_IMPLEMENTATION
    inline operator GLFWwindow*() const noexcept
	{
        return m_window;
    }

	inline void set_projection(int w, int h) noexcept
	{
		m_projection = glm::ortho(0.0f, (float)w, (float)h, 0.0f, -1.0f, 10.0f);
		glfwSetWindowUserPointer(m_window, &m_projection);
	}

#endif

};

struct color_t
{
    double r, g, b, a;
};

namespace window {

    void set_onclick_function(window_t& window,
        void(*onclick_function)(window_t&, int, int, int)) noexcept;
    
    void set_cursor_enter_function(window_t& window, 
        void(*cursor_enter_function)(window_t&, int)) noexcept;
    
    void set_scroll_function(window_t& window, 
        void(*scroll_function)(window_t&, double, double)) noexcept;

    void set_key_function(window_t& window,
        void(*key_function)(window_t&, int, int, int, int)) noexcept;
    
    void set_background(const color_t&& color) noexcept;
    void set_background(const color_t& color) noexcept;

    void set_main_window(const window_t& window) noexcept;

    bool should_close(const window_t& window) noexcept;

    void poll_events(const window_t& window) noexcept;

    int get_key(window_t& window, int key) noexcept;

    void get_cursor_pos(const window_t& window, double& x, double& y) noexcept;
}

namespace draw {
    // Translates to coordinates x, y
    void translate(float x, float y) noexcept;

    void line(float x1, float y1, float x2, float y2, const color_t& c);

    // Draw filled rect at center coordinates x, y
    void fill_rect(float x, float y,
        float width, float height, const color_t& c, float rotation) noexcept;
    
    void draw_rect(float x, float y,
        float width, float height, const color_t& c, float rotation) noexcept;
    
    void draw_circle(float x, float y, float r, const color_t& c) noexcept;
    
    void fill_circle(float x, float y, float r, const color_t& c) noexcept;
}

}

#define D2D_LOG_INFO(...)      spdlog::info(__VA_ARGS__)
#define D2D_LOG_WARN(...)      spdlog::warn(__VA_ARGS__)
#define D2D_LOG_ERROR(...)     spdlog::error(__VA_ARGS__)
#define D2D_LOG_CRITICAL(...)  spdlog::critical( __VA_ARGS__)

#endif // DRAGO2D_ENGINE_HPP

/*************************************************/
// Engine implementation

#ifdef DRAGO2D_ENGINE_IMPLEMENTATION

#include <optional>

/*************************************************/
// Logging system

namespace d2d::log
{
auto core_logger = spdlog::stdout_color_mt("d2d-core-logger");
}

#define D2D_LOG_CORE_INFO(...) d2d::log::core_logger->info(__VA_ARGS__)
#define D2D_LOG_CORE_WARN(...) d2d::log::core_logger->warn(__VA_ARGS__)
#define D2D_LOG_CORE_ERROR(...) d2d::log::core_logger->error(__VA_ARGS__)
#define D2D_LOG_CORE_CRITICAL(...) d2d::log::core_logger->critical(__VA_ARGS__)

/*************************************************/
// Shader source codes so they do not have to be loaded from a file,
// further increasing self sustainability of library

static const char *d2d_draw_vertex_shader_source = R"HERE(
#version 330 core
layout (location = 0) in vec3 i_pos;

uniform mat4 u_mp;

void main()
{
	gl_Position = u_mp * vec4(i_pos, 1);
}
)HERE";

static const char *d2d_draw_fragment_shader_source = R"HERE(
#version 330 core
out vec4 frag_color;
  
uniform vec4 u_color;

void main()
{
    frag_color = u_color;
}   
)HERE";

/*************************************************/
// Shader programs

static unsigned int d2d_draw_shader_program;

/*************************************************/
// Matrices

static glm::mat4* d2d_draw_projection;
static glm::mat4 d2d_draw_translation;

/*************************************************/
// Functions to initialize shader programs

static bool d2d_draw_check_shader_compilation_status(unsigned int &shader, unsigned int shader_type) noexcept
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512]; // 512 is max size for info log
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        D2D_LOG_CORE_ERROR("{} shader compilation failed.\nLog: {}",
                           shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", info_log);
        return false;
    }
    return true;
}

static std::optional<unsigned int> d2d_draw_create_shader(const char *shader_src, unsigned int shader_type) noexcept
{
    unsigned int shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);

    if (d2d_draw_check_shader_compilation_status(shader, shader_type))
        return shader;
    return {};
}

static std::optional<unsigned int> d2d_draw_create_shader_program(const char *vs_source, const char *fs_source) noexcept
{
    auto vertex_shader = d2d_draw_create_shader(vs_source, GL_VERTEX_SHADER);
    if (!vertex_shader)
        return {};
    auto fragment_shader = d2d_draw_create_shader(fs_source, GL_FRAGMENT_SHADER);
    if (!fragment_shader)
        return {};
    auto shader_program = glCreateProgram();

    glAttachShader(shader_program, *vertex_shader);
    glAttachShader(shader_program, *fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(*vertex_shader);
    glDeleteShader(*fragment_shader);

    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        D2D_LOG_CORE_ERROR("Failed to compile shader program\nLog: {}", info_log);
        glDeleteShader(*vertex_shader);
        return {};
    }

    return shader_program;
}

/*************************************************/
// global vao, vbo and ebo

typedef uint uint32_t;

static uint d2d_draw_vao, d2d_draw_vbo;

/*************************************************/
// Initialization system

#include <signal.h>
#include "glfw/glfw3.h"

static bool d2d_initialized_glad = false;

namespace d2d
{

void terminate() noexcept
{
    D2D_LOG_CORE_INFO("Terminating Drago2D");
    glfwTerminate();
    D2D_LOG_CORE_INFO("Terminated Drago2D");
}

int init() noexcept
{
    D2D_LOG_CORE_INFO("Initializing Drago2D");
    D2D_LOG_CORE_INFO("Creating user logger");
    auto user_logger = spdlog::stdout_color_mt("d2d-user-logger");
    spdlog::set_default_logger(user_logger);

    if (!glfwInit())
    {
        D2D_LOG_CORE_CRITICAL("glfw initialization failed");
        return D2D_EXIT_CODE_GLFW_INIT_FAILED;
    }

    D2D_LOG_CORE_INFO("Adding signals");
    signal(SIGINT, [](int){ terminate(); });
    D2D_LOG_CORE_INFO("Added signals");

    D2D_LOG_CORE_INFO("Initialized Drago2D");
    return 0;
}

} // namespace d2d

/*************************************************/
// Window system

static void window_resize_fun(d2d::window_t& win, int w, int h)
{
    glViewport(0, 0, w, h);
	win.set_projection(w, h);
}

namespace d2d
{

window_t::window_t(uint32_t width, uint32_t height, const char *title) noexcept
    : m_window(glfwCreateWindow(width, height, title, nullptr, nullptr)),
	m_projection(glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 10.0f)),
	m_width(width), m_height(height), m_title(title)
	  
{
    D2D_LOG_CORE_INFO("Creating window {}", m_title);
    glfwSetWindowSizeCallback(m_window, (GLFWwindowsizefun)((void*)window_resize_fun));
	glfwSetWindowUserPointer(m_window, &m_projection);
    if (!d2d_initialized_glad)
    {
        D2D_LOG_CORE_INFO("{} is first window therefore, inititalizing glad", m_title);
        glfwMakeContextCurrent(m_window);
        if (!gladLoadGL(glfwGetProcAddress))
        {
            D2D_LOG_CORE_CRITICAL("glad initialization failed");
            std::exit(D2D_EXIT_CODE_GLAD_INIT_FAILED);
        }

        d2d_initialized_glad = true;
        D2D_LOG_CORE_INFO("Initialized glad");

        D2D_LOG_CORE_INFO("Constructing shaders");
        auto shader = d2d_draw_create_shader_program(d2d_draw_vertex_shader_source,
                                                     d2d_draw_fragment_shader_source);
        if (!shader)
        {
            D2D_LOG_CORE_CRITICAL("Due to previous errors program will terminate");
            std::exit(D2D_EXIT_CODE_SHADER_CONSTRUCTION_FAILED);
        }
        d2d_draw_shader_program = *shader;

        glGenVertexArrays(1, &d2d_draw_vao);
        glGenBuffers(1, &d2d_draw_vbo);
    }
}

namespace window
{
void set_onclick_function(window_t &window,
                          void (*onclick_function)(window_t &, int, int, int)) noexcept
{
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)((void *)onclick_function));
}

void set_cursor_enter_function(window_t &window,
                               void (*cursor_enter_function)(window_t &, int)) noexcept
{
    glfwSetCursorEnterCallback(window, (GLFWcursorenterfun)((void *)cursor_enter_function));
}

void set_scroll_function(window_t &window,
                         void (*scroll_function)(window_t &, double, double)) noexcept
{
    glfwSetScrollCallback(window, (GLFWscrollfun)((void *)scroll_function));
}

void set_key_function(window_t &window,
                      void (*key_function)(window_t &, int, int, int, int)) noexcept
{
    glfwSetKeyCallback(window, (GLFWkeyfun)((void *)key_function));
}

void set_background(const color_t &&color) noexcept
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, color.a);
}

void set_background(const color_t &color) noexcept
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void set_main_window(const window_t &window) noexcept
{
    glfwMakeContextCurrent(window);
}

bool should_close(const window_t &window) noexcept
{
    return glfwWindowShouldClose(window);
}

void poll_events(const window_t &window) noexcept
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int get_key(window_t &window, int key) noexcept
{
    return glfwGetKey(window, key);
}

void get_cursor_pos(const window_t &window, double &x, double &y) noexcept
{
    glfwGetCursorPos(window, &x, &y);
}

} // namespace window
} // namespace d2d

/*************************************************/
// Drawing system

static void d2d_draw_bind_vao()
{
    glBindVertexArray(d2d_draw_vao);
}

static void d2d_draw_bind_vbo()
{
    glBindBuffer(GL_ARRAY_BUFFER, d2d_draw_vbo);
}

static void d2d_draw_upload_data_to_vbo(void *data, size_t data_size)
{
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STREAM_DRAW);
}

static void d2d_draw_vertex_attrib_array(uint position, uint size,
                                         GLenum type, bool normalize, size_t stride, void *offset)
{
    glVertexAttribPointer(position, size, type, normalize, stride, offset);
    glEnableVertexAttribArray(position);
}

static void d2d_draw_set_projection(glm::mat4** proj)
{
	*proj = static_cast<glm::mat4*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
}

static void d2d_draw_setup_draw(float* verts, size_t verts_size, size_t vert_count, 
    float rotation, GLenum draw_type, const d2d::color_t& c)
{
    d2d_draw_bind_vao();
    d2d_draw_bind_vbo();

    d2d_draw_upload_data_to_vbo(verts, verts_size);

    d2d_draw_vertex_attrib_array(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), nullptr);

    glUseProgram(d2d_draw_shader_program);
    auto color_loc = glGetUniformLocation(d2d_draw_shader_program, "u_color");
    glUniform4f(color_loc, c.r, c.g, c.b, c.a);

	d2d_draw_set_projection(&d2d_draw_projection);
	
	glm::mat4 model = glm::rotate(d2d_draw_translation, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	auto mp = *d2d_draw_projection * model;

	auto mp_loc = glGetUniformLocation(d2d_draw_shader_program, "u_mp");
	glUniformMatrix4fv(mp_loc, 1, GL_FALSE, &mp[0][0]);

    d2d_draw_bind_vao();
    glDrawArrays(draw_type, 0, vert_count);
}

namespace d2d::draw
{

// Translates to coordinates x, y
void translate(float x, float y) noexcept
{
    d2d_draw_translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
}

// Draws filled rectangle from center
void fill_rect(float x, float y,
    float width, float height, const color_t& c, float rotation) noexcept
{
	translate(x, y);

    float vertices[] = {
        -width / 2.0f, -height / 2.0f, 0.0f,
         width / 2.0f, -height / 2.0f, 0.0f,
		 width / 2.0f,  height / 2.0f, 0.0f,
		-width / 2.0f, -height / 2.0f, 0.0f,
		 width / 2.0f,  height / 2.0f, 0.0f,
		-width / 2.0f,  height / 2.0f, 0.0f
    };

    d2d_draw_setup_draw(vertices, sizeof vertices, 6, rotation, GL_TRIANGLES, c);
}

void line(float x1, float y1, float x2, float y2, const color_t& c)
{
    translate(0, 0);
    float vertices[] = {
        x1, y1, 0,
        x2, y2, 0,
    };
    d2d_draw_setup_draw(vertices, sizeof vertices, 2, 0, GL_LINES, c);
}

void draw_rect(float x, float y,
    float width, float height, const color_t& c, float rotation) noexcept
{
    translate(x, y);

    float vertices[] = {
        -width / 2.0f, -height / 2.0f, 0.0f, 
         width / 2.0f, -height / 2.0f, 0.0f,
         width / 2.0f, -height / 2.0f, 0.0f,
         width / 2.0f,  height / 2.0f, 0.0f,
         width / 2.0f,  height / 2.0f, 0.0f,
        -width / 2.0f,  height / 2.0f, 0.0f,
        -width / 2.0f,  height / 2.0f, 0.0f,
        -width / 2.0f, -height / 2.0f, 0.0f, 
    };

    d2d_draw_setup_draw(vertices, sizeof vertices, 8, rotation, GL_LINES, c);
}

} // namespace d2d::draw

/*************************************************/
// Cleanup

#undef D2D_LOG_CORE_INFO
#undef D2D_LOG_CORE_WARN
#undef D2D_LOG_CORE_ERROR
#undef D2D_LOG_CORE_CRITICAL

#endif // DRAGO2D_ENGINE_IMPLEMENTATION