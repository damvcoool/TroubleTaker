#ifndef TroubleTaker_H_
#define TroubleTaker_H_

#include "gameplay.h"

using namespace gameplay;

/**
 * Main game class.
 */
class TroubleTaker: public Game,Control::Listener
{
public:

    /**
     * Constructor.
     */
    TroubleTaker();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);

    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

    void controlEvent(Control *control, EventType evt);

    /*We are not using this yet*/
    bool checkScene(Node* node, Ray* ray);

protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    Scene* _scene;
    bool _wireframe;



    /**
             * Currently selected node (or NULL)
             */
            Node* _selected;

            /**
               * Sidebar Form
               */
        	  Form* _form;

      /**
       * Form References
       */
        Button* _bPlayAll;
        Button* _rightPunch;

        //Just for the prototype
       Font* _font;
       Font*_fontWinnerMessage;

       int bloodPlayer;
       int bloodEnemy;

       AudioSource* wheelsSound;
       int counter;
};

#endif
