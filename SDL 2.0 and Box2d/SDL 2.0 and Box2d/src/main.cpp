#include <SDL.h>
#include <Box2D/Box2D.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include "window.h"
#include "timer.h"

int RadToDeg(float rad){
    return rad * (180 / 3.145);
}
float DegToRad(int deg){
    return deg * (3.145 / 180);
}
//For converting between box2d units and pixels
//I've chosen 8px = 1Box2d unit
float Box2dToPixel(float unit){
    return unit * 8;
}
float PixelToBox2d(float pixel){
    return pixel / 8.0f;
}

#undef main
int main(int argc, char** argv){
    Window::Init("Box 2d Test");

    //The positions are taken from the center of the object I believe
    //So a half-width offset must be applied to draw things correctly

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0.0f, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
    float gHw = 4.0f, gHh = 1.0f;
	groundBox.SetAsBox(gHw, gHh);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
    
    //Setup the ground's SDL_Rect and texture
    SDL_Rect grndRect = { Window::Box().w / 2 - Box2dToPixel(groundBody->GetPosition().x) - Box2dToPixel(gHw),
        Window::Box().h / 2 - Box2dToPixel(groundBody->GetPosition().y) - Box2dToPixel(gHh), 
        2 * Box2dToPixel(gHw), 2 * Box2dToPixel(gHh) };
    SDL_Texture *grndTex = Window::LoadImage("../res/img/grnd.png");
	
    // Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, PixelToBox2d(80.0f));
    bodyDef.angle = DegToRad(0);
    bodyDef.gravityScale = 1;
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
    float bHw = 1.0f, bHh = 1.0f;
	dynamicBox.SetAsBox(bHw, bHh);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

    //Setup the body's SDL rect and tex
    SDL_Rect bodyRect = { Window::Box().w / 2 - Box2dToPixel(body->GetPosition().x) - Box2dToPixel(bHw), 
        Window::Box().h / 2 - Box2dToPixel(body->GetPosition().y) - Box2dToPixel(bHh),
        2 * Box2dToPixel(bHw), 2 * Box2dToPixel(bHh) };
    SDL_Texture *bodyTex = Window::LoadImage("../res/img/obj.png");
    
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 4;

    //Should i really use a variable timer for the physics?

    //For object movement direction
    b2Vec2 moveVect(0, 0);
    float speed = 500.0f;

    //Our event structure
	SDL_Event e;
	//For tracking if we want to quit
	bool quit = false;
	while (!quit){
		//Event Polling
		while (SDL_PollEvent(&e)){
			//If user closes he window
			if (e.type == SDL_QUIT)
				quit = true;
			//If user presses any key
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
                    case SDLK_w:
                        moveVect.y = 1.0f;
                        break;
                    case SDLK_s:
                        moveVect.y = -1.0f;
                        break;
                    //Why is x move dir backwards?
                    //Because box2d seems to define right to be -x and left to be +x, wtf?
                    case SDLK_d:
                        moveVect.x = -1.0f;
                        break;
                    case SDLK_a:
                        moveVect.x = 1.0f;
                        break;
					//For quitting, escape key
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}
            if (e.type == SDL_KEYUP){
                switch (e.key.keysym.sym){
                    case SDLK_w:
                        moveVect.y = 0;
                        break;
                    case SDLK_s:
                        moveVect.y = 0;
                        break;
                    case SDLK_d:
                        moveVect.x = 0;
                        break;
                    case SDLK_a:
                        moveVect.x = 0;
                        break;
                }
            }
		}
        //Logic
        //Normalize movement vector
        moveVect.Normalize();
   
        //Apply impulse (Doesn't seem to have an effect?
        //body->ApplyLinearImpulse(speed * moveVect, body->GetWorldCenter());
        //Try with a force application
        body->ApplyForceToCenter(speed * moveVect);
        //Set velocity directly
        //body->SetLinearVelocity(speed * moveVect);
        
        //Physics update
        world.Step(timeStep, velocityIterations, positionIterations);
        //Update body rect
        b2Vec2 bodyPos = body->GetPosition();
        float32 angle = body->GetAngle();

        bodyRect.x = Window::Box().w / 2 - Box2dToPixel(bodyPos.x) - Box2dToPixel(bHw);
        bodyRect.y = Window::Box().h / 2 - Box2dToPixel(bodyPos.y) - Box2dToPixel(bHh);

        std::cout << "x Move: " << moveVect.x 
            << " x pixel pos: " << bodyRect.x
            << " x box2d pos: " << bodyPos.x
            << std::endl;
        //std::cout << "y Move: " << moveVect.y << " y pos: " << bodyRect.y << std::endl;

        //Rendering
        Window::Clear();

        Window::Draw(grndTex, grndRect);
        Window::Draw(bodyTex, bodyRect, NULL, RadToDeg(angle));

        Window::Present();
    }

    Window::Quit();
    
	return 0;
}