#include "TestGame.h"
#include "HelloWorldScene.h"
#include "CCActionEase.h"
#include "CCActionInterval.h"
#include "CCActionInstant.h"

USING_NS_CC;

TestGame::TestGame()
{

}


TestGame::~TestGame()
{

}

bool TestGame::Init(HelloWorld* hw)
{

	auto sprite = Sprite::create("nd3_32x32_2.png");

	sprite->setPosition(100, 100);

	//sprite->runAction(EaseIn::create(MoveBy::create(1.0f, Point(200, 100)), 1.0f));

	//sprite->runAction(Repeat::create(
	//Sequence::createWithTwoActions(
	//	CCCallFunc::create([sprite](){
	//	//CCLOG("sprite->getPosition x %f", sprite->getPosition().x);

	//	sprite->setPosition(sprite->getPosition() + Point(1.0f, 0.0f));
	//}),
	//	DelayTime::create(1.0f / 60.0f)
	//)
	//, 100));

	
	{
		Vector<FiniteTimeAction*> actions;

		actions.pushBack(CCCallFunc::create([=](){
			//CCLOG("sprite->getPosition x %f", sprite->getPosition().x);
			sprite->setPosition(sprite->getPosition() + Point(1.0f, 0.0f));

		}));

		//actions.pushBack(Spawn::createWithTwoActions(DelayTime::create(60.0f / 60.0f), Blink::create(1.0f, 1)));

		actions.pushBack(DelayTime::create(1.0f / 60.0f));
		

		sprite->runAction(Repeat::create(Sequence::create(actions), 100));
		//sprite->runAction(Repeat::create(Blink::create(1.0f, 1), 100));
	}

	{

		//hw->runAction(Follow::create(sprite));
	}

	{
		Vector<SpriteFrame*> spriteFrames;

		spriteFrames.pushBack(SpriteFrame::createWithTexture(sprite->getTexture(), Rect(0.0f, 0.0f, 32.0f, 32.0f)));
		spriteFrames.pushBack(SpriteFrame::createWithTexture(sprite->getTexture(), Rect(32.0f, 0.0f, 32.0f, 32.0f)));


		auto animation = Animation::createWithSpriteFrames(spriteFrames, 1.0f / 30.0f);

		sprite->runAction(RepeatForever::create(Animate::create(animation)));


	}

	{
		std::function<void()> fa;
		{
			std::string s = "test";
			auto f = [=]()
			{
				CCLOG("s = %s", s.c_str());
			};

			fa = f;

			s = "test2";

			
		}

		fa();
	}

	hw->addChild(sprite);


	{
		
		auto gen = [=](){
			int i, isz;

			isz = 1000;

			for (i = 0; i < isz; i++)
			{
				auto sprite = Sprite::create("nd3_32x32_2.png");
				sprite->setPosition(200 + (rand() % 100), 200 + (rand() % 100));

				{
					Vector<FiniteTimeAction*> actions;

					actions.pushBack(CCCallFunc::create([=](){
						sprite->setPosition(sprite->getPosition() + Point(2.0f, 1.0f));

					}));
					actions.pushBack(DelayTime::create(1.0f / 60.0f));


					sprite->runAction(Repeat::create(Sequence::create(actions), 100));
				}


				this->sprites.push_back(sprite);

				hw->addChild(sprite);

			}

		};

		auto del = [=](){

			std::for_each(sprites.begin(), sprites.end(), [=](Sprite* sp){
				sp->removeFromParent();
			});

			sprites.clear();

		};
	
		auto sprite = Sprite::create("nd3_32x32_2.png");
		sprite->setPosition(100, 300);

		{
			Vector<FiniteTimeAction*> actions;

			actions.pushBack(CCCallFunc::create([=](){
				gen();

			}));
			actions.pushBack(DelayTime::create(1.0f));

			actions.pushBack(CCCallFunc::create([=](){
				del();
			}));
			actions.pushBack(DelayTime::create(1.0f));


			sprite->runAction(Repeat::create(Sequence::create(actions), 100));
		}

		hw->addChild(sprite);



	}
	
	

	return true;
}

