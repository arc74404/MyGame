#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "physical_object/physical_object.hpp"
#include "player/player.hpp"
#include "storage/instrument.hpp"
#include "world/cell.hpp"

#include "inventory_cell_button.hpp"
#include "is_key_button_clicked_off.hpp"
#include "my_texture.hpp"
#include "rectangle_button.hpp"

class Gui
{
    friend void BaseButton::draw() const;
    friend void InventoryCellButton::draw() const;

public:
    static Gui* getInstance();

    void handleEvents();

    bool isMouseInRectangle(const sf::Vector2f& pos, const sf::Vector2f& s);

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

        void display();

        void zoom(float s);

        //////////////////

        float getScope();

        sf::Vector2f getPlayerPositionInWindow();

        void create();

        class CraftMenuInterface
        {
        public:
            enum class Status
            {
                CLOSE = 0,
                OPEN  = 1
            };

            class CraftRowInterface
            {
            public:
                CraftRowInterface();

                void setSize(const sf::Vector2f&);

                void setPosition(const sf::Vector2f&);

                void setRowIndex(int index);

                void update();

                void draw();

                void operator=(const CraftRowInterface&);

            private:
                isDefaultButtonClickedOff is_result_object_button_clicked_off;

                std::vector<InventoryCellButton> ingredient_shape_vector;

                InventoryCellButton result_object_button;

                int row_index;

                sf::Vector2f m_size;

                float pass;
            };

            void create();

            void draw();

            void raiseShift();

            void lowerShift();

            void update();

            Status getStatus();

        private:
            void updateRowInterfaceVector();
            void open();
            void close();

            Status status;

            sf::RectangleShape background;

            int shift;

            RectangleButton up_arrow_button;
            RectangleButton down_arrow_button;

            std::vector<CraftRowInterface> craft_row_interface_vector;
        };

        class InventoryInterface
        {
            friend void Gui::handleInventoryActions();

        public:
            enum class Status
            {
                CLOSE = 0,
                OPEN  = 1
            };

            void create();

            void drawFullInventory();

            void drawUsingCells();

            void raiseShift();

            void lowerShift();

            void update();

            const StorageCell& getUsingStorageCellRef();

            Status getStatus();

        private:
            class TransferCell : public StorageCell
            {
            public:
                enum class StorageType
                {
                    HAND      = 0,
                    INVENTORY = 1
                };

                TransferCell();

                void setData(StorageType storage_tt, int ii,
                             std::shared_ptr<StorageObject> st_obj, int c);

                StorageType getStorageType();

                int getIndex();

                bool isClear();

                bool isOtherCell();

                void clear() override;

                InventoryCellButton inventory_cell_button;

            private:
                // int count;

                StorageType storage_type;

                int index;
            };

            void open();
            void close();

            void updateTransfer(int index, StorageCell& st_cell,
                                TransferCell::StorageType storage_type);


            void updateStorageObjectTexture(
                const StorageCell& st_cell,
                InventoryCellButton& inv_cell_button);

            Status status;

            int index_using_hand;

            int shift;

            int row_length;
            int count_rows;

            sf::RectangleShape background;

            std::vector<InventoryCellButton> inventory_cell_button_vector;
            // std::vector<isDefaultButtonClickedOff>
            //     inventory_cell_button_checking_left_click_vector;
            // std::vector<isDefaultButtonClickedOff>
            //     inventory_cell_button_checking_right_click_vector;

            std::vector<HandCellButton> hand_cell_button_vector;
            // std::vector<isDefaultButtonClickedOff>
            //     hand_cel_button_checking_click_vector;

            TransferCell transfer_cell;

            isMouseButtonClickedOff is_right_clicked_off;
            isMouseButtonClickedOff is_left_clicked_off;
            isKeyboardButtonClickedOff is_tab_clicked_off_map;

            // RectangleButton up_arrow_button;
            // RectangleButton down_arrow_button;
        };

        class Indicator
        {
        public:
            void create();

            void draw();

            void setColor(const sf::Color& color);

            void setSize(const sf::Vector2f& s2);

            void setPosition(const sf::Vector2f& p2);

            void setDesignation(const std::string& str);

            void setProcent(int procent);

        protected:
            sf::RectangleShape indicator_shape;

            sf::RectangleShape indicator_border_shape;

            sf::Vector2f m_size;
            sf::Vector2f m_position;

            std::vector<sf::RectangleShape> procent_digit_shape_list;

            std::vector<sf::RectangleShape> designation_letter_shape_list;

            std::string designation;

            int int_procent;
            std::string str_procent;
        };

        class TimeCountdown
        {
        public:
            void create();

            void draw();

            void setColor(const sf::Color& color);

            void setSize(const sf::Vector2f& s2);

            void setPosition(const sf::Vector2f& p2);

            void setSeconds(float s);

            void setFullTime(float t);

        private:
            sf::RectangleShape indicator_shape;

            sf::RectangleShape indicator_border_shape;

            std::vector<sf::RectangleShape> seconds_digit_shape_list;

            sf::Vector2f m_size;
            sf::Vector2f m_position;

            std::string str_left_seconds;

            float left_seconds;

            float full_time;
        };

        class PlayerInterface
        {
            friend sf::Vector2f Gui::Graphic::getPlayerPositionInWindow();

            friend void Gui::handlePlayerActions();

        public:
            void create();

            void drawPlayer();

            void drawInterface();

            void update();

            void zoom();

        private:
            void drawDroppedObjects();

            sf::RectangleShape hero_shape;

            sf::CircleShape work_radius_shape;

            sf::RectangleShape left_corner;

            Indicator health_indicator;

            Indicator hunger_indicator;

            TimeCountdown recharge_hit_countdown;
        };

    private:
        float scope;

        int rendering_radius;

        const float MAX_SCOPE = 4;
        const float MIN_SCOPE = 2.5;

        PlayerInterface player_interface;

        InventoryInterface inventory_interface;

        CraftMenuInterface craft_menu_interface;

        void drawWorld();
    };

public:
    Graphic graphic;
};

#endif // GUI_HPP