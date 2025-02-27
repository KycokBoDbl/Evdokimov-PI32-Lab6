﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <limits>
using namespace std;

enum class Classes {
    SWORDSMAN,
    ARCHER,
    SPEARMAN,
    THIEF,
    HAMMERER,
    SHIELDBEARER
};


std::string getClassName(Classes cls) {
    switch (cls) {
    case Classes::SWORDSMAN: return "Мечник";
    case Classes::ARCHER: return "Лучник";
    case Classes::SPEARMAN: return "Копейщик";
    case Classes::THIEF: return "Вор";
    case Classes::HAMMERER: return "Молотоборец";
    default: return "Щитоносец";
    }
}

class Equipment {
protected:
    std::string name;
    int cost;
public:
    Equipment(const std::string& name, int cost) : name(name), cost(cost) {}
    const std::string& getName() const { return name; }
    int getCost() const { return cost; }
    void setName(const std::string& name) { this->name = name; }
    void setCost(int cost) { this->cost = cost; }
    virtual void showInfo() const = 0;
};


class Weapon : public Equipment {
private:
    Classes weaponClass;
    int level;
    double damage;
public:
    Weapon(const std::string& name, Classes weaponClass, int level, int cost, double damage)
        : Equipment(name, cost), weaponClass(weaponClass), level(level), damage(damage) {}
    Classes getWeaponClass() const { return weaponClass; }
    void setWeaponClass(Classes weaponClass) { this->weaponClass = weaponClass; }
    int getLevel() const { return level; }
    void setLevel(int level) { this->level = level; }
    double getDamage() const { return damage; }
    void setDamage(double damage) { this->damage = damage; }
    void showInfo() const override {
        std::cout << "Оружие: " << getName()
            << ", Класс: " << getClassName(weaponClass)
            << ", Уровень: " << level
            << ", Урон: " << damage
            << ", Стоимость: " << getCost() << std::endl;
    }
};

class Armor : public Equipment {
private:
    Classes armorClass;
    int level;
    double defense;
public:
    Armor(const std::string& name, Classes armorClass, int level, int cost, double defense)
        : Equipment(name, cost), armorClass(armorClass), level(level), defense(defense) {}
    Classes getArmorClass() const { return armorClass; }
    void setArmorClass(Classes armorClass) { this->armorClass = armorClass; }
    int getLevel() const { return level; }
    void setLevel(int level) { this->level = level; }
    double getDefense() const { return defense; }
    void setDefense(double defense) { this->defense = defense; }
    void showInfo() const override {
        std::cout << "Броня: " << getName()
            << ", Класс: " << getClassName(armorClass)
            << ", Уровень: " << level
            << ", Защита: " << defense
            << ", Стоимость: " << getCost() << std::endl;
    }
};

class Item : public Equipment {
private:
    std::string description;
public:
    Item(const std::string& name, const std::string& description, int cost)
        : Equipment(name, cost), description(description) {}
    std::string getDescription() const { return description; }
    void setDescription(const std::string& description) { this->description = description; }
    void showInfo() const override {
        std::cout << "Предмет: " << getName()
            << ", Описание: " << description
            << ", Стоимость: " << getCost() << std::endl;
    }
};

class Inventory {
private:
    int slots;
    std::vector<Equipment*> equipments;
public:
    Inventory() : slots(0) {}
    void addWeapon(Weapon* weapon) {
        if (slots < 100) {
            equipments.push_back(weapon);
            slots++;
        }
        else { std::cout << "Инвентарь полон" << std::endl; }
    }
    void addArmor(Armor* armor) {
        if (slots < 100) {
            equipments.push_back(armor);
            slots++;
        }
        else { std::cout << "Инвентарь полон" << std::endl; }
    }
    void addItem(Item* item) {
        if (slots < 100) {
            equipments.push_back(item);
            slots++;
        }
        else { std::cout << "Инвентарь полон" << std::endl; }
    }
    void showInventory() const {
        std::cout << "Инвентарь:" << std::endl;
        for (const auto& equipment : equipments) {
            equipment->showInfo();
        }
    }
    ~Inventory() {
        for (auto& equipment : equipments) {
            delete equipment;
        }
    }
};
class Character {
private:
    std::string username;
    Classes characterClass;
    int level;
    double health;
    double damage;
    double armor;
    double speed;
public:
    Character(const std::string& username, Classes characterClass, int level, double health, double damage, double armor, double speed)
        : username(username), characterClass(characterClass), level(level), health(health), damage(damage), armor(armor), speed(speed) {}
    void showStats() const {
        std::cout << "Имя: " << username << std::endl;
        std::cout << "Класс: " << getClassName(characterClass) << std::endl;
        std::cout << "Уровень: " << level << std::endl;
        std::cout << "Здоровье: " << health << std::endl;
        std::cout << "Урон: " << damage << std::endl;
        std::cout << "Броня: " << armor << std::endl;
        std::cout << "Скорость: " << speed << std::endl;
    }
    std::string getUsername() const { return username; }
    void setUsername(const std::string& username) { this->username = username; }
    Classes getCharacterClass() const { return characterClass; }
    void setCharacterClass(Classes characterClass) { this->characterClass = characterClass; }
    int getLevel() const { return level; }
    void setLevel(int level) { this->level = level; }
    double getHealth() const { return health; }
    void setHealth(double health) { this->health = health; }
    double getDamage() const { return damage; }
    void setDamage(double damage) { this->damage = damage; }
    double getArmor() const { return armor; }
    void setArmor(double armor) { this->armor = armor; }
    double getSpeed() const { return speed; }
    void setSpeed(double speed) { this->speed = speed; }
    // объявление дружественной функции
    friend void levelUp(Character& character);
};

//дружественная функция
void levelUp(Character& character) {
    int levels = -1;
    while (levels < 0 || character.getLevel() + levels > 100) {
        try {
            std::cout << "Введите количество повышенных уровней: ";
            std::cin >> levels;
            if (levels < 0 || character.getLevel() + levels > 100) {
                throw std::invalid_argument("Недопустимое количество уровней.");
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Произошла ошибка ввода. Пожалуйста, попробуйте снова." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (levels > 0) {
        std::cout << "Распределите полученные очки навыков:" << std::endl;
        for (int i = 0; i < levels; ++i) {
            int choice = 0;
            bool valid = false;
            while (!valid) {
                try {
                    std::cout << "Оставшиеся очки: " << (levels - i) << std::endl;
                    std::cout << "1) Здоровье\n2) Урон\n3) Броня\n4) Скорость" << std::endl;
                    std::cin >> choice;
                    if (choice < 1 || choice > 4) {
                        throw std::invalid_argument("Недопустимый выбор. Пожалуйста, выберите от 1 до 4.");
                    }
                    valid = true;
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                catch (...) {
                    std::cerr << "Произошла ошибка ввода. Пожалуйста, попробуйте снова." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            switch (choice) {
            case 1:
                character.health += 5;
                break;
            case 2:
                character.damage++;
                break;
            case 3:
                character.armor++;
                break;
            case 4:
                character.speed++;
                break;
            }
        }
        character.level += levels;
    }
}
class Player {
private:
    Character* character;
    Inventory* inventory;
public:
    static int playerCount; // Статическое поле для подсчета игроков
    static std::vector<Player*> allPlayers; // Статическое поле для хранения всех игроков
    // Конструктор, создающий нового игрока
    Player(Character* character) : character(character), inventory(new Inventory()) {
        playerCount++;
        allPlayers.push_back(this);
        setInventory();
    }
    ~Player() {
        delete inventory;
    }
    // Создание стартового инвентаря
    void setInventory() {
        Weapon* weapon;
        Armor* armor;
        Item* item;
        item = new Item("Зелье лечения", "Восстанавливает 30 здоровья", 10);
        inventory->addItem(item);
        item = new Item("Телепортирующее зеркало", "Позволяет вернуться в стартовый город", 30);
        inventory->addItem(item);
        Classes characterClass = character->getCharacterClass();
        switch (characterClass) {
        case Classes::SWORDSMAN:
            weapon = new Weapon("Меч новичка", Classes::SWORDSMAN, 1, 20, 4);
            inventory->addWeapon(weapon);
            armor = new Armor("Броня мечника", Classes::SWORDSMAN, 1, 15, 3);
            inventory->addArmor(armor);
            break;
        case Classes::ARCHER:
            weapon = new Weapon("Лук новичка", Classes::ARCHER, 1, 20, 3);
            inventory->addWeapon(weapon);
            armor = new Armor("Доспехи лучника", Classes::ARCHER, 1, 15, 2);
            inventory->addArmor(armor);
            break;
        case Classes::SPEARMAN:
            weapon = new Weapon("Копьё новичка", Classes::SPEARMAN, 1, 25, 5);
            inventory->addWeapon(weapon);
            armor = new Armor("Броня копейщика", Classes::SPEARMAN, 1, 18, 3);
            inventory->addArmor(armor);
            break;
        case Classes::THIEF:
            weapon = new Weapon("Кинжалы новичка", Classes::THIEF, 1, 15, 3);
            inventory->addWeapon(weapon);
            armor = new Armor("Лёгкая броня вора", Classes::THIEF, 1, 10, 1);
            inventory->addArmor(armor);
            break;
        case Classes::HAMMERER:
            weapon = new Weapon("Молот новичка", Classes::HAMMERER, 1, 30, 6);
            inventory->addWeapon(weapon);
            armor = new Armor("Тяжёлая броня молотоборца", Classes::HAMMERER, 1, 20, 4);
            inventory->addArmor(armor);
            break;
        default:
            weapon = new Weapon("Щит новичка", Classes::SHIELDBEARER, 1, 20, 2);
            inventory->addWeapon(weapon);
            armor = new Armor("Броня щитоносца", Classes::SHIELDBEARER, 1, 17, 5);
            inventory->addArmor(armor);
            break;
        }
    }
    // Вывод характеристик игрока
    void showStats() const { character->showStats(); }
    // Геттеры и сеттеры
    Character* getCharacter() const { return character; }
    void setCharacter(Character* character) { this->character = character; }
    Inventory* getInventory() const { return inventory; }
    void setInventory(Inventory* inventory) { this->inventory = inventory; }
    // Статические методы для работы с информацией об игроках
    static int getPlayerCount() { return playerCount; }
    static std::vector<Player*> getAllPlayers() { return allPlayers; }
};

int Player::playerCount = 0;
std::vector<Player*> Player::allPlayers;

class CharacterFactory {
public:
    static Character* createCharacter(bool isFirstCharacter) {
        std::string name;
        int classChoice;
        int health;
        int damage;
        int armor;
        int speed;
        std::cout << "Введите имя: ";
        if (!isFirstCharacter) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::getline(std::cin, name);

        bool validChoice = false;
        while (!validChoice) {
            try {
                std::cout << "Выберите класс персонажа:\n1) Мечник\n2) Лучник\n3) Копейщик\n4) Вор\n5) Молотоборец\n6) Щитоносец" << std::endl;
                std::cin >> classChoice;
                if (classChoice < 1 || classChoice > 6) {
                    throw std::invalid_argument("Недопустимый выбор класса. Пожалуйста, выберите от 1 до 6.");
                }
                validChoice = true;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
            catch (...) {
                std::cerr << "Произошла ошибка ввода. Пожалуйста, попробуйте снова." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        classChoice--;
        switch (classChoice) {
        case 0: health = 100; damage = 4; armor = 5; speed = 4; break;
        case 1: health = 80; damage = 7; armor = 1; speed = 7; break;
        case 2: health = 100; damage = 6; armor = 3; speed = 4; break;
        case 3: health = 90; damage = 3; armor = 2; speed = 9; break;
        case 4: health = 110; damage = 6; armor = 5; speed = 2; break;
        default: health = 120; damage = 2; armor = 8; speed = 3; break;
        }
        return new Character(name, static_cast<Classes>(classChoice), 1, health, damage, armor, speed);
    }
};

size_t getClassesCount() {
    return static_cast<size_t>(Classes::SHIELDBEARER) + 1;
}

int main() {
    setlocale(LC_ALL, "Rus");
    Player* currentPlayer = nullptr;
    std::vector<Player*> allPlayers; // Хранит всех созданных игроков
    bool isFirstCharacter = true;

    std::vector<std::vector<Player*>> playersByClass(getClassesCount()); // Двумерный массив игроков по классам

    while (true) {
        // Создание первого игрока
        if (!currentPlayer) {
            Character* character = CharacterFactory::createCharacter(isFirstCharacter);
            currentPlayer = new Player(character);
            allPlayers.push_back(currentPlayer);
            playersByClass[static_cast<size_t>(character->getCharacterClass())].push_back(currentPlayer); // Добавляем игрока в двумерный массив
            isFirstCharacter = false;
        }
        int choice;
        std::cout << "Список действий:" << std::endl;
        std::cout << "1) Посмотреть инвентарь" << std::endl;
        std::cout << "2) Посмотреть характеристики" << std::endl;
        std::cout << "3) Создать нового персонажа" << std::endl;
        std::cout << "4) Повысить уровень персонажу" << std::endl;
        std::cout << "5) Посмотреть количество созданных игроков" << std::endl;
        std::cout << "6) Просмотреть всех игроков" << std::endl;
        std::cout << "7) Просмотреть персонажей по классам" << std::endl;
        std::cout << "8) Завершение работы" << std::endl;
        bool validChoice = false;
        while (!validChoice) {
            try {
                std::cin >> choice;
                if (choice < 1 || choice > 8) {
                    throw std::invalid_argument("Недопустимый выбор. Пожалуйста, выберите от 1 до 8.");
                }
                validChoice = true;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
            catch (...) {
                std::cerr << "Произошла ошибка ввода. Пожалуйста, попробуйте снова." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        switch (choice) {
        case 1:
            currentPlayer->getInventory()->showInventory();
            break;
        case 2:
            currentPlayer->showStats();
            break;
        case 3: {
            Character* newCharacter = CharacterFactory::createCharacter(false);
            Player* newPlayer = new Player(newCharacter);
            allPlayers.push_back(newPlayer);
            playersByClass[static_cast<size_t>(newCharacter->getCharacterClass())].push_back(newPlayer); // Добавляем игрока в двумерный массив
            currentPlayer = newPlayer;
            std::cout << "Новый персонаж создан" << std::endl;
            break;
        }
        case 4:
            levelUp(*currentPlayer->getCharacter());
            break;
        case 5:
            std::cout << "Количество созданных игроков: " << Player::getPlayerCount() << std::endl;
            break;
        case 6: {
            for (Player* p : allPlayers) {
                p->showStats();
            }
            break;
        }
        case 7: {
            std::cout << "Выберите класс персонажа для просмотра:" << std::endl;
            for (size_t i = 0; i < getClassesCount(); ++i) {
                std::cout << (i + 1) << ") " << getClassName(static_cast<Classes>(i)) << std::endl;
            }
            int classChoice;
            std::cin >> classChoice;
            classChoice--;
            if (classChoice >= 0 && classChoice < static_cast<int>(getClassesCount())) {
                for (Player* p : playersByClass[classChoice]) {
                    p->showStats();
                }
            }
            else {
                std::cerr << "Недопустимый выбор класса." << std::endl;
            }
            break;
        }
        default:
            for (Player* p : allPlayers) {
                delete p; // Удаляем всех созданных игроков
            }
            for (auto& classRow : playersByClass) {
                classRow.clear(); // Очищаем строки двумерного массива
            }
            return 0; // Завершаем программу
        }
    }
}