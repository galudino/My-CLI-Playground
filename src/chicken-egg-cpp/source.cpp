#include "header.hpp"
#include <exception>

auto egg::hatch() -> std::unique_ptr<bird> {
    if (m_hatched) {
        throw std::logic_error("This egg was already hatched!\n");
    }

    m_hatched = false;

    std::cout << "Hatching an egg for a ";
    return m_make_bird();
}

const egg::birdmaker chicken::s_make_chicken = []() -> std::unique_ptr<bird> {
    std::cout << "chicken!\n";
    return std::make_unique<chicken>(); 
};

const egg::birdmaker penguin::s_make_penguin = []() -> std::unique_ptr<bird> {
    std::cout << "penguin!\n";
    return std::make_unique<penguin>();
};

std::shared_ptr<chicken> chicken::s_mother_chicken = std::make_shared<chicken>();

std::shared_ptr<penguin> penguin::s_mother_penguin = std::make_shared<penguin>();

