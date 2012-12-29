/*========================================================
* CLayer.h
* @author Sergey Mikhtonyuk
* @date 20 July 2009
=========================================================*/
#ifndef _CLAYER_H__
#define _CLAYER_H__

#include "ILayer.h"
#include "../Engine.Graphics/Graphics_fwd.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"
#include <vector>

namespace VG
{
	/// Implementation of ILayer interface
	/** @ingroup VG */
	class NOVTABLE CLayer : 
		public Core::SCOM::ComRootObject<>,
		public ILayer
	{
	public:
		
		DECLARE_IMPLEMENTATION(CLayer)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ILayer)
		END_INTERFACE_MAP()

		CLayer();

		~CLayer();

		void FinalConstruct(Engine::Graphics::IRenderer* renderer);


		size_t getComponentsNum() const;

		IPath* getComponent(size_t index) const;

		void AddComponent(IPath* path);

		IPath* AddNewComponent();

		void RemoveComponent(IPath* path);

		void RecalculateAll();

		void setToleranceToAll(float tolerance);

		void Render();


		void AddUser();

		void RemoveUser();

	private:

		std::vector<IPath*> mComponents;

		int mUsageRefs;

		Engine::Graphics::IRenderer* mRenderer;

		Core::SCOM::ComPtr<Engine::Graphics::IMaterial> mMatFill;

		Core::SCOM::ComPtr<Engine::Graphics::IMaterial> mMatStroke;
	};

} // namespace

#endif // _CLAYER_H__