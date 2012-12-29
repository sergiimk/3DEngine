/*========================================================
* IEntityObserver.h
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#ifndef _IENTITYOBSERVER_H__
#define _IENTITYOBSERVER_H__

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	enum EEntityChangeType
	{
		ECT_COMPONENT_ADDED,	///< Called when entity component is added (arg = IComponent*)
		ECT_COMPONENT_REMOVED,	///< Called when entity component is removed (arg = IComponent*)
		ECT_DESTROYING,			///< Called when entity is about to be destroyed (arg = 0)
	};

	//////////////////////////////////////////////////////////////////////////

	/// Observers are objects that are notified about important changes in entity.
	/** Common usage is to observe the entity destruction event to clean-up and
	 *  detach all interpolators and other modifiers
	 *  @ingroup Engine */
	class IEntityObserver
	{
	public:

		/// Notification method
		virtual void OnEntityChanged(EEntityChangeType type, void* args) = 0;
	};

} // namespace

#endif // _IENTITYOBSERVER_H__