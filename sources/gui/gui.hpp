#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "physical_object/physical_object.hpp"
#include "player/player.hpp"
#include "storage/instrument.hpp"
#include "world/cell.hpp"

#include "inventory_cell_button.hpp"
#include "my_texture.hpp"
#include "rectangle_button.hpp"

class Gui
{
public:
    static Gui* getInstance();

    void handleEvents();

    sf::Vector2f getMousePosition();

    sf::Vector2f getWindowCentre();

    sf::Vector2f getWindowSize();

private:
    Gui();

    void handlePlayerActions();

    void handleInventoryActions();

    sf::Event m_event;

    sf::RenderWindow m_window;

    class Graphic
    {
        friend void Gui::handleInventoryActions();

        friend void Gui::handlePlayerActions();

        friend class PlayerInterface;

    public:
        Graphic();

        void loadTextures();

        void display();

        void zoom(float s);

        //////////////////

        float getScope();

        sf::Vector2f getPlayerPositionInWindow();

        sf::IntRect getCharTextureRect(char ch);
        const sf::Texture* getCharTexturePtr();

        class InventoryInterface
        {
            friend void Gui::handleInventoryActions();

        public:
            enum class Status
            {
                CLOSE = 0,
                OPEN  = 1
            };

            static void loadTexture();

            void create();

            void drawFullInventory();

            void drawUsingCells();

            void raiseShift();

            void lowerShift();

            void update();

            const StorageCell& getUsingStorageCellRef();

            Status getStatus();

        private:
            class IntermediateBuffer
            {
            public:
                enum class StorageType
                {
                    HAND      = 0,
                    INVENTORY = 1
                };

                IntermediateBuffer();

                void update();

                void moveFromBuffer(StorageType storage_tt, int ii);

                void moveInBuffer(StorageType storage_tt, int ii);

                int getIndex();

            private:
                std::shared_ptr<StorageCell> storage_cell_ptr;

                int count;
            };

            void open();
            void close();

            void updateStorageObjectTexture(
                const StorageCell& st_cell,
                InventoryCellButton& inv_cell_button);

            static MyTexture<BaseButton::Status> inventory_cell_texture;
            static MyTexture<BaseButton::Status> up_down_button_texture;
            static MyTexture<Instrument::InstrumentType> instruments_texture;

            Status status;

            int index_using_hand;

            int shift;

            int row_length;
            int count_rows;

            sf::RectangleShape background;

            std::vector<InventoryCellButton> inventory_cell_button_vector;

            std::vector<HandCellButton> hand_cell_button_vector;

            IntermediateBuffer intermediate_buffer;

            // RectangleButton up_arrow_button;
            // RectangleButton down_arrow_button;
        };

        class Indicator
        {
        public:
            static void loadTexture();

            void create();

            void draw();

            void setColor(const sf::Color& color);

            void setSize(const sf::Vector2f& s2);

            void setPosition(const sf::Vector2f& p2);

            void setDesignation(const std::string& str);

            void setProcent(int procent);

        private:
            static sf::Texture indicator_border_texture;

            sf::RectangleShape indicator_shape;

            sf::RectangleShape indicator_border_shape;

            std::vector<sf::RectangleShape> procent_digit_shape_list;
            std::vector<sf::RectangleShape> designation_letter_shape_list;

            sf::Vector2f m_size;

            std::string designation;

            int int_procent;
            std::string str_procent;
        };

        class PlayerInterface
        {
            friend sf::Vector2f Gui::Graphic::getPlayerPositionInWindow();

            friend void Gui::handlePlayerActions();

        public:
            void loadTextures();

            void drawPlayer();

            void drawInterface();

            void update();

            void zoom();

        private:
            MyTexture<Player::Status> hero_texture;
            sf::RectangleShape hero_shape;

            sf::RectangleShape left_corner;

            Indicator health_indicator;

            Indicator hunger_indicator;
        };

    private:
        float scope;

        int rendering_radius;

        const float MAX_SCOPE = 4;
        const float MIN_SCOPE = 2.5;

        PlayerInterface player_interface;

        InventoryInterface inventory_interface;

        MyTexture<PhysicalObject::Type> physical_object_texture;

        MyTexture<char> char_texture;

        void loadObjectTexture();
        void loadCharTexture();

        void drawWorld();
    };

public:
    Graphic graphic;
};

#endif // GUI_HPP