#include "NetMsgCreateWO.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <iostream>
#include <sstream>
#include <string>
#include "NetMsgMoveObject.h"
#include "Vector.h"
#include "WO.h"
#include "GLView.h"
#include "WorldContainer.h"
#include "Model.h"
#include "WOLight.h"
#include "GLViewNewModule.h"
#include "AftrManagers.h"

using namespace Aftr;

NetMsgMacroDefinition(NetMsgMoveObject);

NetMsgMoveObject::NetMsgMoveObject()
{
	this->message = message;
}

NetMsgMoveObject::~NetMsgMoveObject()
{
}

bool NetMsgMoveObject::toStream(NetMessengerStreamBuffer& os) const
{
	os << this-> message << model << position.x << position.y << position.z;
	return true;
}

bool NetMsgMoveObject::fromStream(NetMessengerStreamBuffer& is)
{
	is >> this-> message >> model >> position.x >> position.y >> position.z;
	return true;
}

void NetMsgMoveObject::onMessageArrived()
{
	if (model == "xwing") {
		if (!((GLViewNewModule*)ManagerGLView::getGLView())->playerTwo) {
			((GLViewNewModule*)ManagerGLView::getGLView())->playerTwo = true;
			((GLViewNewModule*)ManagerGLView::getGLView())->playerTwoShip = WO::New(((GLViewNewModule*)ManagerGLView::getGLView())->xwing, Vector(.1, .1, .1), MESH_SHADING_TYPE::mstFLAT);
			((GLViewNewModule*)ManagerGLView::getGLView())->playerTwoShip->setLabel("Player Two Ship");
			ManagerGLView::getGLView()->getWorldContainer()->push_back(((GLViewNewModule*)ManagerGLView::getGLView())->playerTwoShip);
		}
		((GLViewNewModule*)ManagerGLView::getGLView())->playerTwoShip->setPosition(position);
		//((GLViewNewModule*)ManagerGLView::getGLView())->xwingPosition = position;
		std::cout << this->toString() << std::endl;
	}
	else {
		((GLViewNewModule*)ManagerGLView::getGLView())->ywing->setPosition(position);
		((GLViewNewModule*)ManagerGLView::getGLView())->ywingPosition = position;
		std::cout << this->toString() << std::endl;
	}
}

std::string NetMsgMoveObject::toString() const
{
	std::stringstream ss;
	ss << NetMsg::toString();
	ss << "Message: " << this->message << "\n";
	ss << "Model: " << model << "\n";
	ss << "Position: " << position << "\n";

	return ss.str();
}
 //namespace Aftr
#endif