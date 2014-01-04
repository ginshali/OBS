/********************************************************************************
Copyright (C) 2013 ginshali.info

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
********************************************************************************/

#pragma once

#include <map>
#include <string>

class BASE_EXPORT Effect
{

public:
	Shader* shader;
	Vect2 pos, size;
	bool enabled;

	Effect(Shader* shader, float x, float y, float width, float height);
	~Effect();

	void Apply(Texture* texture);
};

class BASE_EXPORT EffectSource
	: public ImageSource
{
	friend class Effect;

	Texture* texture;
	std::map<std::string, Effect*> effects;

public:
	EffectSource();
	virtual ~EffectSource();

	virtual void Initialize() {}
	virtual void Preprocess() {}
	virtual void Tick(float fSeconds) {}
	void Render(const Vect2 &pos, const Vect2 &size);
	virtual void BeforeRender(const Vect2 &pos, const Vect2 &size) {};
	virtual void AfterRender(const Vect2 &pos, const Vect2 &size) {};

	virtual Vect2 GetSize() { return API->GetBaseSize(); }

	virtual void UpdateSettings() {}

	virtual void BeginScene() {}
	virtual void EndScene() {}

	virtual void GlobalSourceLeaveScene() {}
	virtual void GlobalSourceEnterScene() {}

	virtual void SetFloat(CTSTR lpName, float fValue) {}
	virtual void SetInt(CTSTR lpName, int iValue) {}
	virtual void SetString(CTSTR lpName, CTSTR lpVal) {}
	virtual void SetVector(CTSTR lpName, const Vect &value) {}
	virtual void SetVector2(CTSTR lpName, const Vect2 &value) {}
	virtual void SetVector4(CTSTR lpName, const Vect4 &value) {}
	virtual void SetMatrix(CTSTR lpName, const Matrix &mat) {}

	void AddEffect(const std::string &effectName, Effect* effect);
	void DeleteEffect(const std::string &effectName);
	Effect* GetEffect(const std::string &effectName);

	//-------------------------------------------------------------

	virtual bool GetFloat(CTSTR lpName, float &fValue)   const { return false; }
	virtual bool GetInt(CTSTR lpName, int &iValue)       const { return false; }
	virtual bool GetString(CTSTR lpName, String &strVal) const { return false; }
	virtual bool GetVector(CTSTR lpName, Vect &value)    const { return false; }
	virtual bool GetVector2(CTSTR lpName, Vect2 &value)  const { return false; }
	virtual bool GetVector4(CTSTR lpName, Vect4 &value)  const { return false; }
	virtual bool GetMatrix(CTSTR lpName, Matrix &mat)    const { return false; }
};