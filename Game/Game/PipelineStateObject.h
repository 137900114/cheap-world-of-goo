#pragma once

#include "Common.h"
#include "RootSignature.h"

namespace Game {
	class GraphicPSO {
		template<typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		GraphicPSO() {
			Reset();
		}
		GraphicPSO& operator=(GraphicPSO& pso) {
			memcpy(&m_PSODesc, &pso.m_PSODesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
			m_InputLayouts = pso.m_InputLayouts;
		}
		
		void Reset() { 
			m_Pso = nullptr; 
			memset(&m_PSODesc,0,sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC)); 
		}

		void SetBlendState(D3D12_BLEND_DESC desc) {	m_PSODesc.BlendState = desc; }
		void SetDepthStencilState(D3D12_DEPTH_STENCIL_DESC desc) { m_PSODesc.DepthStencilState = desc; }
		void SetDepthStencilViewFomat(DXGI_FORMAT format) { m_PSODesc.DSVFormat = format; }
		void SetFlag(D3D12_PIPELINE_STATE_FLAGS flag) { m_PSODesc.Flags = flag; }
		void SetNodeMask(UINT nodeMask) { m_PSODesc.NodeMask = nodeMask; }
		void SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE top) { m_PSODesc.PrimitiveTopologyType = top; }
		void SetRenderTargetFormat(DXGI_FORMAT format) { SetRenderTargetFormat(1, &format); }
		void SetRenderTargetFormat(UINT num, const DXGI_FORMAT* formats);
		

		void SetRootSignature(RootSignature* rootSig);

		void SetRasterizerState(D3D12_RASTERIZER_DESC state) { m_PSODesc.RasterizerState = state; }
		void SetSampleDesc(UINT count, UINT quality) { m_PSODesc.SampleDesc = { count,quality }; }
		void SetSampleMask(UINT mask) { m_PSODesc.SampleMask = mask; }
		
		void SetInputElementDesc(std::vector<D3D12_INPUT_ELEMENT_DESC>& desc) {
			m_InputLayouts = desc;
		}
		void PushBackInputElementDesc(D3D12_INPUT_ELEMENT_DESC desc) {
			m_InputLayouts.push_back(desc);
		}

		void SetVertexShader(const void* bytecode, UINT size) { m_PSODesc.VS = { bytecode,size }; }
		void SetPixelShader(const void* bytecode, UINT size) { m_PSODesc.PS = { bytecode,size }; }
		void SetGeometryShader(const void* bytecode, UINT size) { m_PSODesc.GS = { bytecode,size }; }
		void SetHullingShader(const void* bytecode, UINT size) { m_PSODesc.HS = { bytecode,size }; }
		void SetDomainShader(const void* bytecode, UINT size) { m_PSODesc.DS = { bytecode,size }; }

		bool Create(ID3D12Device* device);

		//Default��PSO��Ȼ��Ҫ��ʼ��Shader,RootSignature�ȵ���Щ����
		void LazyBlendDepthRasterizeDefault();

		ID3D12PipelineState* GetPSO();

	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PSODesc;
		ComPtr<ID3D12PipelineState> m_Pso;
		std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayouts;
	};

}