#pragma once

#include <memory>

namespace ZHU
{
	// This is a helper class which should be used in case a class derives from a base class,
	// which derives from enable_shared_from_this<>.
	// If Derived will also inherit enable_shared_from_this, it will cause multiple inheritance from enable_shared_from_this, 
	// which results in a runtime errors because we have 2 copies of the WeakPtr inside shared_ptr
	template<typename Base, typename Derived>
	class inherit_shared_from_this
	{
	public:
		typename std::shared_ptr<Derived> shared_from_this()
		{
			Base* pBase = static_cast<Derived*>(this);
			std::shared_ptr<Base> pShared = pBase->shared_from_this();
			return std::static_pointer_cast<Derived>(pShared);
		}

		typename std::shared_ptr<const Derived> shared_from_this() const
		{
			const Base* pBase = static_cast<const Derived*>(this);
			std::shared_ptr<const Base> pShared = pBase->shared_from_this();
			return std::static_pointer_cast<const Derived>(pShared);
		}
	};
}