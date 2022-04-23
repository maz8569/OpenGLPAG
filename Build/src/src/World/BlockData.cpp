#include "World/BlockData.h"
#include <fstream>

using namespace GameEngine;

GameEngine::BlockData::BlockData(const std::string& fileName)
{
    std::ifstream inFile("res/blocks/" + fileName + ".block");

    if (!inFile.is_open())
    {
        throw std::runtime_error("Unable to open block file: " + fileName + "!");
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line == "TexTop")
        {
            int x, y;
            inFile >> x >> y;
            m_data.texTopCoord = { x, y };
        }
        else if (line == "TexSide")
        {
            int x, y;
            inFile >> x >> y;
            m_data.texSideCoord = { x, y };
        }
        else if (line == "TexBottom")
        {
            int x, y;
            inFile >> x >> y;
            m_data.texBottomCoord = { x, y };
        }
        else if (line == "TexAll")
        {
            int x, y;
            inFile >> x >> y;
            m_data.texTopCoord = { x, y };
            m_data.texSideCoord = { x, y };
            m_data.texBottomCoord = { x, y };
        }
    }
}

const BlockDataHolder& GameEngine::BlockData::getBlockData() const
{
    // TODO: вставьте здесь оператор return
    return m_data;
}
