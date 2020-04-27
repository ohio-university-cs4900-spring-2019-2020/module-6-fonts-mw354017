#pragma once

#include "NetMsg.h"
#include "../../../include/aftr/Vector.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

	class NetMsgMoveObject : public NetMsg
	{
	public:
		//NetMsgMacroDeclaration(NetMsgMoveObject);

		NetMsgMoveObject();
		virtual ~NetMsgMoveObject();
		virtual bool toStream(NetMessengerStreamBuffer& os) const;
		virtual bool fromStream(NetMessengerStreamBuffer& is);
		virtual void onMessageArrived();
		virtual std::string toString() const;

		unsigned int size;
		float* vertices;

		std::string message;
		Vector position;
		std::string model;

	protected:

	};

} //namespace Aftr

#endif