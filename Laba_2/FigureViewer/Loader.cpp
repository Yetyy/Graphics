#include "Loader.h"

Loader::Loader(const std::string& path) :
    m_path(path)
{
}

Loader::~Loader()
{
}

std::vector<Vector2D> Loader::vertices() const
{
    return m_vertices;
}

std::vector<int> Loader::indices() const
{
    return m_indices;
}

bool Loader::isLoad()
{
    return !m_vertices.empty() && !m_indices.empty();
}

void Loader::load()
{
    std::ifstream in(m_path);
    if (!in)
        return;

    std::string line;
    std::string word;
    std::vector<std::string> words;
    while (std::getline(in, line))
    {
        std::stringstream sstr(line);
        while (sstr >> word)
            words.push_back(word);

        if (!words.empty())
        {
            if (words[0] == "v" && words.size() == 3)
            {
                double x = std::stod(words[1]);
                double y = std::stod(words[2]);
                m_vertices.push_back(Vector2D(x, y));
            }
            else if (words[0] == "f" && words.size() > 1)
            {
                for (int i = 1; i < words.size(); i++)
                {
                    int index = std::stoi(words[i]);
                    m_indices.push_back(index);
                }
            }
        }
        word = line = "";
        words.clear();
    }
}
