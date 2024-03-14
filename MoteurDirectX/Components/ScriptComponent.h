#pragma once


class ScriptComponent : public Component
{
public:

	ScriptComponent(Entity* _pEOwner);

	virtual void Update(const Timer& gt);
	virtual void Draw(const Timer& gt);

};