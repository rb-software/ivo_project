#include "Log.h"
#include "Graphic_Engine.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION

#include <tiny_gltf.h>

using namespace tinygltf;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    DBG_PRINTF(INFO, " key event ...");

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/** Linux graphic engine implementation. */
Linux_Graphic_Engine::Linux_Graphic_Engine()
{
    DBG_PRINTF(INFO, "constructor() ...");
}

Linux_Graphic_Engine::~Linux_Graphic_Engine()
{
    DBG_PRINTF(INFO, "desctructor() ...");
}

void PrintNodes(const tinygltf::Scene &scene)
{
  for (size_t i = 0; i < scene.nodes.size(); i++)
  {
      DBG_PRINTF(INFO, "node.name() : " + std::to_string(scene.nodes[i]));
  }
}

void DrawMesh(tinygltf::Model &model, const tinygltf::Mesh &mesh)
{
    for (size_t i = 0; i < mesh.primitives.size(); i++)
    {
        const tinygltf::Primitive &primitive = mesh.primitives[i];

        DBG_PRINTF(INFO, "Mesh primitives " + std::to_string(mesh.primitives.size()) + " " + std::to_string(i));

        if (primitive.indices < 0)
        {
            DBG_PRINTF(INFO, " zero indices");
            return;
        }

        std::map<std::string, int>::const_iterator it(primitive.attributes.begin());
        std::map<std::string, int>::const_iterator itEnd(primitive.attributes.end());

        for (; it != itEnd; it++)
        {
            assert(it->second >= 0);

            const tinygltf::Accessor &accessor = model.accessors[it->second];
            int size = 1;
            
            if (accessor.type == TINYGLTF_TYPE_SCALAR)
            {
                DBG_PRINTF(INFO, "TINYGLTF_TYPE_SCALAR");
                size = 1;
            }
            else if (accessor.type == TINYGLTF_TYPE_VEC2)
            {
                DBG_PRINTF(INFO, "TINYGLTF_TYPE_VEC2");
                size = 2;
            }
            else if (accessor.type == TINYGLTF_TYPE_VEC3)
            {
                DBG_PRINTF(INFO, "TINYGLTF_TYPE_VEC3");
                size = 3;
            }
            else if (accessor.type == TINYGLTF_TYPE_VEC4)
            {
                DBG_PRINTF(INFO, "TINYGLTF_TYPE_VEC4");
                size = 4;
            }
            else
            {
                assert(0);
            }
        }

        /** Missing code  !!! **/

        const tinygltf::Accessor &indexAccessor = model.accessors[primitive.indices];
        int mode = -1;
        if (primitive.mode == TINYGLTF_MODE_TRIANGLES)
        {
            DBG_PRINTF(INFO, "GL_TRIANGLES");
            mode = GL_TRIANGLES;
        }
        else if (primitive.mode == TINYGLTF_MODE_TRIANGLE_STRIP)
        {
            DBG_PRINTF(INFO, "TINYGLTF_MODE_TRIANGLE_STRIP");
            mode = GL_TRIANGLE_STRIP;
        }
        else if (primitive.mode == TINYGLTF_MODE_TRIANGLE_FAN)
        {
            DBG_PRINTF(INFO, "TINYGLTF_MODE_TRIANGLE_FAN");
            mode = GL_TRIANGLE_FAN;
        }
        else if (primitive.mode == TINYGLTF_MODE_POINTS)
        {
            DBG_PRINTF(INFO, "TINYGLTF_MODE_POINTS");
            mode = GL_POINTS;
        }
        else if (primitive.mode == TINYGLTF_MODE_LINE)
        {
            DBG_PRINTF(INFO, "TINYGLTF_MODE_LINE");
            mode = GL_LINES;
        }
        else if (primitive.mode == TINYGLTF_MODE_LINE_LOOP)
        {
            DBG_PRINTF(INFO, "TINYGLTF_MODE_LINE_LOOP");
            mode = GL_LINE_LOOP;
        }
        else
        {
            assert(0);
        }

        glDrawElements(mode, indexAccessor.count, indexAccessor.componentType,
                        BUFFER_OFFSET(indexAccessor.byteOffset));

        DBG_PRINTF(INFO, " indexAccessor.count: " + std::to_string(indexAccessor.count));
        DBG_PRINTF(INFO, " indexAccessor.componentType: " + std::to_string(indexAccessor.componentType));        

        {
            std::map<std::string, int>::const_iterator it(
                primitive.attributes.begin());
            std::map<std::string, int>::const_iterator itEnd(
                primitive.attributes.end());

            for (; it != itEnd; it++)
            {
                if ((it->first.compare("POSITION") == 0) ||
                    (it->first.compare("NORMAL") == 0) ||
                    (it->first.compare("TEXCOORD_0") == 0))
                {
                    DBG_PRINTF(INFO, "Compare ok");

                    /*
                    if (gGLProgramState.attribs[it->first] >= 0)
                    {
                        glDisableVertexAttribArray(gGLProgramState.attribs[it->first]);
                    }
                    */
                }
            }
        }
    }
}

void DrawNode(tinygltf::Model &model, const tinygltf::Node &node)
{
    glPushMatrix();

    if (node.matrix.size() == 16)
    {
        DBG_PRINTF(INFO, "size(16)");
        glMultMatrixd(node.matrix.data());
    } 
    else
    {
        if (node.scale.size() == 3)
        {
            DBG_PRINTF(INFO, "Scale: size(3): ");
            glScaled(node.scale[0], node.scale[1], node.scale[2]);
        }

        if (node.rotation.size() == 4)
        {
            DBG_PRINTF(INFO, "Rotation: size(4) ("    + std::to_string(node.rotation[0]) + ","
                                                                + std::to_string(node.rotation[1]) + ","
                                                                + std::to_string(node.rotation[2]) + ","
                                                                + std::to_string(node.rotation[3]) + ")");

            glRotated(node.rotation[0], node.rotation[1], node.rotation[2],
                        node.rotation[3]);
        }

        if (node.translation.size() == 3)
        {

            DBG_PRINTF(INFO, "Translation: size (3) ("    + std::to_string(node.translation[0]) + ","
                                                                + std::to_string(node.translation[1]) + ","
                                                                + std::to_string(node.translation[2]) + ")");

            glTranslated(node.translation[0], node.translation[1],
                        node.translation[2]);
        }
    }

    if (node.mesh > -1)
    {
        DBG_PRINTF(INFO, "-> mesh_node > -1");
        assert(node.mesh < model.meshes.size());
        DrawMesh(model, model.meshes[node.mesh]);
    }

    // Draw child nodes.
    for (size_t i = 0; i < node.children.size(); i++)
    {
        DBG_PRINTF(INFO, "-> childern : " + std::to_string(i));
        assert(node.children[i] < model.nodes.size());
        DrawNode(model, model.nodes[node.children[i]]);
    }

    glPopMatrix();

    DBG_PRINTF(INFO, "\n");
}

void ModelOperate(tinygltf::Model &model)
{
    int scene_to_display = model.defaultScene > -1 ? model.defaultScene : 0;

    const tinygltf::Scene &scene = model.scenes[scene_to_display];

    for (size_t i = 0; i < scene.nodes.size(); i++)
    {
        DBG_PRINTF(INFO, " For node: " + std::to_string(i));

        DrawNode(model, model.nodes[scene.nodes[i]]);
    }
}

bool LoadShader(GLenum shaderType,  // GL_VERTEX_SHADER or GL_FRAGMENT_SHADER(or
                                    // maybe GL_COMPUTE_SHADER)
                GLuint &shader, const char *shaderSourceFilename)
{
    GLint val = 0;

    // free old shader/program
    if (shader != 0)
    {
        glDeleteShader(shader);
    }

    std::vector<GLchar> srcbuf;
    FILE *fp = fopen(shaderSourceFilename, "rb");

    if (!fp)
    {
        fprintf(stderr, "failed to load shader: %s\n", shaderSourceFilename);
        return false;
    }
    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    rewind(fp);
    srcbuf.resize(len + 1);
    len = fread(&srcbuf.at(0), 1, len, fp);
    srcbuf[len] = 0;
    fclose(fp);

    const GLchar *srcs[1];
    srcs[0] = &srcbuf.at(0);

    DBG_PRINTF(INFO, "RADEK");

    shader = glCreateShader(shaderType);
    DBG_PRINTF(INFO, "DZIADEK");
    glShaderSource(shader, 1, srcs, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &val);


    if (val != GL_TRUE) {
        char log[4096];
        GLsizei msglen;
        glGetShaderInfoLog(shader, 4096, &msglen, log);
        printf("%s\n", log);
        // assert(val == GL_TRUE && "failed to compile shader");
        printf("ERR: Failed to load or compile shader [ %s ]\n",
            shaderSourceFilename);
        return false;
    }

    printf("Load shader [ %s ] OK\n", shaderSourceFilename);
    return true;
}

#define CAM_Z (3.0f)
float eye[3], lookat[3], up[3];

bool LinkShader(GLuint &prog, GLuint &vertShader, GLuint &fragShader) {
  GLint val = 0;

  if (prog != 0) {
    glDeleteProgram(prog);
  }

  prog = glCreateProgram();

  glAttachShader(prog, vertShader);
  glAttachShader(prog, fragShader);
  glLinkProgram(prog);

  glGetProgramiv(prog, GL_LINK_STATUS, &val);
  assert(val == GL_TRUE && "failed to link shader");

  printf("Link shader OK\n");

  return true;
}

bool Linux_Graphic_Engine::init() const 
{
    eye[0] = 0.0f;
    eye[1] = 0.0f;
    eye[2] = CAM_Z;

    lookat[0] = 0.0f;
    lookat[1] = 0.0f;
    lookat[2] = 0.0f;

    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;

    Model model;
    TinyGLTF loader;
    std::string err, warn;

    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    std::string location(buffer);

    DBG_PRINTF(INFO, "Location: " + location);

    if ( true == loader.LoadBinaryFromFile(&model, &err, &warn, location + "/../data/city_model.glb") )
    {
        DBG_PRINTF(INFO, "Model loading - OK");
        DBG_PRINTF(INFO, "of meshes = " + std::to_string(model.meshes.size()));
        DBG_PRINTF(INFO, "Printing nodes: ");

        PrintNodes(model.scenes[model.defaultScene > -1 ? model.defaultScene :0]);
    }
    else
    {
        DBG_PRINTF(ERROR, "Model loading - FAIL");

        if ( !err.empty() )
            DBG_PRINTF(ERROR, err );

        if ( !warn.empty() )
            DBG_PRINTF(WARNING, warn );

        return false;
    } 

    if ( !glfwInit() ) // opengl windows API handler
    {
        DBG_PRINTF(INFO, "Failed to initialize glwf.");
        return false;
    }

    GLFWwindow* window = nullptr;

    if ( nullptr == (window = glfwCreateWindow(800, 640,
                                    "ivo_project-test-window",
                                    NULL, NULL)) )
    {
        glfwTerminate();
        return false;
    }


    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glViewport(0, 0, 800, 600);

    if ( GLEW_OK != glewInit() ) // side tools for open gl
    {
        DBG_PRINTF(INFO, "Failed to initialize glew.");
        return false;
    }

    GLuint vertId = 0, fragId = 0, progId = 0;

    const char *shader_frag_filename = "shader.frag";
    const char *shader_vert_filename = "shader.vert";

    DBG_PRINTF(INFO, "Shaders allocation GL_VERTEX_SHADER ...");

    if ( false == LoadShader(GL_VERTEX_SHADER, vertId, shader_vert_filename) )
    {
        DBG_PRINTF(ERROR, "Function failed !");
        return false;
    }

    DBG_PRINTF(INFO, "Shaders allocation GL_FRAGMENT_SHADER ...");

    if ( false == LoadShader(GL_FRAGMENT_SHADER, fragId, shader_frag_filename) )
    {
        DBG_PRINTF(ERROR, "Function failed !");
        return false;
    }

    if ( false == LinkShader(progId, vertId, fragId) )
    {
        return false;
    }

    DBG_PRINTF(INFO, "Init shader done ...");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], up[0],
              up[1], up[2]);
        
        glBegin(GL_TRIANGLES);

        glColor3f( 1.0f, 0.0f, 0.0f);
        glVertex2f( -0.5f, -0.5f );

        glColor3f( 0.0f, 1.0f, 0.0f);
        glVertex2f( 0.0f,  0.5f );

        glColor3f( 0.0f, 0.0f, 1.0f);
        glVertex2f( 0.5f, -0.5f );

        //ModelOperate(model);
        sleep(1);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
}

ssize_t Linux_Graphic_Engine::ignite() const 
{
    return 0;
}

bool Linux_Graphic_Engine::close() const 
{
    return false;
}

/** Windows graphic engine implementation. */
Windows_Graphic_Engine::Windows_Graphic_Engine()
{
    DBG_PRINTF(INFO, "constructor() ...");
}

Windows_Graphic_Engine::~Windows_Graphic_Engine()
{
    DBG_PRINTF(INFO, "desctructor() ...");
}

bool Windows_Graphic_Engine::init() const
{
    DBG_PRINTF(WARNING, "empty impl !");
    return false;
}

ssize_t Windows_Graphic_Engine::ignite() const 
{
    DBG_PRINTF(WARNING, "empty impl !");
    return 0;
}

bool Windows_Graphic_Engine::close() const
{
    DBG_PRINTF(WARNING, "empty impl !");
    return false;
}