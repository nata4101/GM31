#pragma once


class Manager
{
private:
	static class CScene* m_scene;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

};