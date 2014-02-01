#include "TroubleTaker.h"

// Declare our game instance
TroubleTaker game;

TroubleTaker::TroubleTaker()
    : _scene(NULL), _wireframe(false), _bPlayAll(NULL), _form(NULL),_selected(NULL),_rightPunch(NULL)
{
}

void TroubleTaker::initialize()
{
    // Load game scene from file
	//Bundle* bundle = Bundle::create("res/scene.gpb");
    _scene = Scene::load("res/demo.scene");

    // Set the aspect ratio for the scene's camera to match the current resolution
    _scene->getActiveCamera()->setAspectRatio(getAspectRatio());

    //For prototype
	wheelsSound = AudioSource::create("res/IntroEyeoftheTiger1.wav");

	bloodPlayer=10;
	bloodEnemy=10;
	_font = Font::create("res/ui/arial.gpb");
	_fontWinnerMessage= Font::create("res/ui/arial.gpb");
	counter=0;

	_form = Form::create("res/fist.form");

	_bPlayAll = (Button *)_form->getControl("playAll");
	_rightPunch = (Button *)_form->getControl("rightPunch");

	_bPlayAll->addListener(this, Listener::CLICK);
	_rightPunch->addListener(this, Listener::CLICK);

	/*
	animation = boxNode->getAnimation("animations");
	animation->createClips("res/player.animation");
	idle = animation->getClip("idle");
	walk = animation->getClip("walk");
	AnimationClip* clip = animation->getClip("walk");
	// Set clip properties
	clip->setSpeed(0.5f);
	clip->setRepeatCount(AnimationClip::REPEAT_INDEFINITE);
	clip->play();
	*/

    _scene->visit(this, &TroubleTaker::initializeScene);
}

bool TroubleTaker::initializeScene(Node* node)
{
    Model* model = node->getModel();
    if (model && model->getMaterial())
    {
        initializeMaterial(_scene, node, model->getMaterial());
    }

    return true;
}

void TroubleTaker::initializeMaterial(Scene* scene, Node* node, Material* material)
{
    // Bind light shader parameters to dynamic objects only
    if (node->hasTag("dynamic"))
    {
        material->getParameter("u_ambientColor")->bindValue(scene, &Scene::getAmbientColor);
        Node* lightNode = scene->findNode("sun");
        if (lightNode)
        {
            material->getParameter("u_directionalLightColor[0]")->bindValue(lightNode->getLight(), &Light::getColor);
            material->getParameter("u_directionalLightDirection[0]")->bindValue(lightNode, &Node::getForwardVectorView);
        }
    }
}

void TroubleTaker::finalize()
{
	SAFE_RELEASE(_form);
    SAFE_RELEASE(_scene);
}

void TroubleTaker::update(float elapsedTime)
{
    // Rotate model
    //_scene->findNode("Cube")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void TroubleTaker::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    //For Prototype

    _form->draw();

       	// Draw the text at position 20,20 using red color
       	_font->start();
       	char text[1024];
       	char text3[1024];
       	sprintf(text, "Blood player:%d	Blood enemy:%d ",bloodPlayer, bloodEnemy);
       	//sprintf(text, "Elkin ");
       	_font->drawText(text, 5, 20, Vector4(1, 0, 0, 1), _font->getSize());
       	_font->finish();

       	if(bloodEnemy<=0){

       		_fontWinnerMessage->start();
       		char text2[1024];
       		sprintf(text2, "The winner is player!!!!");
       		_fontWinnerMessage->drawText(text2, 10, 50, Vector4(1, 0, 0, 1), _fontWinnerMessage->getSize());
       		_fontWinnerMessage->finish();
       	}
        // Visit all the nodes in the scene for drawing

        _scene->visit(this, &TroubleTaker::drawScene);
}

bool TroubleTaker::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel();
    if (model)
    {
        model->draw(_wireframe);
    }
    return true;
}

void TroubleTaker::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void TroubleTaker::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        _wireframe = !_wireframe;
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}


void TroubleTaker::controlEvent(Control *control, EventType evt) {
   switch(evt) {
   case Listener::CLICK:
      if (control==_bPlayAll) {
    	  bloodEnemy--;
    	  counter++;
         //_scene->visit(this, &SceneViewer::startAnims);
      }
      if (control==_rightPunch) {
    	  bloodPlayer--;
    	  counter++;
         //_scene->visit(this, &SceneViewer::startAnims);
      }
      //if (control==_bPlaySelected) {
         //this->playNodeAmination(_selected);
      //}
      break;
   }

   if(counter==15){
       wheelsSound->play();
   }
}
