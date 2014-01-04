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

#include "OBSApi.h"

Effect::Effect(Shader* shader, float x, float y, float width, float height)
{
	this->shader = shader;
	this->pos.x = x;
	this->pos.y = y;
	this->size.x = width;
	this->size.y = height;
	this->enabled = true;
}

Effect::~Effect()
{
}

void Effect::Apply(Texture* texture)
{
	if (this->shader && this->enabled)
	{
		Shader* oldShader = GetCurrentPixelShader();

		Vect2 baseSize = OBSGetBaseSize();

		float x = pos.x;
		float y = pos.y;
		float x2 = (x + size.x);
		float y2 = (y + size.y);
		float u = x / baseSize.x;
		float v = y / baseSize.y;
		float u2 = x2 / baseSize.x;
		float v2 = y2 / baseSize.y;

		Texture* renderTarget = GS->GetRenderTarget();

		// apply effect
		GS->CopyTexture(texture, renderTarget);
		LoadPixelShader(this->shader);
		DrawSpriteEx(texture, 0xFFFFFFFF, x, y, x2, y2, u, v, u2, v2);

		LoadPixelShader(oldShader);
	}
}

EffectSource::EffectSource()
{
	Vect2 baseSize = OBSGetBaseSize();
	this->texture = CreateTexture((UINT)baseSize.x, (UINT)baseSize.y, GS_BGRA, NULL, FALSE, TRUE);
}

EffectSource::~EffectSource()
{
	std::map<std::string, Effect*>::iterator i;
	for (i = this->effects.begin(); i != this->effects.end(); i++)
	{
		delete i->second;
	}
	delete this->texture;
}

void EffectSource::Render(const Vect2 &pos, const Vect2 &size)
{
	this->BeforeRender(pos, size);

	std::map<std::string, Effect*>::iterator i;
	for (i = this->effects.begin(); i != this->effects.end(); ++i)
	{
		i->second->Apply(this->texture);
	}

	this->AfterRender(pos, size);
}

void EffectSource::AddEffect(const std::string &effectName, Effect* effect)
{
	this->DeleteEffect(effectName);
	this->effects[effectName] = effect;
}

void EffectSource::DeleteEffect(const std::string &effectName)
{
	std::map<std::string, Effect*>::iterator find;
	find = this->effects.find(effectName);
	if (find != effects.end())
	{
		Effect* oldEffect = find->second;
		delete oldEffect;
		this->effects.erase(find->first);
	}
}

Effect* EffectSource::GetEffect(const std::string &effectName)
{
	std::map<std::string, Effect*>::iterator find;
	find = this->effects.find(effectName);
	if (find != effects.end())
	{
		return find->second;
	}
	else
	{
		return NULL;
	}
}