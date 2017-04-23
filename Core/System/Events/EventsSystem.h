#pragma once
/**
@file EventsSystem.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include "EventProxy.h"
#include "EventHandlers.h"
#include "IEventArgs.h"
#include "RegisteredEvent.h"


#include <mutex>
#include <set>
#include <string>


namespace sw {
namespace gui
{

class UIElement;




/**@brief Events management.

For now this class stores only registered events. Think about future use.

Registering events needs to be in separate dll, otherwise controls can't register their static variables.*/
class EventsSystem
{
private:

	EventType						m_counter;

	std::mutex						m_registerMutex;
	std::set< RegisteredEvent >		m_registeredEvents;

protected:
public:
					~EventsSystem		() = default;

	/**@brief Registers new event and return idetifier used in DelegateContainers.*/
	const RegisteredEvent*		RegisterEvent		( const char* eventName, RoutingStrategy strategy, TypeID ownerType, TypeID eventTypeId );

	/**@brief Sends event to visual tree using @ref RoutingStrategy specyfied in eventInfo.*/
	bool						RaiseEvent			( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgsOPtr&& arguments );

	/**@brief Sends event in response to other event.
	Use this function when you are in event handler and you want to send the same event structure under different name.
	Good example is UIElement::MouseRightButtonDown which is sent by UIElement in response to UIElement::MouseDown event
	sent by EventsSystem.

	@param[in] arguments Arguments structure. Note that this structure is raw pointer and you are not owner of it.
	Never use this function when you created event structure on your own. This couses memory leaks.*/
	bool						RaiseForwardEvent	( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments );


private:

	bool			RaiseDirectEvent			( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments );
	bool			RaiseBubbleEvent			( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments );
	bool			RaiseTunnelEvent			( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments );
	/**@brief Calls recursivly event for parents.*/
	void			RaiseTunnelEventForParents	( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments, UIElement* raiseForElement );

	bool			RaiseEventImpl				( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments );

public:
	static EventsSystem&		Get	();

private:
	explicit		EventsSystem		();
};


}	// gui
}	// sw