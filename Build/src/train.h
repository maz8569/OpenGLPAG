#pragma once
#include "SceneGraph.h"
#include "Shader.h"

float cube[] = {
    // positions          // normals           
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
};

class Locomotive {
private:
	std::shared_ptr<SceneNode> locomotive;
    unsigned int floor_VAO, floor_VBO, floor_buffer;
    glm::mat4* floor_modelMatrices;
    unsigned int wheels_VBO, wheels_VAO, wheels_buffer;
    glm::mat4* wheels_modelMatrices;
    float wheel[712];

    float smoke1_x = -3.0f;
    float smoke1_y = 2.8f;
    float smoke2_x = -2.3f;
    float smoke2_y = 3.1f;

    int walls_count = 3;
    int wheels_count = 7;

    float y_rot = 0.0f;
	std::shared_ptr<SceneNode> floor = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> roof = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> tube1 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> tube2 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> frontPart = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> wheel1 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> wheel2 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> wheel3 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> wheel4 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> wheel5 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> wheel6 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> piston1 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> piston1orbit = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> piston2 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> piston2orbit = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> smoke1 = std::make_shared<SceneNode>();
	std::shared_ptr<SceneNode> smoke2 = std::make_shared<SceneNode>();

public:
	Locomotive(std::shared_ptr<SceneNode> parent);
    ~Locomotive();
    void add_cabin();
    void initiate_walls();
    void initiate_wheels();
    void add_wheels();
    void initiate_smoke();
    void move_smoke();
    void change_cabin_buf();
    void change_wheels_buf();
    void draw_wheels(std::shared_ptr<Shader> ourShader);
    void draw_smoke(std::shared_ptr<Shader> ourShader);
    void draw_refr(std::shared_ptr<Shader> ourShader);
    void draw_ref(std::shared_ptr<Shader> ourShader);
	void draw(std::shared_ptr<Shader> ourShader, std::shared_ptr<Shader> instancedShader, std::shared_ptr<Shader> refractShader, std::shared_ptr<Shader> reflectShader)
	{
        //draw_cabin(ourShader);
        draw_cabin(instancedShader);
        draw_wheels(instancedShader);
        draw_smoke(ourShader);
        draw_refr(refractShader);
        draw_ref(reflectShader);
	}
    void draw_cabin(std::shared_ptr<Shader> ourShader)
    {
        ourShader->use();
        
        glBindVertexArray(floor_VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, walls_count);
        glBindVertexArray(0);

    }

    std::vector<float> drawCylinder(int szczegol)
    {
        vector<float> vertices;
        float xPos = 0, yPos = 0;
        float steps = 4 * szczegol;
        float height = 0.5f;
        float radius = 0.15f;

        float newUx = 0;
        float newUy = 0;
        const double PI = 3.1415926535897932384626433832795;
        const double TAU = 2 * PI;
        float newX = 0, newY = 0;
        float angle = TAU / steps;
        float prevX = 0, prevY = -radius;
        float prevUx = prevX/radius;
        float prevUy = -prevY/radius;
        float meanUx = 0;
        float meanUy = 0;
        for (int i = 0; i <= steps; i++)
        {
            newUx = sin(angle * i);
            newUy = cos(angle * i);
            newX = radius * newUx;
            newY = -radius * newUy;
            for (int j = 0; j < 3; j++)
            {
                vertices.push_back(0);
            }
            meanUx = -(prevUx + newUx) * 0.5;
            meanUy = -(prevUy + newUy) * 0.5;
            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(1);

            vertices.push_back(prevX);
            vertices.push_back(prevY);
            vertices.push_back(0);

            vertices.push_back(meanUx);
            vertices.push_back(meanUy);
            vertices.push_back(1);

            vertices.push_back(newX);
            vertices.push_back(newY);
            vertices.push_back(0);
            
            vertices.push_back(meanUx);
            vertices.push_back(meanUy);
            vertices.push_back(1);

            vertices.push_back(prevX);
            vertices.push_back(prevY);
            vertices.push_back(height);

            vertices.push_back(meanUx);
            vertices.push_back(meanUy);
            vertices.push_back(-1);

            vertices.push_back(newX);
            vertices.push_back(newY);
            vertices.push_back(height);

            vertices.push_back(meanUx);
            vertices.push_back(meanUy);
            vertices.push_back(-1);

            for (int j = 0; j < 2; j++)
            {
                vertices.push_back(0);
            }

            vertices.push_back(height);

            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(-1);

            prevX = newX;
            prevY = newY;

            prevUx = newUx;
            prevUy = newUy;
        }

        return vertices;
    }

    void update_cabin_matr();
    void update_wheels_matr();
    void update_matrices();
    void update(std::shared_ptr<SceneNode> parent);
};

void Locomotive::draw_wheels(std::shared_ptr<Shader> ourShader) {
    ourShader->use();

    glBindVertexArray(wheels_VAO);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 102, wheels_count);
    glBindVertexArray(0);

}

void Locomotive::draw_smoke(std::shared_ptr<Shader> ourShader)
{
    ourShader->use();
    ourShader->setMat4("model", smoke1->get_transform().m_world_matrix);
    glBindVertexArray(floor_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
     
    ourShader->setMat4("model", smoke2->get_transform().m_world_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);


}

inline void Locomotive::draw_refr(std::shared_ptr<Shader> ourShader)
{
    ourShader->use();

    ourShader->setMat4("model", tube1->get_transform().m_world_matrix);
    glBindVertexArray(floor_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    ourShader->setMat4("model", tube2->get_transform().m_world_matrix);
    glBindVertexArray(floor_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

inline void Locomotive::draw_ref(std::shared_ptr<Shader> ourShader)
{
    ourShader->use();

    ourShader->setMat4("model", roof->get_transform().m_world_matrix);
    glBindVertexArray(floor_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Locomotive::update_cabin_matr()
{
    floor_modelMatrices[0] = floor->get_transform().m_world_matrix;
    floor_modelMatrices[1] = piston1->get_transform().m_world_matrix;
    floor_modelMatrices[2] = piston2->get_transform().m_world_matrix;
}

void Locomotive::update_wheels_matr()
{
    wheels_modelMatrices[0] = frontPart->get_transform().m_world_matrix;
    wheels_modelMatrices[1] = wheel1->get_transform().m_world_matrix;
    wheels_modelMatrices[2] = wheel2->get_transform().m_world_matrix;
    wheels_modelMatrices[3] = wheel3->get_transform().m_world_matrix;
    wheels_modelMatrices[4] = wheel4->get_transform().m_world_matrix;
    wheels_modelMatrices[5] = wheel5->get_transform().m_world_matrix;
    wheels_modelMatrices[6] = wheel6->get_transform().m_world_matrix;
}

void Locomotive::update_matrices()
{
    update_cabin_matr();
    update_wheels_matr();
    change_cabin_buf();
    change_wheels_buf();
}

void Locomotive::update(std::shared_ptr<SceneNode> parent)
{
    if (smoke1_x < 0.5f) {
        smoke1_x += 0.02f;
    }
    else {
        smoke1_y = 2.8f;
        smoke1_x = -3.2f;
    }

    if (smoke2_x < 0.5f) {
        smoke2_x += 0.02f;
    }
    else {
        smoke2_y = 2.8f;
        smoke2_x = -3.2f;
    }

    if (smoke1_y < 6.5f) {
        smoke1_y += 0.02f;
    }
    else {
        smoke1_y = 2.8f;
        smoke1_x = -3.2f;
    }

    if (smoke2_y < 6.5f) {
        smoke2_y += 0.02f;
    }
    else {
        smoke2_y = 2.8f;
        smoke2_x = -3.2f;

    }
    
    if (y_rot < 360) {
        y_rot += 2.0f;
    }
    else
    {
        y_rot = 0.0f;
    }

    piston1orbit->set_local_rotation({0.0f, 0.0f, -y_rot});
    piston1->set_local_rotation({0.0f, 0.0f, y_rot});
    piston2orbit->set_local_rotation({0.0f, 0.0f, -y_rot});
    piston2->set_local_rotation({0.0f, 0.0f, y_rot});

    locomotive->update(parent->get_transform(), true);
    move_smoke();
    update_matrices();
}

Locomotive::Locomotive(std::shared_ptr<SceneNode> parent) : locomotive(parent) {
    floor_modelMatrices = new glm::mat4[walls_count];
    wheels_modelMatrices = new glm::mat4[wheels_count];

    std::vector<float> torus = drawCylinder(4);
    std::copy(torus.begin(), torus.end(), wheel);
    locomotive->add_child(floor);
    locomotive->add_child(roof);
    locomotive->add_child(tube1);
    locomotive->add_child(tube2);
    locomotive->add_child(frontPart);
    locomotive->add_child(wheel1);
    locomotive->add_child(wheel2);
    locomotive->add_child(wheel3);
    locomotive->add_child(wheel4);
    locomotive->add_child(wheel5);
    locomotive->add_child(wheel6);
    locomotive->add_child(piston1orbit);
    piston1orbit->add_child(piston1);
    locomotive->add_child(piston2orbit);
    piston2orbit->add_child(piston2);
    locomotive->add_child(smoke1);
    locomotive->add_child(smoke2);
    initiate_walls();
    initiate_wheels();
    initiate_smoke();
    locomotive->update(locomotive->get_transform(), true);
    add_cabin();
    add_wheels();
};

Locomotive::~Locomotive()
{
    glDeleteBuffers(1, &floor_VAO);
    glDeleteBuffers(1, &floor_VBO);
    glDeleteBuffers(1, &floor_buffer);
    glDeleteBuffers(1, &wheels_VAO);
    glDeleteBuffers(1, &wheels_VBO);
    glDeleteBuffers(1, &wheels_buffer);

    delete floor_modelMatrices;
    floor_modelMatrices = NULL;
    delete floor_modelMatrices;
    floor_modelMatrices = NULL;
}

void Locomotive::add_cabin()
{
    update_cabin_matr();
    
    glGenVertexArrays(1, &floor_VAO);
    glGenBuffers(1, &floor_VBO);

    glBindVertexArray(floor_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, floor_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &floor_buffer);
    change_cabin_buf();

}

void Locomotive::initiate_walls()
{
    floor->set_local_position({ 0.0f, 0.7f, 0.0f });
    floor->set_local_scale({ 2.0f, 2.5f, 2.0f });

    roof->set_local_position({ 0.0f, 1.5f, 0.0f });
    roof->set_local_scale({ 2.2f, 0.5f, 2.2f });

    tube1->set_local_position({ -3.5f, 1.8, 0.0f });
    tube1->set_local_scale({ 0.3f, 0.6f, 0.3f });

    tube2->set_local_position({ -3.5f, 2.1f, 0.0f });
    tube2->set_local_scale({ 0.5f, 0.2f, 0.5f });

    piston1orbit->set_local_position({-3.0f, -0.8f, 1.1f});
    piston1->set_local_position({ 0.0f, -0.6f, 0.0f });
    piston1->set_local_scale({2.6f, 0.1f, 0.1f});

    piston2orbit->set_local_position({ -3.0f, -0.8f, -1.1f });
    piston2->set_local_position({ 0.0f, -0.6f, 0.0f });
    piston2->set_local_scale({ 2.6f, 0.1f, 0.1f });
}

void Locomotive::initiate_wheels()
{
    frontPart->set_local_position({-1.0f, 0.5f, 0.0f});
    frontPart->set_local_rotation({0.0f, 90.0f, 0.0f});
    frontPart->set_local_scale({ 7.0f, 7.0f, 7.0f });

    wheel1->set_local_position({0.0f, -0.8f, 1.0f});
    wheel1->set_local_scale({ 5.0f, 5.0f, 0.2f });

    wheel2->set_local_position({ 0.0f, -0.8f, -1.1f });
    wheel2->set_local_scale({ 5.0f, 5.0f, 0.2f });

    wheel3->set_local_position({ -2.0f, -0.8f, 1.0f });
    wheel3->set_local_scale({ 5.0f, 5.0f, 0.2f });

    wheel4->set_local_position({ -2.0f, -0.8f, -1.0f });
    wheel4->set_local_scale({ 5.0f, 5.0f, 0.2f });

    wheel5->set_local_position({ -3.7f, -0.8f, 1.0f });
    wheel5->set_local_scale({ 5.0f, 5.0f, 0.2f });

    wheel6->set_local_position({ -3.7f, -0.8f, -1.0f });
    wheel6->set_local_scale({ 5.0f, 5.0f, 0.2f });

}

void Locomotive::add_wheels()
{
    update_wheels_matr();

    glGenVertexArrays(1, &wheels_VAO);
    glGenBuffers(1, &wheels_VBO);

    glBindVertexArray(wheels_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, wheels_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wheel), wheel, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &wheels_buffer);
    change_wheels_buf();
}

void Locomotive::initiate_smoke()
{
    move_smoke();
    smoke1->set_local_scale({ 0.6f, 0.6f, 0.6f });
    smoke2->set_local_scale({ 0.48f, 0.48f, 0.48f });
}

void Locomotive::move_smoke()
{
    smoke1->set_local_position({ smoke1_x, smoke1_y, 0.0f });
    smoke2->set_local_position({ smoke2_x, smoke2_y, 0.0f });

}

void Locomotive::change_cabin_buf()
{
    glBindVertexArray(floor_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, floor_buffer);
    glBufferData(GL_ARRAY_BUFFER, walls_count * sizeof(glm::mat4), &floor_modelMatrices[0], GL_STATIC_DRAW);

    std::size_t vec4Size = sizeof(glm::vec4);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);

}

void Locomotive::change_wheels_buf()
{
    glBindVertexArray(wheels_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, wheels_buffer);
    glBufferData(GL_ARRAY_BUFFER, wheels_count * sizeof(glm::mat4), &wheels_modelMatrices[0], GL_STATIC_DRAW);

    std::size_t vec4Size = sizeof(glm::vec4);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}

