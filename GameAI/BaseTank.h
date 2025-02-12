#ifndef BASETANK_H
#define BASETANK_H

#include "GameObject.h"
#include "Texture2D.h"
#include <SDL.h>

//---------------------------------------------------------------

class BaseTank : protected GameObject
{
	//---------------------------------------------------------------
public:
	BaseTank(SDL_Renderer* renderer, TankSetupDetails details);
	~BaseTank();

	virtual void	ChangeState(BASE_TANK_STATE newState);

	virtual void	Update(float deltaTime, SDL_Event e);
	void			Render();
	virtual Rect2D	GetAdjustedBoundingBox();

	//Attributes.
	int				GetHealth()									{return mHealth;}
	int				GetBullets()								{return mBullets;}
	int				GetRockets()								{return mRockets;}
	int				GetFuel()									{return mFuel;}
	int				GetMines()									{return mMines;}

	//Movement.
	double			GetMass()									{return mMass;}
	double			GetMaxSpeed()								{return mMaxSpeed;}
	double			GetMaxForce()								{return mMaxForce;}
	double			GetMaxTurnRate()							{return mMaxTurnRate;}

	void			SetPosition(Vector2D newPosition)			{mPosition = newPosition;}
	Vector2D		GetPointAtFrontOfTank();
	Vector2D		GetPointAtRearOfTank();
	void			GetCornersOfTank(Vector2D* topLeft, Vector2D* topRight, Vector2D* bottomLeft, Vector2D* bottomRight);

	void			IncrementTankRotationAngle(double deg);
	void			IncrementManRotationAngle(double deg);

	void			DeductABullet()								{mBullets--;}
	void			DeductAMine()								{mMines--;}
	void			DeductARocket()								{mRockets--;}

	void			Rebound(Vector2D position);
	//---------------------------------------------------------------
protected:
	virtual void	MoveInHeadingDirection(float deltaTime);

	bool			RotateHeadingToFacePosition(Vector2D target);
	void			RotateHeadingByRadian(double radian, int sign);		//Sign is direction of turn. Either -1 or 1.
	void			RotateManByRadian(double radian, int sign);
	void			SetHeading(Vector2D newHeading);

	void			FireABullet();
	void			FireRockets();
	void			DropAMine();

	//---------------------------------------------------------------
private:
	SDL_Rect		GetCurrentManSprite();
	SDL_Rect		GetCurrentCannonSprite();

	//---------------------------------------------------------------
private:
	//We need this to pass on to bullets.
	SDL_Renderer*	mRenderer;

	//Animating man in tank.
	Texture2D*		mManSpritesheet;					//The man in the tank.
	int				mManSingleSpriteHeight;
	int				mManSingleSpriteWidth;

	bool			mManFireFrame;
	float			mManFireTime;
	Vector2D		mManFireDirection;

	Vector2D		mManOffset;
	double			mManRotationAngle;

	//Animating Cannon details.
	Texture2D*		mCannonSpritesheet;					//The man in the tank.
	int				mCannonSingleSpriteHeight;
	int				mCannonSingleSpriteWidth;
	bool			mCannonAttachedRight;
	bool			mCannonAttachedLeft;
	bool			mCannonFireFrame;
	float			mCannonFireTime;
	bool			mFiringRocket;
	//Identifying details.
	string			mStudentName;

	//Attributes.
	int				mHealth;
	int				mBullets;
	int				mFuel;
	int				mMines;
	int				mRockets;
	
	//Movement.
	double			mMass;
	double			mMaxSpeed;
	double			mMaxForce;
	double			mMaxTurnRate;

	//---------------------------------------------------------------
protected:
	BASE_TANK_STATE mCurrentState;

	//Movement.
	double			mCurrentSpeed;
	Vector2D	    mVelocity;
	Vector2D		mHeading;
	Vector2D		mSide;	
};

//---------------------------------------------------------------

#endif //BASETANK_H