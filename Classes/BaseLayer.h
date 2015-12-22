#ifndef __BaseLayer_H__
#define __BaseLayer_H__

#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BaseLayer);

	void appear();
	void disappear();
	void close();
};

#endif