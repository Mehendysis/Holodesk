#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

using namespace std;

int GenerateShaders() 
{
    cout << "Generate shaders" << endl;
    string vertShader = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 modelViewMatrix;
    uniform mat4 projectionMatrix;

    void main()
    {
        gl_Position = projectionMatrix * modelViewMatrix * vec4(aPos, 1.0);
    }
)";

    string fragShader = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // Change the color to red
    }
 )";

    if (!filesystem::exists("shaders")) 
    {
        filesystem::create_directory("shaders");
    }

    ofstream vertFile("shaders/cube.vert");
    vertFile << vertShader;
    vertFile.close();

    ofstream fragFile("shaders/cube.frag");
    fragFile << fragShader;
    fragFile.close();

    return 0;
}