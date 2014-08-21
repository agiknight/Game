#pragma once


namespace graphic
{

	class cSurface
	{
	public:
		cSurface();
		virtual ~cSurface();

		bool CreateRenderTarget(const int width, const int height);
		bool WriteFile(const string &fileName);

		void Begin();
		void End();
		void Render();
		void Clear();

		IDirect3DTexture9* GetTexture();
		IDirect3DSurface9* GetRenderTarget();
		IDirect3DSurface9* GetZBuffer();


	private:
		int m_width;
		int m_height;
		IDirect3DTexture9 *m_texture;
		IDirect3DSurface9 *m_surface;
		IDirect3DSurface9 *m_zbuffer;

		// ����Ÿ�� ����Ī�� ����Ǵ� �ӽ� ������.
		IDirect3DSurface9 *m_oldBackBuffer;
		IDirect3DSurface9 *m_oldZBuffer;
		D3DVIEWPORT9 m_oldViewport;
	};


	inline IDirect3DTexture9* cSurface::GetTexture() { return m_texture; }
	inline IDirect3DSurface9* cSurface::GetRenderTarget() { return m_surface; }
	inline IDirect3DSurface9* cSurface::GetZBuffer() { return m_zbuffer; }
}
